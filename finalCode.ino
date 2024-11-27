#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

int motor1pin1 = 6;   // Left motor direction pin 1
int motor1pin2 = 7;   // Left motor direction pin 2
int motor1speed = 10; // Left motor PWM pin

// Motor pins
int motor2pin1 = 4;  // Right motor direction pin 1
int motor2pin2 = 5;  // Right motor direction pin 2
int motor2speed = 9; // Right motor PWM pin

void setup()
{
  Serial.begin(250000); // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);   // Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.

  // set up all pins as output
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(motor1speed, OUTPUT);
  pinMode(motor2speed, OUTPUT);

  stopMotors();
}

void loop()
{
  Dabble.processInput(); // this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.

  if (GamePad.isUpPressed() || GamePad.isSquarePressed())
  {
    moveForward(255); // Full speed forward
  }
  else if (GamePad.isDownPressed() || GamePad.isCirclePressed())
  {
    moveBackward(255); // Full speed backward
  }
  else if (GamePad.isLeftPressed())
  {
    turnLeft(180); // Turn left at 80% speed
  }
  else if (GamePad.isRightPressed())
  {
    turnRight(180); // Turn right at 80% speed
  }
  else
  {
    stopMotors(); // Stop if no button is pressed
  }
}

void moveForward(int speed)
{
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW); // Left motor forward
  analogWrite(motor1speed, speed);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW); // Right motor forward
  analogWrite(motor2speed, speed - 30);
}

void moveBackward(int speed)
{
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH); // Left motor backward
  analogWrite(motor1speed, speed);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH); // Right motor backward
  analogWrite(motor2speed, speed - 30);
}

void turnRight(int speed)
{
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW); // Left motor forward
  analogWrite(motor1speed, speed);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH); // Right motor backward
  analogWrite(motor2speed, speed);
}

void turnLeft(int speed)
{
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH); // Left motor backward
  analogWrite(motor1speed, speed);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW); // Right motor forward
  analogWrite(motor2speed, speed);
}

void stopMotors()
{
  analogWrite(motor1speed, 0); // Stop left motor
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  analogWrite(motor2speed, 0); // Stop right motor
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}
