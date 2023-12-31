#include <Wire.h>
#include <SparkFun_MMA8452Q.h>
#include <Servo.h>

MMA8452Q accel;

Servo servoMotor1;  // Define first servo motor object
Servo servoMotor2;  // Define second servo motor object

int servo1Pin = 9;  // Pin for first servo motor
int servo2Pin = 10; // Pin for second servo motor

const int targetAngle = 90;  // Target angle for balancing

void setup() {
  servoMotor1.attach(servo1Pin);  // Attaches the first servo to servo1Pin
  servoMotor2.attach(servo2Pin);  // Attaches the second servo to servo2Pin

  Wire.begin();
  accel.init();
  accel.setScale(SCALE_2G);
}

void loop() {
  accel.read();

  // Get accelerometer values
  int x = accel.getX();

  // Calculate error (difference from target angle)
  int error = targetAngle - x;

  // Calculate servo angles based on error
  int servoAngle1 = targetAngle + error;
  int servoAngle2 = targetAngle - error;

  // Set the angles of the servo motors
  servoMotor1.write(constrain(servoAngle1, 0, 180));
  servoMotor2.write(constrain(servoAngle2, 0, 180));

  delay(15);  // Delay for servo to reach position
}
