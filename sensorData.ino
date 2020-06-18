#include <LM35.h>
LM35 temp(A0);

#include <Wire.h>
#define SLAVE_ADDRESS 0x04

#include "DHT.h"
#define DHTPIN 10     // what digital pin we're connected to
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int pin = 11,a=0,b=100;

void setup() {
pinMode(13, OUTPUT);
Serial.begin(9600); // start serial for output
// initialize i2c as slave
Wire.begin(SLAVE_ADDRESS);
dht.begin();
pinMode(A0, INPUT);
// define callbacks for i2c communication
pinMode(pin,INPUT);

Serial.println("ready!");
}

void loop() {
  Wire.onRequest(sendData);
  sendData();
  vibr();
  delay(1);
}
void sendData(){
  int sensorValue=temp.cel();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

    if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.println("Humid: ");
  Serial.print(h);
  Serial.print("  %\t");
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Lm35:");
  Serial.print(sensorValue);
  Serial.print(" vib");
  Serial.print(b);
  String s1=(String)sensorValue;
  String s2=(String)h;
  String s4=(String)b;
  String s3=s1+" "+s4+" "+s2;
  Wire.write(s3.c_str());
}

void vibr(){
  int val = digitalRead(pin);
if(val == LOW & a==1){ 
  a=0;
  b++;
}
if(val==HIGH & a==0){
  a=1;
  b++;
}
if(b>=999){
  b=100;
}
}
