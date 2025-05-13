#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>
#include <RTClib.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

// Pines LoRa para Arduino Nano
#define LORA_SS    10
#define LORA_RST    9
#define LORA_DIO0   2

// Pines DHT11
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// GPS NEO-6M en SoftwareSerial
SoftwareSerial gpsSerial(6, 5); // RX, TX
TinyGPSPlus gps;

// RTC
RTC_DS3231 rtc;

// JSON
StaticJsonDocument<256> doc;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);

  dht.begin();
  rtc.begin();

  // Iniciar LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Error al iniciar LoRa");
    while (1);
  }

  Serial.println("Transmisor LoRa iniciado");
}

void loop() {
  // Leer sensores
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  DateTime now = rtc.now();

  // Leer GPS
  double lat = 0.0, lon = 0.0;
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    lat = gps.location.lat();
    lon = gps.location.lng();
  }

  // Construir JSON
  doc["fecha"] = String(now.year()) + "-" + String(now.month()) + "-" + String(now.day());
  doc["hora"] = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  doc["temperatura"] = temperatura;
  doc["humedad"] = humedad;
  doc["latitud"] = lat;
  doc["longitud"] = lon;

  String mensaje;
  serializeJson(doc, mensaje);

  // Enviar por LoRa
  LoRa.beginPacket();
  LoRa.print(mensaje);
  LoRa.endPacket();

  Serial.println("Datos enviados:");
  Serial.println(mensaje);

  delay(5000); // espera antes de volver a transmitir
}
