//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "IDatapadTFTLCD.h"

#ifndef IDDSImage_h
#define IDDSImage_h

class IDDSImage
{
public:
    IDDSImage(IDatapadTFTLCD &datapadTFTLCD) : _datapadTFTLCD(datapadTFTLCD) {}
    virtual void drawImage(int16_t x, int16_t y) = 0;
    virtual int16_t width() = 0;
    virtual int16_t height() = 0;

protected:
    IDatapadTFTLCD &_datapadTFTLCD;
};

#endif