#include "DHT.h"
#include <Servo.h>

#define DHTPIN 2   
#define DHTTYPE DHT11   // DHT 11

Servo servoMotor;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
servoMotor.attach(9);
  dht.begin();
}

void loop() {
  
  delay(2000);

  int h = dht.readHumidity();
  

  // Check if any reads failed and exit early (to try again).
  if (isnan(h)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(h, false);

  Serial.println(F("Humidity: "));
  Serial.println(h);

  if (h<50){ servoMotor.write(0);}
  else{servoMotor.write(90);}

}
