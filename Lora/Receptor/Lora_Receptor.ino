#include <SPI.h>
#include <LoRa.h>
#include <ArduinoJson.h>

// Pines LoRa (SX1278) para Arduino Uno
#define LORA_SS    10
#define LORA_RST    9
#define LORA_DIO0   2

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Configurar pines LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  // Iniciar LoRa a 433 MHz
  if (!LoRa.begin(433E6)) {
    Serial.println("Error al iniciar LoRa. Verifica conexiones.");
    while (true);
  }

  Serial.println("Receptor LoRa listo y escuchando...");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String received = "";

    while (LoRa.available()) {
      received += (char)LoRa.read();
    }

    Serial.println("\n=== Paquete recibido ===");
    Serial.println("JSON recibido: " + received);

    // Parsear JSON
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, received);

    if (error) {
      Serial.print("Error al parsear JSON: ");
      Serial.println(error.c_str());
      return;
    }

    // Mostrar datos
    Serial.println(">> Datos recibidos:");
    Serial.print("Fecha: ");       Serial.println(doc["fecha"].as<String>());
    Serial.print("Hora: ");        Serial.println(doc["hora"].as<String>());
    Serial.print("Temperatura: "); Serial.print(doc["temperatura"].as<float>()); Serial.println(" °C");
    Serial.print("Humedad: ");     Serial.print(doc["humedad"].as<float>());     Serial.println(" %");
    Serial.print("Latitud: ");     Serial.println(doc["latitud"].as<float>(), 6);
    Serial.print("Longitud: ");    Serial.println(doc["longitud"].as<float>(), 6);
    Serial.println("========================");
  }
}
