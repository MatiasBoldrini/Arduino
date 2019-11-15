#include <SoftwareSerial.h>
SoftwareSerial BT(A0,A1); // RX, TX
#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880
int led1 = 9;
int led2 = 10;
int ENA=5;
int ENB=6;
int in1=2;
int in2=3;
int in3=4;
int in4=7;
int speakerPin = 13;
int dato;
const int tonos[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};
const int countTonos = 10;
void setup() {
Serial.begin(9600);
BT.begin(9600);
pinMode(13,OUTPUT );
 pinMode(ENA,OUTPUT);
 pinMode(ENB,OUTPUT);
 pinMode(in1,OUTPUT);
 pinMode(in2,OUTPUT);
 pinMode(in3,OUTPUT);
 pinMode(in4,OUTPUT);

}

void loop() {
   dato=BT.read();
   Serial.println(dato);
 

//Serial.println(dato);
if (BT.available()){
  dato=BT.read();
 // Serial.println(dato);

  switch (dato){
    case 'a'://adelante
adelante();
      break;
    case 'b'://derecha
       derecha();
      break;
      case 'c'://izquierda
   izquierda();
      break;
    case 'd'://reversa
      atras();
      break;
      case 'e'://parar
   parada();
      break;
      case 'f':
       for (int iTono = 0; iTono < countTonos; iTono++)
  {
   tone(speakerPin, tonos[iTono]);
   delay(100);
  }
  noTone(speakerPin);
    delay(300);
    break;
    case 'j':
beep(speakerPin, a, 500);
beep(speakerPin, a, 500);
beep(speakerPin, a, 500);
beep(speakerPin, f, 350);
beep(speakerPin, cH, 150);

beep(speakerPin, a, 500);
beep(speakerPin, f, 350);
beep(speakerPin, cH, 150);
beep(speakerPin, a, 1000);
    break;
    }
  }
}
void parada(){
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
void adelante(){
  analogWrite(ENA,255);
  analogWrite(ENB,255);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  
  }
 void atras(){
    analogWrite(ENA,255);
  analogWrite(ENB,255);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
 }
void derecha(){
    analogWrite(ENA,255);
  analogWrite(ENB,255);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
void izquierda(){
    analogWrite(ENA,255);
  analogWrite(ENB,255);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{

int x;
long delayAmount = (long)(1000000/frequencyInHertz);
long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
for (x=0;x<loopTime;x++)
{
digitalWrite(speakerPin,HIGH);
delayMicroseconds(delayAmount);
digitalWrite(speakerPin,LOW);
delayMicroseconds(delayAmount);
}

digitalWrite(led1, LOW);
digitalWrite(led2, LOW);
delay(20);
}
