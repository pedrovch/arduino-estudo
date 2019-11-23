/* pedro vch
   30.08.2019
   0.0.0
   contador com infra vermelho
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
void contador();
void imprimirSerial();

unsigned long tempo;

//configuração
void setup() {
  lcd.init();
  lcd.init();
  lcd.backlight();
  attachInterrupt(digitalPinToInterrupt(infV), contador, RISING);
  pulsos = 0;
  rpm = 0;
  tempo = 0;
  pinMode(velMotor, INPUT);
}

//função principal
void loop() {
  valorEntrada = analogRead(velMotor); // le a entrada de 0 a 1023
  valorSaida = map(valorEntrada, 0, 1023, 0, 255);// converte entrada para saida
  analogWrite(saidaMotor, valorSaida); //escreve na saida

  if ( millis() - tempo >= 1000) {
    rpm = pulsos * 60;

    lcd.setCursor(0, 0);
    lcd.print("RPM = ");
    lcd.print(rpm);

    tempo = millis();

    pulsos = 0;
  }
}

void contador() {
  pulsos++;
}
