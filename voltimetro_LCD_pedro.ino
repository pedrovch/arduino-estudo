/* voltimetro 5v lcd I2C
   pedro vargas
   parobé
   20/03
   1.2.0
*/
//bibliotecas
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//definição dos pinos
//inicializa no endereço 0x27
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#define entradaVoltimetro A0
//definição das funções e variaveis
void medirEntrada();
void imprimirSerial();
void imprimirLCD();
int valorSensor = 0;
float media = 0;
float acumul = 0;

//configuração
void setup() {
  Serial.begin(9600); //incializa serial em 96000 bps
  lcd.begin(16, 2); //define numero de linhas e colunas do lcd
}

//função principal
void loop() {
  medirEntrada(); //chama rotina para medir
  imprimirSerial(); //chama rotina de impressão serial
  imprimirLCD(); // chama rotina de impressão no LCD
  delay(100);
}

//rotina para medir 100 vezes o valor de entrada
void medirEntrada() {
  //efetua 100 vezes a medida, calcula a médioa e converte o fundo de escala
  for (int x = 1; x < 100; x++) {
    valorSensor = analogRead(entradaVoltimetro); //le a entrada analogica
    acumul = acumul + valorSensor; //soma o valor acumulado
  }
  acumul = acumul / 100; //calcula a média
  media = acumul * 5 / 1023; // converete para o fundo de escala 5v
}

//rotina de impressão serial
void imprimirSerial() {
  Serial.print("sensor =");
  Serial.print(valorSensor);
  Serial.print("\t tensão =");
  Serial.println(media, 1);
}

//rotina de impressão LCD
void imprimirLCD() {
 
  lcd.setCursor(0, 0);//coluna e linha da impressão
  lcd.print("sensor=");
  lcd.setCursor(8, 0);
  lcd.print(valorSensor);
  lcd.setCursor(0, 1);
  lcd.print("tensao=");
  lcd.setCursor(8, 1);
  lcd.print(media, 1);
  
}
