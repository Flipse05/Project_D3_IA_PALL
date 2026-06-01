// Author: Jeanno Philipsen
// Project: ADENG D3-IA PALL
// Part: Robotic arm station 3
// Language: C++ (arduino)

// Creation date: 17-5-2026
// Completion date: 

// Quality check 1 (passed/failed):
// QC by: 
// QC date:

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// Servo frequentie
#define SERVO_FREQ 50

// Servo pulse range
#define SERVOMIN 120
#define SERVOMAX 620

// Aantal servo's
#define NUM_SERVOS 6

// Huidige hoeken
int servoPos[NUM_SERVOS] = {90, 90, 90, 90, 90, 90};

// Zet graden om naar PCA9685 pulse
int angleToPulse(int angle)
{
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

// Beweeg servo langzaam
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

  // Startpositie
  for (int i = 0; i < NUM_SERVOS; i++)
  {
    pwm.setPWM(i, 0, angleToPulse(90));
  }

  Serial.println("6DOF Robot Arm Ready");
}

void loop()
{
  
  // Base draaien
  moveServoSmooth(0, 30);
  delay(500);

  moveServoSmooth(0, 150);
  delay(500);

  moveServoSmooth(0, 90);
  delay(500);

  // Schouder
  moveServoSmooth(1, 45);
  delay(500);

  moveServoSmooth(1, 120);
  delay(500);

  moveServoSmooth(1, 90);
  delay(500);

  // Elleboog
  moveServoSmooth(2, 60);
  delay(500);

  moveServoSmooth(2, 120);
  delay(500);

  // Gripper open/dicht
  moveServoSmooth(5, 20);
  delay(1000);

  moveServoSmooth(5, 80);
  delay(1000);
}