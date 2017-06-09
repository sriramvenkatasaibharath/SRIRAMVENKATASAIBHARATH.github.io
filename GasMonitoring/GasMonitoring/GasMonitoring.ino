#include<String.h>
const int sensepin= A0;
const int threshold=50;//threshold Weight for Gas cylinder
int reading;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//initialisation for client communication
  Serial1.begin(115200);//initialisation serial communication with GSM shield
  delay(100);

}
void loop()
{
  // put your main code here, to run repeatedly:
  reading = analogRead(sensepin);//to read the value from the sensor
  Serial.println(reading);//to print the values from sensor 
  if (reading > threshold)
{
  Serial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial1.println("AT+CMGS=\"+919789950995\"\r"); // Replace x with mobile number
  delay(1000);
  Serial1.println("   Cylinder status\nYour Gas is under treshold Limit\n Please Book for Cylinder\nThank you..Intel Galelio Gen 2");// The SMS text you want to send
  delay(100);
  Serial1.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
/*if(Serial1.available())
   {
   Serial.write(Serial1.read());
     delay(10000);
   }*/

}

