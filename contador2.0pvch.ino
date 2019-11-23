/*
 * contador
 * pedro vch
 * 22/08/2019
 * 1.0.0.
 */

 //incluir bibliotecas
 #include<Arduino.h>

 //definição dos pinos
 #define inc 8
 #define dec 9
 #define zer 10
 #define inter 2
 //definição das variaveis
int count = 0;
void alt();

 //definição das configutações
void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(inter), alt, FALLING);
  Serial.print("valor = ");
  Serial.println(count);
}

//função principal
void loop(){
}

void alt(){
  if(digitalRead(zer)== 0){
  count = 0;
  Serial.print("valor = ");
  Serial.println(count);
  }
  if(digitalRead(dec)== 0){
  count--;
  Serial.print("valor = ");
  Serial.println(count);
}
 if(digitalRead(inc)== 0){
  count++;
  Serial.print("valor = ");
  Serial.println(count);
}
 }
