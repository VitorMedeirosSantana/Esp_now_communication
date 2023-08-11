#include <esp_noow.h>
#include <WiFi.h>

// Struct criada para receber informação
// Precisa ser exatamente igual da que envia
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

// Criando uma struct chamada myData
struct_message myData;

// feedback quando o dado for recebido
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("Bool: ");
  Serial.println(myData.d);
  Serial.println();
}

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);

  // Configura o esp32 no modo wifi
  WiFi.mode(WIFI_STA);

  // Inicializa o esp_now
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Assim que configurado, começa o registro dos dados do pacote
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() 
{

}
