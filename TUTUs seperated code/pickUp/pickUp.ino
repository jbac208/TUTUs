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
  Serial.begin(9600);
  servo.attach(SERVO);

  pinMode(MOTOR_LEFT_DIRECTION, OUTPUT);
  pinMode(MOTOR_LEFT_SPEED, OUTPUT);
  pinMode(MOTOR_RIGHT_DIRECTION, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("forwards");
  digitalWrite(MOTOR_LEFT_DIRECTION, 1);
  digitalWrite(MOTOR_RIGHT_DIRECTION, 1);
  analogWrite(MOTOR_LEFT_SPEED, 255);
  analogWrite(MOTOR_RIGHT_SPEED, 255);
  delay(250);

  // turn around 180
  Serial.println("180 turn");
  digitalWrite(MOTOR_LEFT_DIRECTION, 1);
  digitalWrite(MOTOR_RIGHT_DIRECTION, 0);
  analogWrite(MOTOR_LEFT_SPEED, 255);
  analogWrite(MOTOR_RIGHT_SPEED, 255);
  delay(270);

  Serial.println("stop");
  analogWrite(MOTOR_LEFT_SPEED, 0);
  analogWrite(MOTOR_RIGHT_SPEED, 0);

  Serial.println("claw down");
  // claw going down
  for (int i = SERVO_DOWN_POS; i > 0; i--) {
    servo.write(i);
    delay(10);
  }
  delay(400);

  Serial.println("backwards");
  // go backwards
  digitalWrite(MOTOR_LEFT_DIRECTION, 0);
  analogWrite(MOTOR_LEFT_SPEED, 255);
  analogWrite(MOTOR_RIGHT_SPEED, 255);
  delay(800);

  Serial.println("Stop");
  analogWrite(MOTOR_LEFT_SPEED, 0);
  analogWrite(MOTOR_RIGHT_SPEED, 0);

  Serial.println("claw up");
  // claw goin up
  for (int i = SERVO_UP_POS; i < 180; i++) {
    servo.write(i);
    delay(10);
  }
  delay(400);

  Serial.println("forwards");
  digitalWrite(MOTOR_LEFT_DIRECTION, 1);
  digitalWrite(MOTOR_RIGHT_DIRECTION, 1);
  analogWrite(MOTOR_LEFT_SPEED, 255);
  analogWrite(MOTOR_RIGHT_SPEED, 255);
  delay(750);
}
