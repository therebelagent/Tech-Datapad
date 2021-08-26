//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadActionSetup_h
#define DatapadActionSetup_h

#include <MCUFRIEND_kbv.h>

class DatapadActionSetup
{
public:
    DatapadActionSetup(MCUFRIEND_kbv *tftlcd, uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin);
    MCUFRIEND_kbv getTftlcd();
    uint8_t getSmallWhiteButtonPin();
    uint8_t getRedButtonPin();
    uint8_t getWhiteButtonPin();
    uint8_t getYellowButtonPin();

private:
    MCUFRIEND_kbv *_tftlcd;
    uint8_t _smallWhiteButtonPin, _redButtonPin, _whiteButtonPin, _yellowButtonPin;
};

#endif