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

/* Déclaration des variables booleans déstinées à la vérification de l'état des capteurs*/
bool leftSensorState;
bool centerSensorState;
bool rightSensorState;

/* Fonction setup basique à ARDUINO */
void setup() {
    Serial.begin(9600);

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    pinMode(leftSensor, INPUT);
    pinMode(centerSensor, INPUT);
    pinMode(rightSensor, INPUT);
}

/* Fonction loop basique à ARDUINO */
void loop() {
    leftSensorState = digitalRead(leftSensor);
    centerSensorState = digitalRead(centerSensor);
    rightSensorState = digitalRead(rightSensor);

    if (!centerSensorState) {
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
            back();
        }
    }
}

/* Fonction assurant l'avancer du robot */
void forward() {
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

/* Fonction permettant au robot de tourner a gauche */
void left() {
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

/* Fonction permettant au robot de tourner a droite*/
void right() {
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

/* Fonction assurant la marche arrière du robot */
void back() {
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

/* Fonction assurant l'arrêt du robot */
void stop() {
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
