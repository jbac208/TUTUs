#define MOTOR_LEFT_DIRECTION      8
#define MOTOR_LEFT_SPEED          9
#define MOTOR_RIGHT_DIRECTION     11
#define MOTOR_RIGHT_SPEED         10



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(MOTOR_LEFT_DIRECTION, OUTPUT);
  pinMode(MOTOR_LEFT_SPEED, OUTPUT);
  pinMode(MOTOR_RIGHT_DIRECTION, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(MOTOR_LEFT_DIRECTION, 1);
  digitalWrite(MOTOR_RIGHT_DIRECTION, 1);
  analogWrite(MOTOR_LEFT_SPEED, 55);
  analogWrite(MOTOR_RIGHT_SPEED, 55);
  
}
