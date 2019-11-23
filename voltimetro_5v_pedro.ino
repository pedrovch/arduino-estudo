/*voltimetro 0 a 5v
 * Pedro Vargas
 * Escola Estadual Parobé
 * 20/03
 * 0.1.0
 */

 //bibliotecas
 #include <Arduino.h>

 //definição dos pinos
 #define entradaVoltimetro A0 // rotula o pino A0

 //declaração de variaveis e funções
 void medirEntrada();
 void imprimirSerial();
 int valorSensor = 0;
 float media = 0;
 float acumul = 0;

 //configuração
 void setup(){
  Serial.begin(9600); //inicializa serial em 9600 bps
 }

//função principal
void loop(){
  medirEntrada();//chama rotina para medir
  imprimirSerial();//chama rotina de impressão
  delay(100);
}

//rotina para medir 100 vezes o valor de entrada
void medirEntrada(){
  //efetua 100 vezes a medida, calcula a média e converte o fundo de escala

  for(int x = 1; x <100; x++){
    valorSensor = analogRead(entradaVoltimetro); //le a porta analogiaca
    acumul = acumul + valorSensor; //soma o valor acumulado
  }
  acumul = acumul / 100; //calcula a média
  media = acumul*5/1023;//converte para o fundo de escala 5v
}

//rotina de impressão serial
void imprimirSerial(){
  Serial.print("sensor =");
  Serial.print(valorSensor);
  Serial.print("\t tensão =");
  Serial.println(media,1);
}
