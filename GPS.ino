#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int gpsRXPin = 4, gpsTXPin = 3;
static const uint32_t gpsBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial serialGPS(gpsRXPin, gpsTXPin);

// déclaration des variables
double gpsCourseToLondon;
static const double LONDON_LAT = 48.028194, LONDON_LON =5.446296;
//51.508131 -0.128002;
unsigned long gpsDistanceKmToLondon;
//double courseToLondon = courseToLondon;
double vitMoteurDroit ;
double vitMoteurGauche;

void gpsInit()
{
  serialGPS.begin(gpsBaud);
  }

void gpsLoop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (serialGPS.available() > 0)
    if (gps.encode(serialGPS.read()))
      //displayInfo();
    if (gps.location.isValid()) {
      gpsDir();
    }
     

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("GPS non détecté : vérifier le cablage."));
    while(true);
  }
  
}

void gpsDir()   {

gpsCourseToLondon =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON);

Serial.print ("Angle de direction: ");
Serial.print(gpsCourseToLondon) ; //, gps.location.isValid(), 7, 2);



if ((gpsCourseToLondon > 10) && (gpsCourseToLondon <180 )) { //on va vers la droite
  vitMoteurGauche = 100;
  vitMoteurDroit = 100 - (100*(gpsCourseToLondon/180));
  Serial.println("  ==> A droite");
  //digitalWrite (12, HIGH);
  //digitalWrite (11, LOW);
  }

if ((gpsCourseToLondon > 180) && (gpsCourseToLondon <350)) { //on va vers la gauche
  vitMoteurDroit = 100;
  vitMoteurGauche = 100 - (100*((360 - gpsCourseToLondon) / 180));
  Serial.println("  ==> A gauche");
  //digitalWrite (11, HIGH);
  //digitalWrite (12, LOW);
  }

if ((gpsCourseToLondon > 349) && (gpsCourseToLondon <11) ) { //on va tout droit
  vitMoteurDroit = 100;
  vitMoteurGauche = 100;
  Serial.println("  ==> Tout droit");
  //digitalWrite (11, HIGH);
  //digitalWrite (12, HIGH);
  }
Serial.print ("Vitesse droit = ");
Serial.print (vitMoteurDroit);
Serial.print ("   Vitesse gauche = ");
Serial.println (vitMoteurGauche);
  

}
