#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

const int capteurGauche = 10;
const int capteurCentre = 4;
const int capteurDroit = 2;
bool etatCapteurGauche;
bool etatCapteurCentre;
bool etatCapteurDroit;

void setup() {
  Serial.begin(9600);

  pinMode(IN1,OUTPUT); 
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  pinMode(capteurGauche,  INPUT);
  pinMode(capteurCentre,  INPUT);
  pinMode(capteurDroit,  INPUT);
}

void avancer() {
  digitalWrite(ENA, HIGH); 
  digitalWrite(ENB, HIGH); 
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, LOW);  
  digitalWrite(IN4, HIGH); 
}

void gauche() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void droite(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void reculer(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void arreter() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);   
}

void loop() {
  etatCapteurGauche = digitalRead(capteurGauche);
  etatCapteurCentre = digitalRead(capteurCentre);
  etatCapteurDroit = digitalRead(capteurDroit);

  if(!etatCapteurCentre) {
    if ((etatCapteurGauche) && (!etatCapteurDroit))
    gauche();
    else if ((!etatCapteurGauche) && (etatCapteurDroit))
    droite();
    else 
    avancer();

  } else {

    if ((etatCapteurGauche) && (!etatCapteurDroit))
    gauche();
    else if ((!etatCapteurGauche) && (etatCapteurDroit))
    droite();
    else
    reculer();
  }
}