/* Capteur ultrason makeblock
pour brancher sur port 3 de la carte == pin 13 arduino

*/
int uSonLastEnterTime = millis();
int uSonMeasureFlag = true;
int uSonMeasureValue = 0;
int uSonPin = 13;
long uSonDuration;
double uSonMAXcm = 400;
unsigned long uSonTimeout = (uSonMAXcm * 55 + 200);


void uSonMesure()
{

	if (millis() - uSonLastEnterTime > 23)
	{
		uSonMeasureFlag = true;
	}

	if (uSonMeasureFlag == true)
	{
		uSonLastEnterTime = millis();
		uSonMeasureFlag = false;
		uSonPinWrite(LOW);
		delayMicroseconds(2);
		uSonPinWrite(HIGH);
		delayMicroseconds(10);
		uSonPinWrite(LOW);
		pinMode(uSonPin, INPUT);
		uSonDuration = pulseIn(uSonPin, HIGH, uSonTimeout);
		uSonMeasureValue = uSonDuration;
	}
	else
	{
		uSonDuration = uSonMeasureValue;
	}
	
	long uSonDistance = uSonDuration;
	if (uSonDistance == 0)
	{
		uSonDistance = uSonMAXcm * 58;
	}
	uSonDistance = uSonDistance / 58;
	Serial.print("Distance : ");
	Serial.println(uSonDistance); // / 58.0);


	delay(300); /* l'interval minimum de mesure est de 100 milliseconds */
}



void uSonPinWrite(bool value)
{
	pinMode(uSonPin, OUTPUT);
	digitalWrite(uSonPin, value);
}
