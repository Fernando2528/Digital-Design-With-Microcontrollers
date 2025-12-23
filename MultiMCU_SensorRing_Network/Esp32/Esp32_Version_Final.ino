#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!
#endif

BluetoothSerial SerialBT;

#define RXD2 16          // RX2 (por si luego lees respuesta del PIC)
#define TXD2 17          // TX2 -> hacia RX del PIC

const unsigned long INTERVALO_ENVIO_MS = 2000;   // cada 2 s se repite el par de tramas
unsigned long lastSend = 0;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("===== ESP32 TRAMAS LUX + TEMP =====");

  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);   // UART2 a 9600 8N1 [web:8]
  Serial.println("UART2: TX2=GPIO17, RX2=GPIO16, 9600 bps.");

  SerialBT.begin("Anillo_PIC_BT");               // Nombre BT [web:37][web:52]
  Serial.println("Bluetooth SPP listo. Emparejar como 'Anillo_PIC_BT'.");
}

void enviar_dos_tramas() {
  const char *trama1 =
    "kHI=0|ID=101|L=0.00lux|D=11/12/2025|H=08:58:54|HO=11110011|C=0P\r\n";
  const char *trama2 =
    "kHI=0|ID=102|T=27.34C|D=11/12/2025|H=08:58:56|HO=01000000|C=70P\r\n";

  // Enviar seguidas por UART2
  Serial.println("Enviando TRAMA 1 y TRAMA 2 por UART2:");
  Serial.print(trama1);
  Serial.print(trama2);

  Serial2.write((const uint8_t *)trama1, strlen(trama1));
  Serial2.write((const uint8_t *)trama2, strlen(trama2));

  // Eco por Bluetooth (para verlas igual que en la terminal verde)
  SerialBT.print(trama1);
  SerialBT.print(trama2);
}

void loop() {
  if (millis() - lastSend >= INTERVALO_ENVIO_MS) {
    lastSend = millis();
    enviar_dos_tramas();
  }

  // Opcional: puente BT -> UART2
  while (SerialBT.available()) {
    char c = SerialBT.read();
    Serial2.write(c);
    Serial.write(c);
  }

  // Opcional: puente UART2 -> BT (por si el PIC responde)
  while (Serial2.available()) {
    char c = Serial2.read();
    SerialBT.write(c);
    Serial.write(c);
  }

  delay(1);
}
