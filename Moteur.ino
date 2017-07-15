// ---------------------------------------------------------------
// Fonctions moteurs


//Variables moteurs
//Motor A
int moteurPWMA = 6; //Speed control 
int moteurAIN1 = 7; //Direction
//Motor B
int moteurPWMB = 5; //Speed control
int moteurBIN1 = 4; //Direction



void moteurInit () {
//***** Création des contrôles moteurs
  pinMode(moteurPWMA, OUTPUT);
  pinMode(moteurAIN1, OUTPUT);
  pinMode(moteurPWMB, OUTPUT);
  pinMode(moteurBIN1, OUTPUT);
  
}

void moteurTest () {
  moteurMove (0, 100, 1);
  delay (200);
  moteurStop();
  moteurMove (1, 100, 1);
  delay (200);
  moteurStop();
}

void moteurMove(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  //digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(moteurAIN1, inPin1);
    //digitalWrite(AIN2, inPin2);
    analogWrite(moteurPWMA, speed);
  }else{
    digitalWrite(moteurBIN1, inPin1);
    //digitalWrite(BIN2, inPin2);
    analogWrite(moteurPWMB, speed);
  }
}

void moteurStop(){

    digitalWrite(moteurAIN1, LOW);
    digitalWrite(moteurBIN1, LOW);
    analogWrite(moteurPWMA, HIGH);
    analogWrite(moteurPWMB, HIGH);


}

void moteurJoyMove (int joyX, int joyY) {
  int sens = 0;
  if (joyY > 0) {
    sens = 1;
  }
  
  int X = map ((abs (joyX)), 0, 100, 15, 255);
  Serial.println ("X = " + X);
  int Y = map ((abs (joyY)), 0, 100, 15, 255);
  Serial.println ("Y = " + Y);

  int vTourne = (Y*(1-(X/100)));

  if (joyX > 0) {
    moteurMove (1, vTourne, sens);
    moteurMove (0, Y, sens);
  }

  if (joyX < 0) {
    moteurMove (0, vTourne, sens);
    moteurMove (1, Y, sens);
  }
  
}

