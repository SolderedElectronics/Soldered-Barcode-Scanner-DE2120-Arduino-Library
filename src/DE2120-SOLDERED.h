/**
 **************************************************
 *
 * @file        DE2120-SOLDERED.h
 * @brief       Header file for barcode scanner.
 *              Wrapper for SparkFun library.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Fran Fodor @ soldered.com
 ***************************************************/

#ifndef __DE2120_SOLDERED__
#define __DE2120_SOLDERED__

#include "Arduino.h"
#include "libs/SparkFun_DE2120_Arduino_Library.h"

class DE2120_Soldered : public DE2120
{
  public:
    DE2120_Soldered() : DE2120() {}
};

#endif
