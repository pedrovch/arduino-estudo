#include <SoftwareSerial.h> //INCLUSÃO DE BIBLIOTECA
#include <Thermistor.h> //INCLUSÃO DA BIBLIOTECA

const int pinoRX = 2; //PINO DIGITAL 2 (RX)
const int pinoTX = 3; //PINO DIGITAL 3 (TX)
const int pinoLed = 8; //PINO DIGITAL UTILIZADO PELO LED
int dadoBluetooth = 0; //VARIÁVEL QUE ARMAZENA O VALOR ENVIADO PELO BLUETOOTH
boolean loopLED = false; //VARIÁVEL BOOLEANA QUE FAZ O CONTROLE DE ATIVAÇÃO DO LOOP DO LED
Thermistor temp(2);

SoftwareSerial bluetooth(pinoRX, pinoTX); //PINOS QUE EMULAM A SERIAL, ONDE
//O PINO 2 É O RX E O PINO 3 É O TX

void setup() {
  Serial.begin(9600); //INICIALIZA A SERIAL
  bluetooth.begin(9600); //INICIALIZA A SERIAL DO BLUETOOTH
  bluetooth.print("$"); //IMPRIME O CARACTERE
  bluetooth.print("$"); //IMPRIME O CARACTERE
  bluetooth.print("$"); //IMPRIME O CARACTERE
  delay(100); //INTERVALO DE 100 MILISSEGUNDOS
  pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA
}

void loop() {
  if (bluetooth.available()) { //SE O BLUETOOTH ESTIVER HABILITADO, FAZ
    dadoBluetooth = bluetooth.read(); //VARIÁVEL RECEBE O VALOR ENVIADO PELO BLUETOOTH

    if (dadoBluetooth == '1') { //SE O VALOR RECEBIDO FOR IGUAL A 1, FAZ
      Serial.println("LED LIGADO"); //IMPRIME O TEXTO NA SERIAL
      digitalWrite(pinoLed, HIGH); //LIGA O LED
    }
    if (dadoBluetooth == '0') { //SE O VALOR RECEBIDO FOR IGUAL A 0, FAZ
      Serial.println("LED DESLIGADO"); //IMPRIME O TEXTO NA SERIAL
      digitalWrite(pinoLed, LOW); //DESLIGA O LED
    }
    if (dadoBluetooth == 'b') { //SE O VALOR RECEBIDO FOR IGUAL A b, FAZ
      Serial.println("LOOP DO LED ATIVADO"); //IMPRIME O TEXTO NA SERIAL
      loopLED = true; //VARIÁVEL RECEBE verdadeiro
    } else { //SENÃO, FAZ
      loopLED = false; //VARIÁVEL RECEBE falso
    }
  }

  //MÉTODO RESPONSÁVEL PELO LOOP (LIGA / DESLIGA) DO LED
  if (loopLED) {
    digitalWrite(pinoLed, HIGH); //LIGA O LED
    Serial.println("LOOP (LED LIGADO)"); //IMPRIME O TEXTO NA SERIAL
    delay(500); //INTERVALO DE 500 MILISSEGUNDOS
    digitalWrite(pinoLed, LOW); //DESLIGA O LED
    Serial.println("LOOP (LED DESLIGADO)"); //IMPRIME O TEXTO NA SERIAL
    delay(500); //INTERVALO DE 500 MILISSEGUNDOS
  }
//NTC
  int temperature = temp.getTemp(); //VARIÁVEL DO TIPO INTEIRO QUE RECEBE O VALOR DE TEMPERATURA CALCULADO PELA BIBLIOTECA
  bluetooth.print("Temperatura: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  bluetooth.print(temperature); //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA
  bluetooth.println("*C"); //IMPRIME O TEXTO NO MONITOR SERIAL
  delay(1000); //INTERVALO DE 1 SEGUNDO
}
