#include<Servo.h>

#define SERVO_DOWN_POS   180
#define SERVO_UP_POS     0

#define SERVO            11

#define MOTOR_LEFT_DIRECTION      4
#define MOTOR_LEFT_SPEED          5
#define MOTOR_RIGHT_DIRECTION     7
#define MOTOR_RIGHT_SPEED         6

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

  digitalWrite(MOTOR_LEFT_DIRECTION, 0);
  digitalWrite(MOTOR_RIGHT_DIRECTION, 1);
  analogWrite(MOTOR_LEFT_SPEED, 255);
  analogWrite(MOTOR_RIGHT_SPEED, 255);
  delay(700);
  
  analogWrite(MOTOR_LEFT_SPEED, 0);
  analogWrite(MOTOR_RIGHT_SPEED, 0);
  // claw going down
  for (int i = SERVO_DOWN_POS; i > 0; i--) {
    servo.write(i);
    delay(10);
  }
  delay(400);

  digitalWrite(MOTOR_RIGHT_DIRECTION, 0);
  analogWrite(MOTOR_LEFT_SPEED, 255);
  analogWrite(MOTOR_RIGHT_SPEED, 255);
  delay(500);

  analogWrite(MOTOR_LEFT_SPEED, 0);
  analogWrite(MOTOR_RIGHT_SPEED, 0);
  // claw going up
  for (int i = SERVO_UP_POS; i < 180; i++) {
    servo.write(i);
    delay(10);
  }
  
}
