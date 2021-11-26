//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef IDatapadActionSetup_h
#define IDatapadActionSetup_h

#include "IDatapadTFTLCD.h"

class IDatapadActionSetup
{
public:
    IDatapadActionSetup(IDatapadTFTLCD &datapadTFTLCD, uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin) : _datapadTFTLCD(datapadTFTLCD), _smallWhiteButtonPin(smallWhiteButtonPin), _redButtonPin(redButtonPin), _whiteButtonPin(whiteButtonPin), _yellowButtonPin(yellowButtonPin) {}
    virtual IDatapadTFTLCD &getDatapadTFTLCD() = 0;
    virtual uint8_t getSmallWhiteButtonPin() = 0;
    virtual uint8_t getRedButtonPin() = 0;
    virtual uint8_t getWhiteButtonPin() = 0;
    virtual uint8_t getYellowButtonPin() = 0;

protected:
    IDatapadTFTLCD &_datapadTFTLCD;
    const uint8_t _smallWhiteButtonPin, _redButtonPin, _whiteButtonPin, _yellowButtonPin;
};

#endif