//tempo de reação

#define start 4
#define fim 5
#define alert 6
byte fl;
byte fz;
void calculo();
unsigned long start_millis;
unsigned long tempo;
unsigned long count_millis;
void setup() {
  fl = 1;
  Serial.begin(9600);
  pinMode(start, INPUT);
  pinMode(fim, INPUT);
  pinMode(alert, OUTPUT);
  Serial.print("esperando...");
}

void loop() {
  if (fl == 1) {
    if (digitalRead(start) == HIGH) {
      while (digitalRead(start) == HIGH); // espera soltar o bt
      start_millis = millis();
      Serial.println("se prepare");
      Serial.print(fl);
      digitalWrite(alert, LOW);
      fz = 1;
    }
    if(fz == 1){
    if ( (millis() - start_millis) > 4000) {
      count_millis = millis();
      digitalWrite(alert, HIGH);
      fl = 0;
      Serial.println(fl);
      fz = 0;
    }
    }
  }
  if (fl == 0) {
    if (digitalRead(fim) == HIGH) {
      while (digitalRead(fim) == HIGH);
      tempo = millis() - count_millis;
      calculo();
      fl = 1;
    }
  }
}

void calculo() {
  Serial.println(tempo);
}
