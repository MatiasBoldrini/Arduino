#include <Stepper.h>
#include <SoftwareSerial.h>
#include <Servo.h>
Servo Miservo;
SoftwareSerial BTSerial (2,3); //pines bluetooth
const int stepsPerRevolution = 200;
boolean Motor;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
char comando;
void setup() {
  myStepper.setSpeed(60);
  Serial.begin(9600);
  BTSerial.begin(9600);
  Miservo.attach(5);
  Miservo.write(90);
}

void loop() {
  if (Serial.available()) {
    comando = Serial.read();
    Serial.println(comando);
    if (comando == 'W' ) {
      adelante();
      Motor = true;
    }
    }
    if (comando == 'X') {
    parado();
    Motor = false;
    }        
        if(Motor == true){
          myStepper.step(stepsPerRevolution);
    }
}
void adelante(){
        Miservo.write(0);

  }
void parado(){
      Miservo.write(90);
  }
