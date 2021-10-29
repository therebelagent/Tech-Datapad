//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DDSImage.h"

#ifndef DDSIrlingBImage_h
#define DDSIrlingBImage_h

class DDSIrlingBImage : DDSImage
{
public:
    DDSIrlingBImage(DatapadTFTLCD &datapadTFTLCD);
    void drawImage(int16_t x, int16_t y);
    int16_t width();
    int16_t height();

private:
    DatapadTFTLCD &_datapadTFTLCD;
};

#endif