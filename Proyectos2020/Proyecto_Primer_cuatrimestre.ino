#include <SoftwareSerial.h>
SoftwareSerial BT(A0, A1); // RX, TX
int led1 = 6; //Cocina 1
int led2 = 7; //Living 2
int led3 = 8; //Cocina 1
int led4 = 9; //Living 2
int dato;
boolean state1 = true; //todas las luces
boolean state2 = true; //luces cocina
boolean state3 = true; //luces living
boolean ledstate1 = true; //Cocina 1
boolean ledstate2 = true; //Cocina 2
boolean ledstate3 = true; //Living 1
boolean ledstate4 = true; //Living 2
void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(led1, OUTPUT );
  pinMode(led2, OUTPUT );
  pinMode(led3, OUTPUT );
  pinMode(led4, OUTPUT );
}

void loop() {
  
//int  datoint=dato.toInt();
    
  if (Serial.available()>0) {
    dato = Serial.read();
    Serial.println(dato);
    //datoint=dato.toInt();
    switch (dato) {
      case 'a': //prender y apagar todas las luces
        digitalWrite(led1, state1);
        digitalWrite(led2, state1);
        digitalWrite(led3, state1);
        digitalWrite(led4, state1);
        state1 = !state1;
        break;
      case 'b': //ON OFF Cocina
        digitalWrite(led1, state2);
        digitalWrite(led2, state2);
        state2 = !state2;
        break;
      case 'c': //on off living
        digitalWrite(led3, state3);
        digitalWrite(led4, state3);
        state3 = !state3;
        break;
      case 'd': //Led cocina1
        digitalWrite(led1, ledstate1);
        ledstate1 = !ledstate1;
        break;
      case 'e': //Led cocina2
        digitalWrite(led2, ledstate2);
        ledstate2 = !ledstate2;
        break;
      case 'f': //Led Living 1
        digitalWrite(led3, ledstate3);
        ledstate3 = !ledstate3;
        break;
      case 'g': //Led Living 2
        digitalWrite(led4, ledstate4);
        ledstate4 = !ledstate4;
        break;
    }
  }
}
