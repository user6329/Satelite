#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>
#include <RTClib.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

// LoRa pins para Arduino Nano
#define LORA_SS   10
#define LORA_RST   9
#define LORA_DIO0  2

// DHT11
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// RTC DS3231
RTC_DS3231 rtc;

// GPS: RX = D6, TX = D5
SoftwareSerial gpsSerial(6, 5);
TinyGPSPlus gps;

// Objeto JSON
StaticJsonDocument<256> doc;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);

  dht.begin();
  rtc.begin();

  // LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Error iniciando LoRa");
    while (1);
  }

  Serial.println("Transmisor LoRa listo");
}

void loop() {
  // Leer sensores
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  DateTime now = rtc.now();

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

  // Enviar por LoRa
  String mensaje;
  serializeJson(doc, mensaje);

  LoRa.beginPacket();
  LoRa.print(mensaje);
  LoRa.endPacket();

  Serial.println("Datos enviados:");
  Serial.println(mensaje);

  delay(5000); // espera antes de la siguiente transmisión
}
