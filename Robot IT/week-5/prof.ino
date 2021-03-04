//DECLARATION DU SERVOMOTEUR
#include <Servo.h>  	// Activation bibliotheque du servomoteur
Servo monservo;     	//Création de l'objet servo

//DECLARATION DE VARIABLES UTILISEES DANS LE PROGRAMME
int VMax=200; 	//valeur de la vitesse maxi des moteurs
int Vmin=50;  	//valeur de la vitesse mini des moteurs
int Vma=90;   	//valeur d la vitesse de marche arrière
int D=10;     	//distance d'arret au plot en cm

//DÉCLARATIONS DES MOTEURS 
int moteurGaucheA = 7;  	//moteurs gauches marche avant
int moteurGaucheR = 8;  	//moteurs gauches marche arriere
int moteurDroitA = 11;  	//moteurs droits marche avant
int moteurDroitR = 9;  		//moteurs droits marche arriere
int vitesseG = 5;      	 	//variable de vitesse moteurs gauche
int vitesseD = 6;       		//variable de vitesse moteur de droite

//DÉCLARATIONS DES CAPTEURS DE LUMINOSITÉ (pour le suivi de ligne)
const int capteurGauche = 10;
const int capteurCentre = 4;
const int capteurDroit = 2;
bool etatCapteurGauche;
bool etatCapteurCentre;
bool etatCapteurDroit;

//DECLARATION DU CAPTEUR ULTRASON (pour la mesure de distance)
int recepteur = A4; 	//Recepteur ultrason
int emetteur = A5;  	//Emetteur ultrason
int distanceAvant;  	//Mesure de la distance libre devant le robot (ARRONDI)
float intervalle;   	//Variable réelle mesurée (EXACTE)

//INITIALISATION DU ROBOT
void setup() {

//Initialisation du servomoteur
  monservo.attach(3);
  monservo.write(0);  //Mise en position initiale du servo (angle à 0)
  
//Initialisation du capteur ULTRASON 
  pinMode(recepteur, INPUT);
  pinMode(emetteur, OUTPUT);
  
//Initialisation des broches des moteurs
  pinMode(moteurGaucheA, OUTPUT);
  pinMode(moteurGaucheR, OUTPUT);
  pinMode(moteurDroitA, OUTPUT);
  pinMode(moteurDroitR, OUTPUT);
  pinMode(vitesseG, OUTPUT);
  pinMode(vitesseD, OUTPUT);
  digitalWrite(moteurGaucheA, LOW);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, LOW);
  digitalWrite(moteurDroitR, LOW);

 //Initialisation des capteurs de ligne
  pinMode(capteurGauche, INPUT);
  pinMode(capteurCentre, INPUT);
  pinMode(capteurDroit, INPUT);
}


//SOUS PROGRAMMES DEPLACEMENTS 
void avancer()
{
    analogWrite (vitesseG,VMax);    //Reglage de la vitesse
    analogWrite (vitesseD,VMax);    //Reglage de la vitesse
  digitalWrite(moteurGaucheA, HIGH);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, HIGH);
  digitalWrite(moteurDroitR, LOW);
}

void gauche()
{
    analogWrite (vitesseG,Vmin);    //Reglage de la vitesse
    analogWrite (vitesseD,VMax);    //Reglage de la vitesse
  digitalWrite(moteurGaucheA, HIGH);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, HIGH);
  digitalWrite(moteurDroitR, LOW);
}
void droite()
{
    analogWrite (vitesseG,VMax);    //Reglage de la vitesse
    analogWrite (vitesseD,Vmin);    //Reglage de la vitesse
  digitalWrite(moteurGaucheA, HIGH);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, HIGH);
  digitalWrite(moteurDroitR, LOW);
 }
void reculer()
{
     analogWrite (vitesseG,Vma);    //Reglage de la vitesse
     analogWrite (vitesseD,Vma);    //Reglage de la vitesse
  digitalWrite(moteurGaucheA, LOW);
  digitalWrite(moteurGaucheR, HIGH);
  digitalWrite(moteurDroitA, LOW);
  digitalWrite(moteurDroitR, HIGH);
}
void arreter()
{
  digitalWrite(moteurGaucheA, LOW);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, LOW);
  digitalWrite(moteurDroitR, LOW);
 }

//SOUS PROGRAMME DETECTION OBSTACLE 
void mesurerDistanceAvant()
{
  digitalWrite(emetteur, LOW);            //Arret emmeteur sonore
  delayMicroseconds(2);                   //Attend 2 millisecondes
  digitalWrite(emetteur, HIGH);           //Envoi d'une onde sonore
  delayMicroseconds(10);                  //Attend 10 millisecondes
  digitalWrite(emetteur, LOW);
  intervalle = pulseIn(recepteur, HIGH);  //Réception de l'écho
  intervalle = intervalle/5.8/10;         //Conversion de la différence de temps entre l'envoie de l'onde sonore et la réception de l'écho distance en cm
  distanceAvant = intervalle;             //Met en memoire et arrondi la mesure de la distance 
}
  


//SOUS PROGRAMME SUIVIE DE LIGNE
void suivideligne(){
  etatCapteurGauche = digitalRead(capteurGauche);
  etatCapteurCentre = digitalRead(capteurCentre);
  etatCapteurDroit = digitalRead(capteurDroit);

if(!etatCapteurCentre)                                    //Si le capteur du centre détecte du noir
  {
    if ((etatCapteurGauche) && (!etatCapteurDroit))       //S'il y a du noir à gauche et du blanc à droite, tourner à gauche
    gauche();
    else if ((!etatCapteurGauche) && (etatCapteurDroit))  //S'il y a du blanc à gauche et du noir à droite, tourner à droite
    droite();
    else                                                  //Si les conditions plus haut ne s'appliquent pas, continuer tout droit
    avancer();
  }
 else                                                     //Si le capteur du centre détecte du blanc
 {
    if ((etatCapteurGauche) && (!etatCapteurDroit))       //S'il y a du noir à gauche et du blanc à droite, tourner à gauche
    gauche();
    else if ((!etatCapteurGauche) && (etatCapteurDroit))  //S'il y a du blanc à gauche et du noir à droite, tourner à droite
    droite();
    else                                                  //Si les conditions plus haut ne s'appliquent pas, reculer
    reculer();
  }

}



//PROGRAMME PRINCIPAL
void loop() {
 mesurerDistanceAvant();
   if (distanceAvant >D)    	//si distance avant > à la distance d'arret en cm
   suivideligne();          	//Lancer le programme de suivi de ligne
   else
   arreter();
   if (distanceAvant <=D)  	//si distance avant <= à la distance d'arret en cm
   monservo.write(120);    	 //Faire tourner le servo de 120°
}
