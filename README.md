# Satelite
CanSat 2025 con Arduino, LoRa y Node-RED para telemetría y visualización de datos en tiempo real.
# CanSat 2025 🚀

Proyecto CanSat 2025 con Arduino, LoRa y visualización de datos en Node-RED.

## 🔧 Tecnologías utilizadas

- Arduino UNO / Nano
- Sensor DHT11 y BME280
- Módulos LoRa SX1278
- GPS NEO-6M
- Node-RED (para visualización en dashboard)
- Comunicación serial y LoRa

## 📁 Estructura

- `arduino/`: Código principal del CanSat y manejo de sensores
- `lora/`: Código para transmisión y recepción LoRa
- `node-red/`: Flujo exportado del dashboard y documentación visual
- `docs/`: Diagramas, esquemas y documentación adicional

## 📡 Objetivo

Monitorear temperatura, humedad, altitud y ubicación geográfica en tiempo real durante el vuelo del CanSat, transmitiendo datos por LoRa y mostrándolos en un dashboard Node-RED.

## 🛠️ Cómo usar

1. Carga `main.ino` al Arduino transmisor.
2. Conecta el receptor a una PC y corre `lora_receiver.ino`.
3. Importa `flow.json` en Node-RED.
4. Visualiza los datos en el dashboard.

## 👨‍🚀 Equipo

- Nombre del líder: Jael Omar Valerio Sandoval
- Institución: Instituto Tecnologico Superior de la Sierra Negra de Ajalpan
- Año: 2025
