/**
 **************************************************
 *
 * @file        SendCommand.ino
 * @brief       Toggle Code ID prefix transmission on the DE2120
 *              1D/2D barcode scanner module over SoftwareSerial.
 *
 *              When Code ID is enabled, the scanner prepends a
 *              symbology identifier character to every scanned barcode
 *              (e.g. 'A' for Code 128, 'Q' for QR Code). This can help
 *              the host application distinguish barcode types at runtime.
 *
 *              The sketch presents a Serial Monitor prompt and also
 *              continuously polls for barcodes while waiting for input.
 *              Sending 'y' enables Code ID via the CIDENA command;
 *              sending 'n' disables it.
 *
 *              The scanner must first be put into TTL/RS232 mode by
 *              scanning the POR232 barcode from the DYScan settings
 *              manual. Change the SoftwareSerial pin arguments to match
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
  flushRx(); // Clear the serial rx buffer to avoid line endings
  
  Serial.println();
  Serial.println("Transmit Code ID with Barcode? (y/n)");
  Serial.println("-------------------------------------");
  Serial.println("Type 'y' or 'n' or scan a barcode: ");

  // Wait for the user to reply but look for barcodes in the meantime
  while (Serial.available() == false)
  {
      if (scanner.readBarcode(scanBuffer, BUFFER_LEN))
    {
      Serial.println("...");
      Serial.print("Code found: ");
      for (int i = 0; i < strlen(scanBuffer); i++)
        Serial.print(scanBuffer[i]);
      Serial.println();
    }
  
    delay(200);
  }

    switch (Serial.read())
    {

      case 'y':
        Serial.println("Code ID will be displayed on scan");
        scanner.sendCommand("CIDENA", "1");
        break;

      case 'n':
        Serial.println("Code ID will NOT be displayed on scan");
        scanner.sendCommand("CIDENA", "0");
        break;

      default:
        Serial.println("Command not recognized");
        break;
    }
}

void flushRx(){
  while(Serial.available()){
    Serial.read();
    delay(1);
  }
}