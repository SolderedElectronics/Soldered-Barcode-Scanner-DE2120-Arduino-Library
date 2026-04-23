/**
 **************************************************
 *
 * @file        HardwareScan.ino
 * @brief       Scan and output barcodes using the DE2120 1D/2D barcode
 *              scanner module over HardwareSerial (UART2) on ESP32.
 *
 *              Unlike SoftwareSerial, HardwareSerial uses a dedicated
 *              UART peripheral for reliable communication at 115200 bps.
 *              The library will automatically negotiate the baud rate
 *              down to 9600 bps on first connect.
 *
 *              Default wiring: GPIO4 = RX (scanner TX),
 *              GPIO5 = TX (scanner RX). Change the pin arguments in
 *              scannerSerial.begin() to match your wiring.
 *
 *              The scanner must first be put into TTL/RS232 mode by
 *              scanning the POR232 barcode from the DYScan settings
 *              manual before uploading this sketch.
 *
 * @authors     Fran Fodor @ soldered.com
 ***************************************************/

#include "HardwareSerial.h"
HardwareSerial scannerSerial(2); // Use UART2

#include "DE2120-SOLDERED.h"
DE2120_Soldered scanner;

#define BUFFER_LEN 40
char scanBuffer[BUFFER_LEN];

void setup()
{
  Serial.begin(115200);
  Serial.println("DE2120 Scanner Example");

  scannerSerial.begin(115200, SERIAL_8N1, 4, 5); // RX=GPIO4, TX=GPIO5
  delay(500);

  if (scanner.begin(scannerSerial) == false)
  {
    Serial.println("Scanner did not respond. Please check wiring. Did you scan the POR232 barcode? Freezing...");
    while (1);
  }
  Serial.println("Scanner online!");
}

void loop()
{
  if (scanner.readBarcode(scanBuffer, BUFFER_LEN))
  {
    Serial.print("Code found: ");
    for (int i = 0; i < strlen(scanBuffer); i++)
      Serial.print(scanBuffer[i]);
    Serial.println();
  }
  delay(200);
}