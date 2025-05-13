#include <SPI.h>
#include <LoRa.h>

#define SS_PIN 10     // NSS
#define RST_PIN 9     // RESET
#define DIO0_PIN 2    // IRQ

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Configurar pines LoRa
  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);

  // Inicializar LoRa a 433 MHz
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa no detectado. Verifica conexiones.");
    while (1);
  }

  Serial.println("Transmisor LoRa listo");
}

void loop() {
  String mensaje = "Hola desde el transmisor";
  Serial.println("Enviando: " + mensaje);

  LoRa.beginPacket();
  LoRa.print(mensaje);
  LoRa.endPacket();

  delay(2000); // Espera 2 segundos entre envíos
}
