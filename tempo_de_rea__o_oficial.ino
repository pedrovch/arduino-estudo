//tempo de reação

#define start 4
#define fim 5
#define alert 6
byte fl;
byte fz;
void calculo();
unsigned long start_millis;
float tempo;
unsigned long count_millis;
float segundos;
float tr;
float frontCar = 95; // posição final do carro da frente
float pos; //primeira posição do carro de tras
float pos1;
float posFinal1; //quadrado da primeira posição
float posFinal2; // posição final do segundo carro
float velImpacto1; // velocidade do impacto
float velImpacto2; //velocidade ao quadrado
float variacaoPos; // diferença da pos do carro um e do carro dois
float impacto;
float force;
float peso;
float sqrtvel;

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
      //Serial.print(fl);
      digitalWrite(alert, LOW);
      fz = 1;
    }
    if (fz == 1) {
      if ( (millis() - start_millis) > 4000) {
        count_millis = millis();
        digitalWrite(alert, HIGH);
        fl = 0;
        //Serial.println(fl);
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
  //segundos = tempo / 1000; // de milissegundos para segundos
  tr = tempo + 700; // tempo de reação mais tempo de acionametno
  pos1 = 30 * tr; // primeira posição do carro de tras
  pos = pos1 / 1000;
  posFinal1 = pos * pos; //quadrado da prmeira posição
  posFinal2 = posFinal1 / 16; // posição do segundo carro após freiar

  //velocidade no impacto
  variacaoPos = frontCar - pos;// diferença da posição dos dois carros
  velImpacto1 = posFinal1 - 16 * variacaoPos; // velocidade do carro após freiar
  sqrtvel = sqrt(velImpacto1);
  //força do impacto
  velImpacto2 = sqrtvel * sqrtvel; //quadrado da velocidade
  impacto = velImpacto2 / 3.778; //aceleração na colisão
  force = impacto * 68;//força em um homem de 68kg
  peso = force / 10; //de newtons para Kg

  if (posFinal2 < frontCar) {
    Serial.println("Você estava atento e seu carro não bateu ");
    Serial.println("Parabens!");

  }
  if (posFinal2 >= frontCar) {
    Serial.println("Sua falta de atenção causou um acidente");
    Serial.print("Seu tempo de reação foi de: ");
    Serial.print(tempo);
    Serial.println(" millisegundos");
    Serial.print("Devido a sua velocidade e seu tempo de reação, a força exercida sobre o seu corpo foi de: ");
    Serial.print(force);
    Serial.println(" N");
    Serial.print("O que é equivalente a: ");
    Serial.print(peso);
    Serial.println(" Kg");
  }

}
