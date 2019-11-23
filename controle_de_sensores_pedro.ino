/*
    Controle de Sensores
    Pedro Vargas Castro Hindrichson
    Escola Técnica parobé
    14/03/2019
    0.0.0
*/

//inclusãoe bibliotecas
#include <Arduino.h> //biblioteca padrão

//definição dos pinos
#define sensorPino A0 //da nome ao pino
#define pinoSaida 13

//definição das variaveis
int valorSensor = 0; //valor inicial do sensor
int valorSaida = 0; //valor inicial da saida

//setup do hardware
void setup() {
  Serial.begin(9600); //inicializa a porta seria reserva dos pinos 2 3
}

//função principal
void loop(){
  valorSensor = analogRead(sensorPino); // lê a entrada A0 de 0 a 1023
  valorSaida = map(valorSensor, 0, 1023, 0, 255); //converte saida pra entrada
  analogWrite(pinoSaida, valorSaida); //escreve na saida

  //imprime no monitor serial
  Serial.print("sensor = "); //imprime a palavra sensor
  Serial.print(valorSensor); //imprime o valor de entrada
  Serial.print("\t saida = "); //tabula e imprime a palavra saida
  Serial.println(valorSaida); //imprime o valor de saida

  delay(2); //aguarda 2ms

}
