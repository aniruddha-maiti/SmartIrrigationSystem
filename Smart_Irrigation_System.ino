#define BLYNK_TEMPLATE_ID "TMPL8MP_QTh6"
#define BLYNK_DEVICE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "6c06hPcHiJis2cDYAA-O5MIDQ5MGqcvY"

#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
#define BLYNK_PRINT Serial
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YourNetworkName"; //WiFi SSID
char pass[] = "YourNetworkPassword"; //WiFi Password
#define pirPin D1
int pirValue;
int pinValue;
#define sensorPin D6
#define rainPin D5
int sensorState = 0;
int rainState = 0;
int lastState = 0;
int lastRainState = 0;
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
BLYNK_WRITE(V0)
{
pinValue = param.asInt();
}
BLYNK_WRITE(V1)
{
int Value0 = param.asInt();
if(Value0 == 1)
digitalWrite(D0,HIGH);
else if(Value0 == 0)
digitalWrite(D0,LOW);
}
void sendSensor()
{
float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
return;
}
Blynk.virtualWrite(V5, h); //V5 is for Humidity
Blynk.virtualWrite(V6, t); //V6 is for Temperature
}
void setup()
{
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
pinMode(sensorPin, INPUT);
pinMode(D0,OUTPUT);
pinMode(rainPin, INPUT);
pinMode(pirPin, INPUT);
dht.begin();
timer.setInterval(1000L, sendSensor);
Serial.begin(115200);
Blynk.begin(auth, ssid, pass);
sensors.begin();
}
int sensor=0;
void send Temps()
{
sensor= analogRead(A0);
Serial.println(temp);
sensors.requestTemperatures();
float temp = sensors.getTempCByIndex(0); 
Serial.println(sensor); 
delay(1000);
}
Blynk virtualWrite(V1, temp);
Blynk virtualWrite(V6, sensor);
void getPirValue(void)
{
//Get PIR Data
pirValue = digitalRead(pirPin);
if (pirValue)
{
Serial.println("Motion detected"); 
Blynk.notify("Motion detected");
}
}
void loop()
{
Blynk.run(); 
timer.run();
sendTemps(); 
sensorState = digitalRead(sensorPin); 
Serial.println(sensorState);
if (sensorState== 1 && lastState == 0) 
{ 
  Serial.println("needs water, send notification"); 
  Blynk.notify("Water your plants"); 
  lastState = 1;
  delay(1000);
  digitalWrite(DO,HIGH); 
  //send notification
}
else if (sensorState== 1 && lastState == 1) 
{ //do nothing, has not been watered yet 
  Serial.println("has not been watered yet"); 
  delay(1000); 
}

else { 
  //st
  Serial.println("does not need water"); 
  lastState = 0; 
  digitalWrite(DO,LOW); 
  delay(1000);
}
rainState= digitalRead(rainPin);
Serial.println(rainState);

if (rainState== 0 && lastRainState= =0){ 
  Serial.println("Its Raining!"); 
  digitalWrite(DO,LOW); 
  Blynk virtualWrite(V4,1); 
  Blynk.notify("Its Raining!"); 
  lastRainState=1;
  delay(1000); 
  //send notification
}

else if (rainState = 0 && lastRainState = 1) 
{ 
  delay(1000);
}
else {
  Serial.println("No Rains")
  Blynk virtualWrite(V4,0);
  lastRainState = 0;
  delay(1000);
}
if(pinValue == HIGH)
{
  getPirValue();
}
Blynk.run();
delay(100);
}
