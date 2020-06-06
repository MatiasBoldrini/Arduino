#include <Separador.h>
Separador separador;
#include <IRremote.h>
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
int led1 = 6; //Cocina 1
int led2 = 7; //Cocina 2
int led3 = 8; //Living 1
int led4 = 9; //Living 2
int tempPin = 0; //Pin de temperatura
int encendido = true;
int apagado = 'E318261B';
int vol2 = '511DBB';
int vol1 = 'A3C8EDDB';
int play = 'D7E84B1B';
int skip_fw = '20FE4DBB';
int skip_bw = '52A3D41F';
int uno = '9716BE3F';
int dos = '3D9AE3F7';
int tres = '6182021B';
int cuatro = '8C22657B';
int cinco = '488F3CBB';
int seis = '449E79F';
int siete = '32C6FDF7';
int ocho = '1BC0157B';
int nueve = '3EC3FC1B';
void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(led1, OUTPUT );
  pinMode(led2, OUTPUT );
  pinMode(led3, OUTPUT );
  pinMode(led4, OUTPUT );
}

void loop() {
  if (Serial.available() > 0) {
    int tempReading = analogRead(tempPin); // leer temperatura
    double tempC = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempC = (1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempC * tempC )) * tempC )) - 273.15; //temperatura en Celsius
    int valor = round(map(tempC, 15, 40, 30, 180)); // conversion de temperatura para la app
    String datoString = Serial.readString(); // llegaran 3 datos desde el Bluetooth, separados por coma
    String estado = separador.separa(datoString, ',', 0);
    String pin = separador.separa(datoString, ',', 1);
    String dispositivo = separador.separa(datoString, ',', 2);
    if (dispositivo.length() > 1) { // si es un string
      if (dispositivo == "leds") {
        digitalWrite(pin.toInt(), estado.toInt());
      }
    } else if (dispositivo.length() == 1) { // si es un char
      if (dispositivo == "a") {
        //prender las luces
      } else if (dispositivo == "b") {
        //apagar las luces
      }
    }
  }
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }

}
