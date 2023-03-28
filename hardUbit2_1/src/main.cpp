// receive
#include <Arduino.h>
#include <painlessMesh.h>

// Detalhes da rede MESH
#define   MESH_PREFIX     "RNTMESH"   // Nome da rede MESH
#define   MESH_PASSWORD   "MESHpassword" // Senha da rede MESH
#define   MESH_PORT       5555        // Porta padrão
#define   RELAY_PIN       D0          // Pino ao qual o relé está conectado

painlessMesh mesh;

void receivedCallback(uint32_t from, String &msg) {
  if (msg == "relay:on") {
    digitalWrite(RELAY_PIN, HIGH); // Ligar o relé
    mesh.sendSingle(from, "relay:onok");
  } else if (msg == "relay:off") {
    digitalWrite(RELAY_PIN, LOW); // Desligar o relé
    mesh.sendSingle(from, "relay:offok");
  }
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  mesh.setDebugMsgTypes(ERROR | STARTUP);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);
}

void loop() {
  mesh.update();
}
