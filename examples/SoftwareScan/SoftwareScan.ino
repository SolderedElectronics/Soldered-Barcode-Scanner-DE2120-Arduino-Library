/**
 **************************************************
 *
 * @file        SoftwareScan.ino
 * @brief       Scan and output barcodes using the DE2120 1D/2D barcode
 *              scanner module over SoftwareSerial.
 *
 *              The scanner must first be put into TTL/RS232 mode by
 *              scanning the POR232 barcode from the DYScan settings
 *              manual. The library will automatically negotiate the
 *              baud rate down from 115200 to 9600 bps on first connect.
 *              Change the SoftwareSerial pin arguments to match
 *              your wiring before uploading.
 * 
 *              Make sure you have SoftwareSerial library installed. It
 *              can be found in Arduino library manager.
 * 
 * @authors     Fran Fodor @ soldered.com
 ***************************************************/

#include "SoftwareSerial.h"
SoftwareSerial softSerial(4, 5); // change according to your wiring

#include "DE2120-SOLDERED.h" 
DE2120_Soldered scanner;

#define BUFFER_LEN 40
char scanBuffer[BUFFER_LEN];

void setup()
{
  Serial.begin(115200);
  Serial.println("DE2120 Scanner Example");

  if (scanner.begin(softSerial) == false)
  {
    Serial.println("Scanner did not respond. Please check wiring. Did you scan the POR232 barcode? Freezing...");
    while (1)
      ;
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