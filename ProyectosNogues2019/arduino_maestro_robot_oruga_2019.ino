#include "Wire.h"
#include <SoftwareSerial.h> 
SoftwareSerial BT(A2,A3); // RX, TX
#define MPU 0x68
#define A_R 16384.0    
#define G_R 131.0       
#define RAD_A_DEG = 57.295779
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;//MPU-6050 da los valores en enteros de 16 bits
int gesto=0;
float Acc[2];
float Gy[3];
float Angle[3];
String valores;
long tiempo_prev;
float dt;
int gesto_buzzer=0;
void setup()
{
 Wire.begin(); // D2(GPIO4)=SDA / D1(GPIO5)=SCL
 Wire.beginTransmission(MPU);
 Wire.write(0x6B);
 Wire.write(0);
 Wire.endTransmission(true);
 Serial.begin(9600);
 BT.begin(9600);
 pinMode(13,OUTPUT);
}
 
void loop()
{
   Wire.beginTransmission(MPU);
   Wire.write(0x3B); //Pedir el registro 0x3B - corresponde al AcX
   Wire.endTransmission(false);
   Wire.requestFrom(MPU,6,true);   //A partir del 0x3B, se piden 6 registros
   AcX=Wire.read()<<8|Wire.read(); //Cada valor ocupa 2 registros
   AcY=Wire.read()<<8|Wire.read();
   AcZ=Wire.read()<<8|Wire.read();
   Acc[1] = atan(-1*(AcX/A_R)/sqrt(pow((AcY/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;
   Acc[0] = atan((AcY/A_R)/sqrt(pow((AcX/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;
   Wire.beginTransmission(MPU);
   Wire.write(0x43);
   Wire.endTransmission(false);
   Wire.requestFrom(MPU,6,true);   //A partir del 0x43, se piden 6 registros
   GyX=Wire.read()<<8|Wire.read(); //Cada valor ocupa 2 registros
   GyY=Wire.read()<<8|Wire.read();
   GyZ=Wire.read()<<8|Wire.read();
   Gy[0] = GyX/G_R;
   Gy[1] = GyY/G_R;
   Gy[2] = GyZ/G_R;
   dt = (millis() - tiempo_prev) / 1000.0;
   tiempo_prev = millis();
   Angle[0] = 0.98 *(Angle[0]+Gy[0]*dt) + 0.02*Acc[0];
   Angle[1] = 0.98 *(Angle[1]+Gy[1]*dt) + 0.02*Acc[1];
   Angle[2] = Angle[2]+Gy[2]*dt;
   valores = "90, " +String(Angle[0]) + "," + String(Angle[1]) + "," + String(Angle[2]) ;
   //Serial.println(valores);

   if(gesto == 0){
    if(Angle[0] > 45){
       gesto=gesto*0+1;
      } 
    }
     if(gesto == 1){
      if(Angle[0] < -45){
        gesto=gesto*0+2;
      }
    }
     if(gesto == 2){
      
       if(gesto_buzzer == 0){
        BT.write('f');
        delay(500);
        gesto_buzzer=gesto_buzzer+1;
        }
               arrancar_auto();

      }
    }
 
void arrancar_auto() {
  digitalWrite(13,HIGH);
  if(Angle[0] < 45 && Angle[0] > -45 && Angle[1] < 45 && Angle[1] > -45){
 //estar quieto
  BT.write('e');
  }
  else if(Angle[0] > 45 && Angle[1] < 45 && Angle[1] > -45){
  // mover izquierda rotar ruedas
  BT.write('c');
  }
  else if(Angle[0] < -45 && Angle[1] < 45 && Angle[1] > -45 ){
  //moverderecha
  BT.write('b');
  }
  else if(Angle[1] > 45 && Angle[0] < 45 && Angle[0] > -45 ){
  //atras(creo)
  BT.write('d');
  }
  else if(Angle[1] < -45 && Angle[0] < 45 && Angle[0] > -45){
  //adelante(creo)
  BT.write('a');
  }  }
