/*pedro vargas c h
   631M2
   escola tecnica estadual parobe
   08.05.2019
   estação meteorologica para hortaliças
   3.2.5
*/
//inicio do programa
//incluão de bibliotecas

#include<Arduino.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<dht.h>
#include<Keypad.h>
#include "Ultrasonic.h"
//definir variaveis  e pinos
LiquidCrystal_I2C lcd(0x27, 16, 2); //configuração do lcd
dht DHT;
char password [4] = {'1', '2', '3', '4'};// senha correta
byte linhas[] = {10, 5, 6, 8};//pinagem das linhas
byte colunas[] = {9, 11, 7, 3};//pinagem das coluunas
int count = 0;
int entrada = 0;
int distancia;


char teclas[4][4] = {{'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Ultrasonic ultrasonic(12, 13);
Keypad keypad = Keypad( makeKeymap(teclas), linhas, colunas, 4, 4);//mapeamento das teclas

#define res 2 // saida do rele da resistencia
#define irrig 4 // saido do rele da irrigação
#define sensor A0 // sensor DHT



//definição de variaveis

void printLcd();
void irrigacao();
void resistencia();
void key_init();
void code_entry_init();
void unlocked();
void liga();

//configuração
void setup() {
  lcd.init();
  lcd.init();//inicia o lcd
  lcd.backlight();
  Serial.begin(9600);//iniica porta serial em 9600bps
  //  pinMode(exaust, OUTPUT); //define o pino do motor como saida
  pinMode(res, OUTPUT);
  pinMode(irrig, OUTPUT);

  key_init();
}
//função principal
void loop() {
  int chk = DHT.read11(sensor);//le o DHT11 no seu pino
  char key = keypad.getKey(); //Obtém tecla pressionada

  //função do ultrasom

  if (ultrasonic.Ranging(CM) <= 10) {
    key_init();
  }
  else {
    liga();
  }
}

void unlocked() {

  Serial.print("acesso liberado");
  //exaustao();
  irrigacao();
  resistencia();
  printLcd();
  //som();
  delay(2);
}

void key_init () {
  Serial.println("aguardando... ");
  Serial.println();
  digitalWrite(irrig, LOW);
  digitalWrite(res, LOW);
  count = 0;       //Variável count é zero na inicialização
}

//Subrotina de Entrada da Senha
void code_entry_init() {
  Serial.println("Entre a Senha:"); //Emite mensagem

  count = 0; //Variável count é zero na entrada de senha
}

void irrigacao() {
  if (DHT.humidity < 90) {
    digitalWrite(irrig, HIGH);
  }
  if (DHT.humidity >= 95) {
    digitalWrite(irrig, LOW);
  }
}

void resistencia() {
  if (DHT.temperature < 20) {
    digitalWrite(res, HIGH);
  }
  if (DHT.temperature > 25) {
    digitalWrite(res, LOW);
  }
}

void printLcd() {
  lcd.setCursor(0, 0);
  lcd.print(DHT.temperature);
  lcd.setCursor(0, 1);
  lcd.print(DHT.humidity);
}

void liga() {
  char key = keypad.getKey(); //Obtém tecla pressionada

  if (key != NO_KEY) { //Se foi pressionada uma tecla:
    if (key == '#') {  //Se a tecla é '#'
      code_entry_init();  //Então espera que seja inserida uma senha

      while (count < 4 ) { //Conta 4 entradas/teclas

        char key = keypad.getKey(); //Obtém tecla pressionada

        if (key != NO_KEY) {  //Se foi pressionada uma tecla:
          entrada += 1;  //Faz entrada = entrada + 1

          if (key == password[count])count += 1;  //Se a tecla pressionada corresponde ao dígito
          //da senha correspondente, soma 1 no contador

          if ( count == 4 ) unlocked();  //Se contador chegou a 4 e com dígitos corretos,
          //desbloqueia sistema

          if (key == '#') { //Se foi pressionada a tecla "#' ou foram feitas
            //4 entradas,
            key_init();   //Inicializa o sistema

            break;  //Para o sistema e espera por uma tecla
          }
        }
      }
    }
  }
}
