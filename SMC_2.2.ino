//Blibliotecas para conexão com servidor
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

//Senha e login do Wi-fi
const char* ssid = "";
const char* password = "";

//Pinos dos sensores utilizados
#define sensor 4
#define full 21

//definição da ID do microcontrolador
#define ORG "mvm1bx"
#define DEVICE_TYPE "ESP32"
#define DEVICE_ID "E43A17286F24"
#define TOKEN "0MZbDqpffW*DpzmATr"

//conexão com banco de dados
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char pubTopic1[] = "iot-2/evt/status1/fmt/json";
char pubTopic2[] = "iot-2/evt/status2/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);

//variaveis de controle dos sensores
volatile double waterFlow;
volatile double currentf;
int ftank = 0;

void setup() {
  Serial.begin(115200);

  waterFlow = 0;
  currentf = 0;
  
  //usado para ativação do sensor de fluxo
  attachInterrupt(digitalPinToInterrupt(4), pulse, RISING);
  
  //conecta o Wi-fi
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.print("WiFi connected, IP address: ");
  Serial.println(WiFi.localIP());

  //conecta ao banco de dados
  if (!client.connected()) {
    Serial.print("Reconnecting client to ");
    Serial.println(server);
    while (!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    Serial.println("Bluemix connected");
  }
}

long lastMsg = 0;
void loop() {
  // muda o tipo da variavel dos dados recebidos pelo sensor para melhor leitura
  float m = waterFlow;
  float c = currentf;

  // cria o alerta de tanque cheio
  if (digitalRead(full) == HIGH) {
    while (digitalRead(full) == HIGH); // espera soltar o bt
    ftank = 1;
    if (ftank == 1) {
      currentf = 0;
      Serial.print("tanque cheio");
    }
    ftank = 0;
  }

// envio dos dados lidos para o banco de dados
  client.loop();
  long now = millis();

// envio da primeira variavel de fluxo, para a media de fluxo
  if (now - lastMsg > 3000) {
    lastMsg = now;
    Serial.print("fluxo de agua:");
    Serial.print(m);
    Serial.println("  L");
    delay(500);
    String payload = "{\"d\":{\"flow\":";;
    payload += m;
    payload += "}}";

    Serial.print("Sending payload: ");
    Serial.println(payload);

    if (client.publish(pubTopic1, (char*) payload.c_str())) {
      Serial.println("Publish ok");
    } else {
      Serial.println("Publish1 failed");
    }
//envio da segunda variavel de fluxo, para o fluxo atual
    String payload2 = "{\"d\":{\"currentf\":";;
    payload2 += c;
    payload2 += "}}";

    Serial.print("Sending payload: ");
    Serial.println(payload2);

    if (client.publish(pubTopic1, (char*) payload2.c_str())) {
      Serial.println("Publish ok");
    } else {
      Serial.println("Publish2 failed");
    }
// envio do alerta de tanque cheio
    String payload3 = "{\"d\":{\"alerta\":";; // alerta de tanque cheio
    payload3 += ftank;
    payload3 += "}}";

    Serial.print("Sending payload: ");
    Serial.println(payload3);

    if (client.publish(pubTopic1, (char*) payload3.c_str())) {
      Serial.println("Publish3 ok");
    } else {
      Serial.println("Publish failed");
    }
  }
}
void pulse()   //calculo de quanto liquido passa pelo sensor
{
  waterFlow += 1.0 / 5880.0;
  currentf += 1.0 / 5880.0;
}
