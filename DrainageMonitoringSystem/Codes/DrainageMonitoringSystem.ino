#include <WiFi.h>
#include <SPI.h> 
 // ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com"; //TS
String writeAPIKey = "8IAYE5HVTV7US8YT";       //TS
int updateThingSpeakInterval = 1 * 1000;      // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)
int status = WL_IDLE_STATUS;                 // the Wifi radio's status
const int analogIn = A0;
const int analogIn_1 = A1;
int RawValue= 0;
int RawValue_1= 0;
// initialize the library instance: 
WiFiClient client;
// Variable Setup
long lastConnectionTime = 0; 
boolean lastConnected = false;
int failedCounter = 0;

void setup()
{
  //Initialize serial and wait for port to open:
   Serial.begin(9600); 
   while (!Serial)
   {
    ; // wait for serial port to connect. Needed for Leonardo only
   }
  
   // you're connected now, so print out the data:
   Serial.print("You're connected to the network");
   printCurrentNet();
   printWifiData();
}


void loop() 
{
  // check the network connection once every 10 seconds:
  lastConnectionTime = 0;
  updateThingSpeakInterval = 1000;
  RawValue = analogRead(analogIn);
  RawValue_1 = analogRead(analogIn_1);
  String analogPin0 = String(RawValue);
  String analogPin_1 = String(RawValue_1);
 // Print Update Response to Serial Monitor
  if (client.available())
  {
    char c = client.read();
    Serial.print(c);
  }
   // Disconnect from ThingSpeak
  if (!client.connected() && lastConnected)
  {
    Serial.println("...disconnected");
    Serial.println();
    client.stop();
  }
  // Update ThingSpeak
  if(!client.connected() && (lastConnectionTime < updateThingSpeakInterval))
  {
      Serial.print("\t Amps = ");
      Serial.print(analogPin0);
      Serial.print(analogPin_1);
      updateThingSpeak("field2="+analogPin_1+"&field1="+analogPin0);
      delay(20000);
      client.stop();
  }
  lastConnected = client.connected();
}

void updateThingSpeak(String tsData)
{
  if (client.connect(thingSpeakAddress, 80))             //https://www.arduino.cc/en/Reference/WiFiClientConnect
  {         
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");

    client.print(tsData);
 
       lastConnectionTime = millis();
          Serial.println(lastConnectionTime);

        if (client.connected())
        {
         Serial.println("Connecting to ThingSpeak...");
         Serial.println();
         failedCounter = 0;
        }
        else
        {
          failedCounter++;
          Serial.println("Connection to ThingSpeak failed ("+String(failedCounter, DEC)+")");   
          Serial.println();
        }
   else
   {
     failedCounter++;
     Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");   
     Serial.println();
     lastConnectionTime = millis(); 
   }
  //lastConnectionTime = 0;
}

    
void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);
  
  // print your MAC address:
  byte mac[6];  
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
 
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);    
  Serial.print("BSSID: ");
  Serial.print(bssid[5],HEX);
  Serial.print(":");
  Serial.print(bssid[4],HEX);
  Serial.print(":");
  Serial.print(bssid[3],HEX);
  Serial.print(":");
  Serial.print(bssid[2],HEX);
  Serial.print(":");
  Serial.print(bssid[1],HEX);
  Serial.print(":");
  Serial.println(bssid[0],HEX);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption,HEX);
  Serial.println();
}s