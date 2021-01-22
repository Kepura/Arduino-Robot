#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

const int leftSensor = 10;
const int centerSensor = 4;
const int rightSensor = 2;
bool leftSensorState;
bool centerSensorState;
bool rightSensorState;

void setup() {
  Serial.begin(9600);

  pinMode(IN1,OUTPUT); 
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  pinMode(leftSensor,  INPUT);
  pinMode(centerSensor,  INPUT);
  pinMode(rightSensor,  INPUT);
}

void forward() {
  digitalWrite(ENA, HIGH); 
  digitalWrite(ENB, HIGH); 
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, LOW);  
  digitalWrite(IN4, HIGH); 
}

void left() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void right() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void back() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);   
}

void loop() {
  leftSensorState = digitalRead(leftSensor);
  centerSensorState = digitalRead(centerSensor);
  rightSensorState = digitalRead(rightSensor);

  if(!centerSensorState) {
    if ((leftSensorState) && (!rightSensorState)) {
        left();
    } else if ((!leftSensorState) && (rightSensorState)) {
        right();
    } else {
        forward();
    }
  } else {
    if ((leftSensorState) && (!rightSensorState)) {
        left();
    } else if ((!leftSensorState) && (rightSensorState)) {
        right();
    } else {
        stop();
    }
  }
}