//https://github.com/ShadowFighter99/Arduino/tree/master Ver Branch Mas actualizada y README para las librerias
int led1 = 6; //Cocina 1
int led2 = 7; //Cocina 2
int led3 = 8; //Living 1
int led4 = 9; //Living 2
int tempPin = 0; //Pin de temperatura (Analog)
int movpin = 2; // sensor de movimiento
boolean alarma_state = false;
double tempC = 0;
double tiempo1;
int tiempo2 = 0;
int tempTimer = 1200;
String alarmaChar= "a";
int tempReading;
boolean activado=false;
void setup() {
  Serial.begin(9600);
pinMode(2, INPUT );
  pinMode(led1, OUTPUT );
  pinMode(led2, OUTPUT );
  pinMode(led3, OUTPUT );
  pinMode(led4, OUTPUT );
  
 // attachInterrupt(digitalPinToInterrupt(2), alarma, RISING);
}

void loop() {
int tiempo1=millis();
 tempReading = analogRead(tempPin); // leer temperatura
    tempC = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempC = (1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempC * tempC )) * tempC )) - 273.15; // temperatura en Celsiu
  
  if (Serial.available() > 0) {
activado=true;
    String dato = Serial.readString();
    String dispositivo = dato.substring(0, 3); // Dispositivo
    String pin = dato.substring(3, 4); // el pin que se va a prender
    String estado = dato.substring(4, 5); // El estado 1 o 0 led81
    
    String dispositivo2 = dato.substring(5, 8); // Dispositivo
    String pin2 = dato.substring(8, 9); // el pin que se va a prender
    String estado2 = dato.substring(9, 10); // El estado 1 o 0 led81
   
    String dispositivo3 = dato.substring(10, 13); // Dispositivo
    String pin3 = dato.substring(13, 14); // el pin que se va a prender
    String estado3 = dato.substring(14, 15); // El estado 1 o 0 led81
   
    String dispositivo4 = dato.substring(15, 18); // Dispositivo
    String pin4 = dato.substring(18, 19); // el pin que se va a prender
    String estado4 = dato.substring(19, 20); // El estado 1 o 0 led81

    if (dispositivo == "led") {
      digitalWrite(pin.toInt(), estado.toInt());
    }if (dispositivo2 == "led") {
      digitalWrite(pin2.toInt(), estado2.toInt());
    }
      if (dispositivo3 == "led") {
      digitalWrite(pin3.toInt(), estado3.toInt());
      } if (dispositivo4== "led") {
      digitalWrite(pin4.toInt(), estado4.toInt());
      }
  
}

  if (activado && tiempo1-tiempo2>=tempTimer) {
   Serial.println(tempC);
      tiempo2=tiempo1;
    }
    

}
/*void alarma() {
 alarma_state=true;
 Serial.print("ALRAMAR");
}*/
