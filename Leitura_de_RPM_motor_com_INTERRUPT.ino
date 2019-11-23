#include <LiquidCrystal.h>

#define potenciometro A0
#define motorBase 6
#define infraRed 2

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int valorRegulador = 0;
int valorSaida = 0;
int rpm;

float media = 0;
float acumul = 0;

volatile byte pulsos;
unsigned long tempo;
unsigned int pulsosPorVolta = 4;

void contador() {
  pulsos++;
}

void setup() {

  lcd.begin(16, 2);
  Serial.begin(9600);

  pinMode(motorBase, OUTPUT);
  pinMode(infraRed, INPUT);

  // 0 = pino 2 interrupt
  // 1 = pino 3 interrupt

  attachInterrupt(0, contador, RISING);
  pulsos = 0;
  rpm = 0;
  tempo = 0;
}
void loop() {

  valorRegulador = analogRead(potenciometro);
  valorSaida = map(valorRegulador, 0, 1023, 0, 255);

  analogWrite(motorBase, valorSaida);

  if (millis() - tempo >= 1000) {
    detachInterrupt(0);
    rpm = (60 * 1000 / pulsosPorVolta) / (millis() - tempo) * pulsos;
    tempo = millis();
    pulsos = 0;

    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("RMP = ");
    lcd.print(rpm);

    attachInterrupt(0, contador, RISING);
  }

  for (int x = 1; x < 100; x++) {
    valorRegulador = analogRead(potenciometro);// lê porta analógica
    acumul = acumul + valorRegulador; // soma o valor acumulado
  }
  acumul = acumul / 100; // calcula a média
  media = acumul * 100 / 1023; // Converte para o fundo de escala em percentagem

  imprimirSerial(); // chama rotina de impressão

  delay(10);
}

void imprimirSerial () {
  Serial.print("ENTRADA = "); // imprime a palavra entrada
  Serial.print(valorRegulador);// imprime o valor da entrada

  Serial.print("\t    ROTAÇÃO = ");// tabula /t e imprime a palavra rotação
  Serial.print(media);// imprime em nova linha o valor em percentual
  Serial.print("%");// imprime simbolo %

  Serial.print("\t SAIDA = ");// tabula /t e imprime a palavra saida
  Serial.print(valorSaida);// imprime em nova linha o valor

  Serial.print("\t RPM = ");// tabula /t e imprime a palavra saida
  Serial.println(rpm);// imprime em nova linha o valor

  delay(2);// aguarda 2 ms
}
