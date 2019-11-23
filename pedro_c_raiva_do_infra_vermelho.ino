/* pedro vch
 * 30.08.2019
 * 0.0.0
 * contador com infra vermelho
 */

 //incluir bibliotecas

#include<Arduino.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //configuração do lcd

//definição dos pinos
#define velMotor A0 //velocidade do motor
#define infV 2 //interrupt
#define saidaMotor A1

//definição de variaveis
int valorEntrada = 0;
int valorSaida = 0;
int rpm;
int pulsos;
void contador(){
  pulsos++;
}

void lcdprint();
void RPM();
void percent();
void imprimirSerial();

unsigned long tempo;
volatile byte pulse;
unsigned int ppv;

float media = 0;
float acumul = 0;


//configuração
void setup(){
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(infV), RPM, RISING);
  pulsos = 0;
  rpm = 0;
  tempo = 0;
}

//função principal
void loop(){
  valorEntrada = analogRead(velMotor); // le a entrada de 0 a 1023
  valorSaida = map(valorEntrada, 0, 1023, 0, 255);// converte entrada para saida
  analogWrite(saidaMotor, valorSaida); //escreve na saida

for (int x = 1; x < 100; x++) {
    valorEntrada = analogRead(velMotor);// lê porta analógica
    acumul = acumul + valorEntrada; // soma o valor acumulado
  }
  acumul = acumul / 100; // calcula a média
  media = acumul * 100 / 1023; // Converte para o fundo de escala em percentagem

  imprimirSerial(); // chama rotina de impressão

  delay(10);
  
  }

 //funçoes
 void RPM(){
  if( millis() - tempo >= 10000){
    detachInterrupt(digitalPinToInterrupt(infV));
    rpm = (6*10000 / ppv) / (millis() - tempo) * pulsos;
    tempo = millis();
    pulsos = 0;

    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("RPM = ");
    lcd.print(rpm);

    attachInterrupt(digitalPinToInterrupt(infV), RPM, RISING);
 }
 }
 
 void imprimirSerial () {
  Serial.print("ENTRADA = "); // imprime a palavra entrada
  Serial.print(valorEntrada);// imprime o valor da entrada

  Serial.print("\t    ROTAÇÃO = ");// tabula /t e imprime a palavra rotação
  Serial.print(media);// imprime em nova linha o valor em percentual
  Serial.print("%");// imprime simbolo %

  Serial.print("\t SAIDA = ");// tabula /t e imprime a palavra saida
  Serial.print(valorSaida);// imprime em nova linha o valor

  Serial.print("\t RPM = ");// tabula /t e imprime a palavra saida
  Serial.println(rpm);// imprime em nova linha o valor

  delay(2);// aguarda 2 ms
 }


 
