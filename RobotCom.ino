



void setup() {
  
  Serial.begin(115200);
  Serial.println("Debut du test");

	gyroInit();
	
  moteurInit();
  moteurTest();

  BTInit();

  gpsInit();

  }


void loop() {

	gyroData();
  
  //Pour débug, affichage des données du gyro:
	gyroDataPrint();

  BTLoop();

  uSonMesure();

  }
