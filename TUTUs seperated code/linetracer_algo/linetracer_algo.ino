#define LEFT_LINE_SENSOR          2
#define MIDDLE_LINE_SENSOR        3
#define RIGHT_LINE_SENSOR         4

#define MOTOR_LEFT_DIRECTION      8
#define MOTOR_LEFT_SPEED          9
#define MOTOR_RIGHT_DIRECTION     11
#define MOTOR_RIGHT_SPEED         10

#define STATE_WAIT                0
#define STATE_DELIVERY            1

int lineCount = 4;
int nRobotState = STATE_DELIVERY;

int lineTracer() {
  // line tracer algo for black line on white background
  int output = 2;

  if (digitalRead(LEFT_LINE_SENSOR)) {  // left most sensor
    if (digitalRead(MIDDLE_LINE_SENSOR)) {  // middle sensor
      if (digitalRead(RIGHT_LINE_SENSOR)) {  // right most sensor
        // 111 forwards
        output = 2;
      }
      else {
        // 110 hard right
        output = 3;
      }
    }
    else {
      if (digitalRead(RIGHT_LINE_SENSOR)) {  // right most sensor
        // 101 forwards
        output = 2;
      }
      else {
        // 100 slight right
        output = 3;
      }
    }
  }
  else {
    if (digitalRead(MIDDLE_LINE_SENSOR)) {  // middle sensor
      if (digitalRead(RIGHT_LINE_SENSOR)) {  // right most sensor
        // 011 hard left
        output = 1;
      }
      else {
        // 010 forwards
        output = 2;
      }
    }
    else {
      if (digitalRead(RIGHT_LINE_SENSOR)) {  // right most sensor
        // 001 slight left
        output = 1;
      }
      else {
        // 000 all not detected
        output = 0;
      }
    }
  }
  delay(50);   // if line multi counting for single line then increase this delay
  return output;
}

void motorControl(int dir) {

  switch (dir) {
    case 1:
      // turn left
      Serial.println("LEFT");
      digitalWrite(MOTOR_LEFT_DIRECTION, 0);
      digitalWrite(MOTOR_RIGHT_DIRECTION, 1);
      analogWrite(MOTOR_LEFT_SPEED, 45);
      analogWrite(MOTOR_RIGHT_SPEED, 45);
      break;

    case 2:
      // go straight
      Serial.println("MIDDLE");
      digitalWrite(MOTOR_LEFT_DIRECTION, 1);
      digitalWrite(MOTOR_RIGHT_DIRECTION, 1);
      analogWrite(MOTOR_LEFT_SPEED, 45);
      analogWrite(MOTOR_RIGHT_SPEED, 45);
      break;

    case 3:
      // turn right
      Serial.println("RIGHT");
      digitalWrite(MOTOR_LEFT_DIRECTION, 1);
      digitalWrite(MOTOR_RIGHT_DIRECTION, 0);
      analogWrite(MOTOR_LEFT_SPEED, 45);
      analogWrite(MOTOR_RIGHT_SPEED, 45);
      break;

    case 0:
      // count and stop
      Serial.println(lineCount);
      lineCount--;
      if (lineCount == 0) {
        nRobotState = STATE_WAIT;
      }
      break;
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR_LEFT_DIRECTION, OUTPUT);
  pinMode(MOTOR_LEFT_SPEED, OUTPUT);
  pinMode(MOTOR_RIGHT_DIRECTION, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED, OUTPUT);

  pinMode(LEFT_LINE_SENSOR, INPUT);
  pinMode(MIDDLE_LINE_SENSOR, INPUT);
  pinMode(RIGHT_LINE_SENSOR, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 /* switch (nRobotState) {
    case STATE_DELIVERY:
      motorControl(lineTracer());
      Serial.println("line track");

    case STATE_WAIT:
      Serial.println("Wait");
      analogWrite(MOTOR_LEFT_SPEED, 0);
      analogWrite(MOTOR_RIGHT_SPEED, 0);
  }*/
  motorControl(lineTracer());
}
