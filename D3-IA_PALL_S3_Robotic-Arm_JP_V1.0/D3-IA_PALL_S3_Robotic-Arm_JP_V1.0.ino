/*
  Author: Jeanno Philipsen
  Project: ADENG D3-IA PALL
  Part: Robotic arm station 3
  Language: C++ (arduino)
*/

/*
  Creation date: 17-5-2026
  Completion date: 10-6-2026
  POA after completion:
*/

/*
  Quality check 1 (passed/failed):
  QC by: 
  QC date:
  Remarks:
*/


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// Servo frequency
#define SERVO_FREQ 50

// Servo pulse range
#define SERVOMIN 120
#define SERVOMAX 620

// servo amount
#define NUM_SERVOS 6

// current angles
int servoPos[NUM_SERVOS] = {90, 90, 90, 90, 90, 90};

// 0 = base
// 1 = base shoulder
// 2 = elbow
// 3 = wrist up-down
// 4 = wrist turn
// 5 = gripper

// degrees to PCA9685 pulse
int angleToPulse(int angle)
{
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

// move servo slowly
void moveServoSmooth(uint8_t servo, int targetAngle)
{
  targetAngle = constrain(targetAngle, 0, 180);

  int currentAngle = servoPos[servo];

  if (currentAngle < targetAngle)
  {
    for (int angle = currentAngle; angle <= targetAngle; angle++)
    {
      pwm.setPWM(servo, 0, angleToPulse(angle));
      delay(10);
    }
  }
  else
  {
    for (int angle = currentAngle; angle >= targetAngle; angle--)
    {
      pwm.setPWM(servo, 0, angleToPulse(angle));
      delay(10);
    }
  }

  servoPos[servo] = targetAngle;
}

void setup()
{
  Serial.begin(115200);

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  delay(500);

  // Startpos
  for (int i = 0; i < NUM_SERVOS; i++)
  {
    pwm.setPWM(i, 0, angleToPulse(90));
  }

  Serial.println("6DOF Robot Arm Ready");
}

void loop()
{

  // Base
  // moveServoSmooth(0, 30);
  // delay(2000);

  // moveServoSmooth(0, 150);
  // delay(1000);

  // moveServoSmooth(0, 90);
  // delay(500);

  // Shoulder
  // moveServoSmooth(1, 45);
  // delay(500);

  // moveServoSmooth(1, 0);
  // delay(500);

  // moveServoSmooth(1, 200);
  // delay(500);

  // elbow
  moveServoSmooth(0, 255);
  delay(1000);

  moveServoSmooth(1, 135);
  delay(1000);

  moveServoSmooth(2, 80);
  delay(1000);

  moveServoSmooth(3, 100);
  delay(1000);

  moveServoSmooth(4, 10);
  delay(1000);

  // Gripper open/closed
  // moveServoSmooth(5, 20);
  // delay(1000);

  // moveServoSmooth(5, 100);
  // delay(1000);
}