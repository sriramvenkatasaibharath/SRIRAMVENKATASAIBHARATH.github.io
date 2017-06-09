#include <WiFi.h>
#include <SPI.h> 
 // ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";  //TS
String writeAPIKey = "TMFOBAXD7BZ3JWFI";//TS
int updateThingSpeakInterval = 1 * 1000;      // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)
int status = WL_IDLE_STATUS;     // the Wifi radio's status
const int analogIn = A0;
const int analogIn_1 = A1;
int mVperAmp = 100; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int RawValue_1= 0;
int ACSoffset = 2500; 
double Voltage = 0;
double Voltage_1 = 0;
double Amps = 0;
double Amps_1 = 0;
int power =0;
int power_1 =0;
// initialize the library instance: 
WiFiClient client;
// Variable Setup
long lastConnectionTime = 0; 
boolean lastConnected = false;
int failedCounter = 0;
int a;
int B=3975; 
float ctemp;
float res;

void setup() {
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

void loop() {
  // check the network connection once every 10 seconds:
  lastConnectionTime = 0;
  updateThingSpeakInterval = 1000;
  RawValue = analogRead(analogIn);
  RawValue_1 = analogRead(analogIn_1);
     Voltage = ((RawValue /1024.0) * 5000); // Gets you mV
     Voltage_1 = ((RawValue_1 /1024.0) * 5000);
     Amps = ((Voltage - ACSoffset) / mVperAmp);
     Amps_1 = ((Voltage_1 - ACSoffset) / mVperAmp);
    // Serial.println("Amps: ");
    // Serial.println(Amps);
   //  delay(1000);
  //res=(float)(1023-a)*10000/a; 
  //ctemp=1/(log(res/10000)/B+1/298.15)-273.15;
  power = 230 * (Amps*11);
  power_1 = 230 * (Amps_1*11.2);
  if(power < 0)
  {
    power = -power;
  }
  if(power_1 < 0)
  {
    power_1 = -power_1;
  }
//  Serial.println(power);

   String analogPin0 = String(power);
   String analogPin_1 = String(power_1);
  //(ctemp*100), DEC);
  
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
      Serial.print("\n");
      Serial.print("Sensor 1");
      Serial.print(analogPin0);
      Serial.print("\t");
      Serial.print((Voltage)/11.2,3);
      Serial.print("mV");
      Serial.print("\t");
      Serial.print(Amps,3);
      Serial.print("Amps");
      Serial.print("\t");
      Serial.print("POWER  ");
      Serial.print(power);
      Serial.print("\n");
      Serial.print("Sensor 2");
      Serial.print(analogPin_1);
      Serial.print("\t");
      Serial.print((Voltage_1)/11.2,3);
      Serial.print("mV");  
      Serial.print("\t");
      Serial.print(Amps_1,3);
      Serial.print("Amps");
      Serial.print("\t");
      Serial.print("POWER  ");
      Serial.print(power_1);

      updateThingSpeak("field2="+analogPin_1+"&field1="+analogPin0);
      
      delay(20000);
    //  updateThingSpeak("field1="+analogPin0);
     // delay(20000);
      
      client.stop();
  }
  
  lastConnected = client.connected();
 
}

void updateThingSpeak(String tsData)
{
  if (client.connect(thingSpeakAddress, 80))
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
  //  client.print(tsData_1);
    
    lastConnectionTime = millis();
          Serial.println("Last Connection Time\t");
          Serial.print(lastConnectionTime);

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
}
