#include <Servo.h>

#define LEFT_LINE_SENSOR          8
#define MIDDLE_LINE_SENSOR        9
#define RIGHT_LINE_SENSOR         10

#define MOTOR_LEFT_DIRECTION      4
#define MOTOR_LEFT_SPEED          5
#define MOTOR_RIGHT_DIRECTION     7
#define MOTOR_RIGHT_SPEED         6

#define SERVO_LEFT                2
#define SERVO_RIGHT               3

// States
#define STATE_WAIT                0
#define STATE_DELIVERY            1
#define STATE_RETURN              2

// Delivery Sub-States
#define DELIVERY_STATE_DOWN       0
#define DELIVERY_STATE_PICK       1
#define DELIVERY_STATE_UP         2
#define DELIVERY_STATE_DROP       3

// Standard servo angles
#define LEFT_SERVO_STANDARD_POS   20
#define RIGHT_SERVO_STANDARD_POS  120

Servo  leftServo;
Servo  rightServo;

int nRobotState = STATE_WAIT;               // initial robot state
int nDeliveryState = DELIVERY_STATE_DOWN;   // initial delivery state
int lineCount = 4;

int lineTracer() {
  // line tracer algo
  int output = 2;

  if (digitalRead(LEFT_LINE_SENSOR)) {  // left most sensor
    if (digitalRead(MIDDLE_LINE_SENSOR)) {  // middle sensor
      if (digitalRead(RIGHT_LINE_SENSOR)) {  // right most sensor
        // 111 forwards
        output = 0;
      }
      else {
        // 110 slight left
        output = 1;
      }
    }
    else {
      if (digitalRead(RIGHT_LINE_SENSOR)) {  // right most sensor
        // 101 forwards
        output = 2;
      }
      else {
        // 100 hard left
        output = 1;
      }
    }
  }
  else {
    if (digitalRead(MIDDLE_LINE_SENSOR)) {  // middle sensor
      if (digitalRead(RIGHT_LINE_SENSOR)) {  // right most sensor
        // 011 slight right
        output = 3;
      }
      else {
        // 010 forwards
        output = 2;
      }
    }
    else {
      if (digitalRead(RIGHT_LINE_SENSOR)) {  // right most sensor
        // 001 hard right
        output = 3;
      }
      else {
        // 000 forwards
        output = 2;
      }
    }
  }
  delay(200);   // if line mulit counting for single line then increase this delay
  return output;
}

void motorControl(int dir) {
  switch (dir) {
    case 1:
      // turn left
      Serial.println("LEFT");
      digitalWrite(MOTOR_LEFT_DIRECTION, 0);
      digitalWrite(MOTOR_RIGHT_DIRECTION, 1);
      analogWrite(MOTOR_LEFT_SPEED, 255);
      analogWrite(MOTOR_RIGHT_SPEED, 255);
      break;

    case 2:
      // go straight
      Serial.println("MIDDLE");
      digitalWrite(MOTOR_LEFT_DIRECTION, 1);
      digitalWrite(MOTOR_RIGHT_DIRECTION, 1);
      analogWrite(MOTOR_LEFT_SPEED, 255);
      analogWrite(MOTOR_RIGHT_SPEED, 255);
      break;

    case 3:
      // turn right
      Serial.println("RIGHT");
      digitalWrite(MOTOR_LEFT_DIRECTION, 1);
      digitalWrite(MOTOR_RIGHT_DIRECTION, 0);
      analogWrite(MOTOR_LEFT_SPEED, 255);
      analogWrite(MOTOR_RIGHT_SPEED, 255);
      break;

    case 0:
      if (nDeliveryState == DELIVERY_STATE_DOWN) {
        nDeliveryState = DELIVERY_STATE_PICK;
      }
      else if (nDeliveryState == DELIVERY_STATE_UP) {
        // count and stop
        Serial.println(lineCount);
        lineCount--;
        if (lineCount == 0) {
          nDeliveryState = DELIVERY_STATE_DROP;
        }
      }
      break;
  }
}

void dropOff() {
  leftServo.write(LEFT_SERVO_STANDARD_POS +/- ?);
  rightServo.write(RIGHT_SERVO_STANDARD_POS +/- ?);
  delay(1000);
  leftServo.write(LEFT_SERVO_STANDARD_POS);
  rightServo.write(RIGHT_SERVO_STANDARD_POS);
  delay(500);
}

void wait() {
  Serial.println("wait");
  if (digitalRead(LEFT_LINE_SENSOR)) {
    nRobotState = STATE_DELIVERY;
  }
  delay(1000);
}

void delivery() {
  switch (nDeliveryState) {
    case DELIVERY_STATE_DOWN:
      Serial.println("DOWN");
      // down condition in motorControl()
      motorControl(lineTracer());
      break;

    case DELIVERY_STATE_PICK:
      Serial.println("PICK");
      // pickUp function
      nDeliveryState = DELIVERY_STATE_UP;
      break;

    case DELIVERY_STATE_UP:
      Serial.println("UP");
      // up condition in motorControl()
      motorControl(lineTracer());
      break;

    case DELIVERY_STATE_DROP:
      Serial.println("DROP");
      // dropOff function

      nRobotState = STATE_RETURN;
      break;
  }
}

void returnHome() {
  //  180 turn
  digitalWrite(MOTOR_LEFT_DIRECTION, 1);
  digitalWrite(MOTOR_RIGHT_DIRECTION, 0);
  analogWrite(MOTOR_LEFT_SPEED, 255);
  analogWrite(MOTOR_RIGHT_SPEED, 255);
  delay(300);   // if not 180 turn, modify this delay accordingly
  
  // linetracer back
  motorControl(lineTracer());
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  leftServo.attach(SERVO_LEFT);
  rightServo.attach(SERVO_RIGHT);

  pinMode(MOTOR_LEFT_DIRECTION, OUTPUT);
  pinMode(MOTOR_LEFT_SPEED, OUTPUT);
  pinMode(MOTOR_RIGHT_DIRECTION, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED, OUTPUT);

  pinMode(LEFT_LINE_SENSOR, INPUT);
  pinMode(MIDDLE_LINE_SENSOR, INPUT);
  pinMode(RIGHT_LINE_SENSOR, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  switch (nRobotState) {
    case STATE_WAIT:
      Serial.println("state wait");
      wait();
      break;

    case STATE_DELIVERY:
      Serial.println("state delivery");
      delivery();
      break;

    case STATE_RETURN:
      Serial.println("state return");
      returnHome();
      break;
  }
}
