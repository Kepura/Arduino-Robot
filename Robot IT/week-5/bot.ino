#include <Servo.h>

/* Voir table de vérités pour comprendre quelle variable correspond a quel roue / axe */
#define ENA 5
#define ENB 6 
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

/* Déclarations des constantes de types int qui représentent les PIN des différents capteurs*/
const int leftSensor = 10;
const int centerSensor = 4;
const int rightSensor = 2;
int servoState = 0;

/* Déclaration des variables booleans déstinées à la vérification de l'état des capteurs*/
bool leftSensorState;
bool centerSensorState;
bool rightSensorState;

const byte TRIGGER = 5; // broche TRIGGER
const byte ECHO = 4; // broche ECHO
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = 8m à 340m/s
const float SOUND_SPEED = 340.0 / 1000;
const boolean plot = false;

Servo myServo;

/* Fonction setup basique à ARDUINO */
void setup() {
    Serial.begin(115200);

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    pinMode(leftSensor, INPUT);
    pinMode(centerSensor, INPUT);
    pinMode(rightSensor, INPUT);

    myServo.attach(3);
    myServo.write(servoState);

    pinMode(TRIGGER, OUTPUT);
    digitalWrite(TRIGGER, LOW);
    pinMode(ECHO, INPUT);
}

void loop() {
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  
  long measure = pulseIn(ECHO, HIGH, MEASURE_TIMEOUT);
  
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  Serial.println("Distance: ");
  Serial.print(distance_mm);
  Serial.print("cm, ");
  
  if (distance_mm > 65) {
    lineFollower();
  } else {
    Stop();
    servo(180);
  }
  delay(300);
}

void lineFollower() {
    leftSensorState = digitalRead(leftSensor);
    centerSensorState = digitalRead(centerSensor);
    rightSensorState = digitalRead(rightSensor);

    if (!centerSensorState) {
        if ((leftSensorState) && (!rightSensorState)) {
            left(6);
        } else if ((!leftSensorState) && (rightSensorState)) {
            right(4);
        } else {
            forward(7);
        }
    } else {
        if ((leftSensorState) && (!rightSensorState)) {
            left(4);
        } else if ((!leftSensorState) && (rightSensorState)) {
            right(6);
        } else {
            Stop();
        }
    }
}

void servo(int x) {
  for(servoState = 0; servoState <= x; servoState++) {
      myServo.write(servoState);
      delay(5);
    }
    
    for(servoState = x; servoState >= 0; servoState--) {
      myServo.write(servoState);
      delay(5);
    }
}

/* Fonction assurant l'avancer du robot */
void forward(int Power) {
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, Power);
    analogWrite(ENB, Power);
}

/* Fonction permettant au robot de tourner a gauche */
void left(int Power) {
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, Power);
    analogWrite(ENB, Power);
}

/* Fonction permettant au robot de tourner a droite*/
void right(int Power) {
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, Power);
    analogWrite(ENB, Power);
}

/* Fonction assurant la marche arrière du robot */
void back(int Power) {
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, Power);
    analogWrite(ENB, Power);
}

/* Fonction assurant l'arrêt du robot */
void Stop() {
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
