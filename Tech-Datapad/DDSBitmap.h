//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadTFTLCD.h"

#ifndef DDSBitmap_h
#define DDSBitmap_h

class DDSBitmap
{
public:
    DDSBitmap();
    virtual void drawRGBBitmap(int16_t x, int16_t y);
    virtual int16_t width();
    virtual int16_t height();
};

#endif