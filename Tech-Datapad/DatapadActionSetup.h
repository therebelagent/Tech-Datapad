//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadActionSetup_h
#define DatapadActionSetup_h

#include "IDatapadActionSetup.h"

class DatapadActionSetup : public IDatapadActionSetup
{
public:
    DatapadActionSetup(IDatapadTFTLCD &datapadTFTLCD, uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin);
    IDatapadTFTLCD &getDatapadTFTLCD();
    uint8_t getSmallWhiteButtonPin();
    uint8_t getRedButtonPin();
    uint8_t getWhiteButtonPin();
    uint8_t getYellowButtonPin();
};

#endif