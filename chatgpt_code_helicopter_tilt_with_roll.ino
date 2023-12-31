#include <Wire.h>
#include <SparkFun_MMA8452Q.h>
#include <Servo.h>

MMA8452Q accel;

Servo servoMotor1;  // Define first servo motor object
Servo servoMotor2;  // Define second servo motor object

int servo1Pin = 9;  // Pin for first servo motor
int servo2Pin = 10; // Pin for second servo motor

const int targetAngle = 90;  // Target angle for balancing
const int rollThreshold = 10; // Define a threshold for roll detection

void setup() {
  servoMotor1.attach(servo1Pin);  // Attaches the first servo to servo1Pin
  servoMotor2.attach(servo2Pin);  // Attaches the second servo to servo2Pin

  Wire.begin();
  accel.init();
  accel.setScale(SCALE_2G);
}

void loop() {
  accel.read();

  // Get accelerometer values for X, Y, and Z axes
  int x = -accel.getX(); // Negate the X value to reverse direction
  int y = -accel.getY(); // Negate the Y value to reverse direction
  int z = -accel.getZ(); // Negate the Z value to reverse direction

  // Calculate errors (difference from target angles)
  int errorX = x - targetAngle;
  int errorY = y - targetAngle;

  // Detect roll
  if (abs(z) > rollThreshold) {
    // Adjust servo angles based on roll
    int rollAdjustment = map(z, -1024, 1024, -30, 30); // Map roll to servo adjustment (-30 to 30 degrees)
    int servoAngle1 = targetAngle + errorX + errorY + rollAdjustment;
    int servoAngle2 = targetAngle - errorX + errorY - rollAdjustment;

    // Set the angles of the servo motors
    servoMotor1.write(constrain(servoAngle1, 0, 180));
    servoMotor2.write(constrain(servoAngle2, 0, 180));
  } else {
    // If no roll is detected, operate as before
    int servoAngle1 = targetAngle + errorX + errorY;
    int servoAngle2 = targetAngle - errorX + errorY;

    // Set the angles of the servo motors
    servoMotor1.write(constrain(servoAngle1, 0, 180));
    servoMotor2.write(constrain(servoAngle2, 0, 180));
  }

  delay(15);  // Delay for servo to reach position
}
