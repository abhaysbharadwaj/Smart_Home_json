/************* Smart Home ******************
  This project collects data from the sensors like DHT11,
  LDR, IR and sends them serially using a HC-05 BT device
  to the Raspberry-pi in json string format.
  ---------------------------------------------------------
  created on 2 Dec 2015
  by Abhay Shankar Bharadwaj
  abhaysbharadwaj@gmail.com
  facebook.com/abhaysbharadwaja
  ---------------------------------------------------------
  credits go to Benoit Blanchon for the ArduinoJson library
  and Adafruit industries / Lady Ada for the DHT library
  ---------------------------------------------------------
  This project code is in the public domain.
  It is given as is, and any modifications can be done
  as an open sorce standard. credits to be updated wherever
  and whenever necessary.
  ---------------------------------------------------------
  ----------------- connection details --------------------
  ldr to A0
  DHT!! to D12
  IR to D4
  Relay to D5
  sensor1 to D6 -- connect a pizeo buzzer
  BT Tx to software Rx (D11)
  BT Rx to software Tx (D10)
  ----------------------------------------------------------
  you must include the "ArduinoJson", "DHT" and "SoftwareSerial"
  libraries in arduino's library directory
  (C:\Program Files (x86)\Arduino\libraries)
  (or ...\Arduino\libraries)
  you can download the libraries from:
  ArduinoJson: https://github.com/bblanchon/ArduinoJson
  SoftwareSerial: https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/SoftwareSerial
  DHT: https://github.com/adafruit/DHT-sensor-library

**********************************************************/
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#define DHTPIN 12     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 sensor
DHT dht(DHTPIN, DHTTYPE); //initilize the DHT sensor
int ldr = A0;   // LDR connected to A0
int relay = 5;
int ir = 4;
int buzz = 6;

int rx = 11; // softwareserial rx of arduino is pin 11
int tx = 10; // softwareserial tx of arduino is pin 12
SoftwareSerial mySerial(rx, tx);

float h, t;
int l;  // variable to store the value coming from the sensor
int bt = 0; // variable to store incoming BT data

void setup()
{
  pinMode(relay, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(ir, INPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  dht.begin();
  delay(2000);
}

void loop()
{
  relay_control();//control relay by reading serial data 0=off, 1=on
  humidity_read();//read humidity value
  temperature_read();//read temperature
  light_read(); //read LDR value
  json_print();// send sensor values serially in json format
  ir_control(); // read IR and change buzzer state
  delay(10);
}

/////////////////////////////////////////////////////////////////////////////////////////////
void json_print()
{
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["humidity"] = h;
  root["temp"] = t;
  root["light"] = l;
  root.printTo(mySerial);
  mySerial.println();
  delay(50);
}

void humidity_read()
{
  h = dht.readHumidity();  // Reading temperature or humidity takes about 250 milliseconds!
}

void temperature_read()
{
  t = dht.readTemperature();  // Read temperature as Celsius (the default)
}

void light_read()
{
  l = analogRead(ldr); //Read LDR value
}

void relay_control()
{
  if (mySerial.available() > 0)
    bt = mySerial.read();
  if (bt == '1')
    digitalWrite(relay, HIGH);
  else if (bt == '0')
    digitalWrite(relay, LOW);
  delay(500);
}

void ir_control()
{
  int i = digitalRead(ir);
  if (i == 1)
  {
    for (int j=5; j>0; j--)
    {
      digitalWrite(buzz, HIGH);
      delay(50);
      digitalWrite(buzz,LOW);
    }
  }
  else if (i == 0)
  {
    digitalWrite(buzz, LOW);
  }
}
