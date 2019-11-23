#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

const char* ssid = "VARGAS_2G";
const char* password = "Q2019cpx";
#define sensor 4
#define ORG "mvm1bx"
#define DEVICE_TYPE "ESP32"
#define DEVICE_ID "E43A17286F24"
#define TOKEN "0MZbDqpffW*DpzmATr"

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char pubTopic1[] = "iot-2/evt/status1/fmt/json";
char pubTopic2[] = "iot-2/evt/status2/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);
volatile double waterFlow;


void setup() {
  Serial.begin(115200);

  waterFlow = 0;
  attachInterrupt(digitalPinToInterrupt(4), pulse, RISING);
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
  client.loop();
  long now = millis();
  if (now - lastMsg > 3000) {
    lastMsg = now;
    Serial.print("fluxo de agua:");
    Serial.print(waterFlow);
    Serial.println("   L");
    delay(500);
    String payload = "{\"d\":{\"flow\":";;
    payload += waterFlow;
    payload += "}}";

    Serial.print("Sending payload: ");
    Serial.println(payload);

    if (client.publish(pubTopic1, (char*) payload.c_str())) {
      Serial.println("Publish ok");
    } else {
      Serial.println("Publish failed");
    }
  }
}
void pulse()   //measure the quantity of square wave
{
  waterFlow += 1.0 / 5880.0;
}
