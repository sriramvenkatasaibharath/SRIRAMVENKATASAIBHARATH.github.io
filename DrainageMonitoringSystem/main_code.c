#include<stdlib.h>
#include "DHT.h"

//-----ESP8266 macros---------
#define SSID "------"//your network name
#define PASS "------"//your network password
#define IP "184.106.153.149" // thingspeak.com
#define Baud_Rate 9600 //Another common value is 115200
#define GREEN_LED 3 //optional LED's for debugging
#define RED_LED 4 //optional LED's for debugging
#define YELLOW_LED 5 //optional LED's for debugging
#define ESP_FOUND_LED 6 //optional LED's for debugging
#define DELAY_TIME 3000 //time in ms between posting data to ThingSpeak

//Can use a post also
String GET = "GET /update?key=------";
//String FIELD1 = "&field1=";
String FIELD2 = "&field2=";
String FIELD3 = "&field3=";

bool updated;

//----Relay/MQ-7 macros
#define RELAY 8
#define MQ7_ANALOG_IN_PIN 0
#define HEATING_LED 9
#define READING_LED 10
#define BUZZER 11

#define MQ7_HEATER_5_V_TIME_MILLIS 60000
#define MQ7_HEATER_1_4_V_TIME_MILLIS 90000
#define GAS_LEVEL_READING_PERIOD_MILLIS 1000

unsigned long startMillis;
unsigned long switchTimeMillis;
unsigned int gasLevel;
boolean heaterInHighPhase;

//----Temperature sensor macros
#define DHTPIN 7     // what pin the DHT sensor is connected to
#define DHTTYPE DHT11   // Change to DHT22 if that's what you have

DHT dht(DHTPIN, DHTTYPE);

//this runs once
void setup()
{
  //initalize DHT sensor
  dht.begin();

  //start the clock
  startMillis = millis();

  //initialize network LEDs
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(ESP_FOUND_LED, OUTPUT);


  //initialize MQ-7 LEDs
  pinMode(HEATING_LED, OUTPUT);
  pinMode(READING_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  //initialize MQ-7 power supply
  pinMode(RELAY, OUTPUT);

  //set baud rate
  Serial.begin(Baud_Rate);
  delay(1000);

  //-----connect to network---------
  Serial.println("Checking if ESP8266 is online...");
connectionStart:
  Serial.println("AT");
  delay(5000);

  if (Serial.find("OK")) {
    digitalWrite(ESP_FOUND_LED, HIGH);
    Serial.println("ESP8266 found <module online>...");
    Serial.println("Trying to connect to network...");
    //connect to your wifi netowork
    bool connected = false;

    do {
      networkBlinkConnecting();

      connected = connectWiFi();

      if (!connected) //signal failure
        for (int i = 0; i < 3; i++)
          networkBlinkError();
    } while (!connected);

    Serial.println("Connection achived....");
    digitalWrite(YELLOW_LED, HIGH); // indicate connection achived

  } else {
    Serial.println("ESP8266 not found...");
    Error();
    goto connectionStart;
  }

}

//this runs over and over
void loop() {

  if (heaterInHighPhase) {
    // 5v phase of cycle. see if need to switch low yet
    if (millis() > switchTimeMillis) {
      Serial.println("Reading from sensors....");
      turnHeaterLow();
    }
    blinkHeating();
  }
  else {
    // 1.4v phase of cycle. see if need to switch high yet
    if (millis() > switchTimeMillis) {
      Serial.println("Heating the gas sensor....");
      turnHeaterHigh();
    }

    // Read temperature and humidity
    float h = dht.readHumidity();
    float f = dht.readTemperature(false);
    unsigned int gasLevel = readGasLevel();
    blinkReading();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(f) || isnan(gasLevel)) {
      networkBlinkError();
      return;
    }
    else if (gasLevel >= 60) {
      tone(BUZZER, 3000); // Send 1KHz sound signal...
    }
    else {
      noTone(BUZZER);     // Stop sound...
    }

    //update ThingSpeak channel with new values
    updated = updateValues(String(f), String(h), String(gasLevel));

    //if update succeeded light up green LED, else light up red LED
    Serial.println(updated);
    if (updated) {
      networkBlinkSending();
    } else {

      networkBlinkError();
    }

    blinkReading();
  }
}

//----network update function--------------
bool updateValues(String temp, String humid, String gasLevel) {

  //initialize your AT command string
  String cmd = "AT+CIPSTART=\"TCP\",\"";

  //add IP address and port
  cmd += IP;
  cmd += "\",80";

  //connect
  Serial.println(cmd);
  delay(500);

  if (Serial.find("Error")) {
    return false;
  }

  //build GET command, ThingSpeak takes Post or Get commands for updates, I use a Get
  cmd = GET;
  //cmd += FIELD1;
  cmd += temp;
  cmd += FIELD2;
  cmd += humid;
  cmd += FIELD3;
  cmd += gasLevel;

  cmd += "\r\n";

  //Use AT commands to send data
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  if (Serial.find(">")) {
    //send through command to update values
    Serial.print(cmd);
  } else {
    Serial.println("AT+CIPCLOSE");
  }

  if (Serial.find("OK")) {
    //success! Your most recent values should be online.
    return true;
  } else {
    return false;
  }
}

//----network functions--------------
boolean connectWiFi() {
  //set ESP8266 mode with AT commands
  Serial.println("AT+CWMODE=1");
  delay(2000);

  //build connection command
  String cmd = "AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";

  //connect to WiFi network and wait 5 seconds
  Serial.println(cmd);
  delay(5000);

  //if connected return true, else false
  if (Serial.find("OK")) {
    return true;
  } else {
    return false;
  }
}

void Error() {
  networkBlinkError();
  Serial.println("Error");
}

//----MQ-7 functions--------------

void blinkHeating() {
  digitalWrite(HEATING_LED, HIGH);
  delay(200);
  digitalWrite(HEATING_LED, LOW);
  delay(200);
}

void blinkReading() {
  digitalWrite(READING_LED, HIGH);
  delay(GAS_LEVEL_READING_PERIOD_MILLIS / 2);
  digitalWrite(READING_LED, LOW);
  delay(GAS_LEVEL_READING_PERIOD_MILLIS / 2);
}
//--read from gas sensor---------
unsigned int readGasLevel() {
  return analogRead(MQ7_ANALOG_IN_PIN);
}

//----network LEDs--------

void networkBlinkSending() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  delay(500);
  digitalWrite(GREEN_LED, LOW);
  delay(500);
}

void networkBlinkError() {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  delay(200);
  digitalWrite(RED_LED, LOW);
  delay(200);
}

void networkBlinkConnecting() {
  digitalWrite(YELLOW_LED, HIGH);
  delay(200);
  digitalWrite(YELLOW_LED, LOW);
  delay(200);
}

//--- relay logic
void turnHeaterHigh() {
  // 5v phase
  digitalWrite(RELAY, HIGH);
  heaterInHighPhase = true;
  switchTimeMillis = millis() + MQ7_HEATER_5_V_TIME_MILLIS;
}

void turnHeaterLow() {
  // 1.4v phase
  digitalWrite(RELAY, LOW);
  heaterInHighPhase = false;
  switchTimeMillis = millis() + MQ7_HEATER_1_4_V_TIME_MILLIS;
}
