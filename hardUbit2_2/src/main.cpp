// send
#include <Arduino.h>
#include <painlessMesh.h>

// Detalhes da Rede Mesh
#define MESH_PREFIX "RNTMESH" // Nome para sua rede Mesh
#define MESH_PASSWORD "MESHpassword" // Senha para sua rede Mesh
#define MESH_PORT 5555 // Porta padrão
#define RELAY_PIN D0 // Pino ao qual o relé está conectado

painlessMesh mesh; // Criação de um objeto Mesh


void sendMessage(String msg) {
  mesh.sendBroadcast(msg); // Função para enviar mensagem
}

void handleRelayon() {
  sendMessage("relay:on"); // Envia mensagem para a rede Mesh
}

void handleRelayoff() {
  sendMessage("relay:off"); // Envia mensagem para a rede Mesh
}

void receivedCallback(uint32_t from, String &msg) {
  if (msg == "relay:onok") {
    sendMessage("relay:off"); // Envia mensagem para a rede Mesh  
  } 
}


void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT); // Configura o pino do relé como saída
  digitalWrite(RELAY_PIN, LOW); // Desliga o relé
  handleRelayoff();

  mesh.setDebugMsgTypes(ERROR | STARTUP); // Habilita tipos de mensagens de depuração
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT); // Inicializa a rede Mesh
  mesh.onReceive(&receivedCallback);
}

void loop() {
  handleRelayon();
  delay(500);
  handleRelayoff();
  delay(500);
  mesh.update(); // Atualiza a rede Mesh
}
