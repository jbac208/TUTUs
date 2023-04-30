#include <Servo.h>

#define MOTOR_LEFT_DIRECTION      8
#define MOTOR_LEFT_SPEED          9
#define MOTOR_RIGHT_DIRECTION     11
#define MOTOR_RIGHT_SPEED         10

#define SERVO                     13

#define SERVO_DOWN_POS            180
#define SERVO_UP_POS              0

Servo servo;


void setup() {
  // put your setup code here, to run once:
  servo.attach(SERVO);

  pinMode(MOTOR_LEFT_DIRECTION, OUTPUT);
  pinMode(MOTOR_LEFT_SPEED, OUTPUT);
  pinMode(MOTOR_RIGHT_DIRECTION, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  // turn around 90
  digitalWrite(MOTOR_LEFT_DIRECTION, 1);
  digitalWrite(MOTOR_RIGHT_DIRECTION, 0);
  analogWrite(MOTOR_LEFT_SPEED, 255);
  analogWrite(MOTOR_RIGHT_SPEED, 255);
  delay(80);

  analogWrite(MOTOR_LEFT_SPEED, 0);
  analogWrite(MOTOR_RIGHT_SPEED, 0);

  for (int i = SERVO_DOWN_POS; i > 0; i--) {
    servo.write(i);
    delay(10);
  }
  delay(400);

  // forwards
  digitalWrite(MOTOR_RIGHT_DIRECTION, 1);
  analogWrite(MOTOR_LEFT_SPEED, 255);
  analogWrite(MOTOR_RIGHT_SPEED, 255);
  delay(150);

  // turn 90
  digitalWrite(MOTOR_RIGHT_DIRECTION, 0);
  analogWrite(MOTOR_LEFT_SPEED, 255);
  analogWrite(MOTOR_RIGHT_SPEED, 255);
  delay(80);

  digitalWrite(MOTOR_RIGHT_DIRECTION, 1);
  analogWrite(MOTOR_LEFT_SPEED, 255);
  analogWrite(MOTOR_RIGHT_SPEED, 255);
  delay(500);
}
