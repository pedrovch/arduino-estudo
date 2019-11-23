/*
   Controle de Sensores com Motor
   Pedro Vargas Castro Hindrichson
   Escola técnica Parobe
   12/03/2019
   1.1.1
*/
//inclusão das bibliotecas
#include <Arduino.h>

//definição dos pinos
#define sensorPino A0 //define rotulo ao pino
#define pinoSaida 13

//estruturas e variaveis
void imprimeSaida(); //estrutura de impressão

int valorSensor = 0;//valor incial do sensor
int valorSaida = 0;//valor inicial da saida

//setup do hardware
void setup() {
  Serial.begin(9600);//inicializaa porta serial reserva pinos 2 e 3
}

//função principal
void loop(){
  valorSensor = analogRead(sensorPino); // le a entrada de 0 a 1023
  valorSaida = map(valorSensor, 0, 1023, 0, 255);// converte entrada para saida
  analogWrite(pinoSaida, valorSaida); //escreve na saida
  imprimeSerial();
}

//rotina de impressão
void imprimeSerial(){
  Serial.print("sensor = ");
  Serial.print(valorSensor);
  Serial.print("\t motor = ");
  Serial.println(valorSaida);

  delay(2);//aguarda 2ms
}
