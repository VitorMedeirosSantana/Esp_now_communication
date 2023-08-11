#include <esp_now.h>
#include <WiFi.h>

// Endereço MAC do esp32 que ira receber os dados
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Struct para enviar dados
// Precisa ser igual ao que recebe os dados
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

// Criando uma struct com o nome de myData
struct_message myData;

// Criando a variavel peerInfor, com os dados de pareamento
esp_now_peer_info_t peerInfo;

// feedback quando as informações forem enviadas
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Inicializando a comunicação serial
  Serial.begin(115200);
 
  // Configurando o esp32 como wifi
  WiFi.mode(WIFI_STA);

  // Inicializando o protocolo esp_now
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Assim que preparado, as informações são empacotadas para serem enviadas
  esp_now_register_send_cb(OnDataSent);
  
  // Registrando o pareamento
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Adicionando os pares        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  // Parametrizando os dados das variaveis a serem enviadas
  strcpy(myData.a, "THIS IS A CHAR");
  myData.b = random(1,20);
  myData.c = 1.2;
  myData.d = false;
  
  // Enviando os dados via esp_now
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(100);
}
