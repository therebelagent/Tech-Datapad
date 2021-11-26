//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "IDatapadTFTLCD.h"

#ifndef DDSImagePainter_h
#define DDSImagePainter_h

class DDSImagePainter
{
public:
    DDSImagePainter(IDatapadTFTLCD &datapadTFTLCD);
    void drawArrayJpeg(const uint8_t arrayname[], uint32_t array_size, int x, int y);

private:
    IDatapadTFTLCD &_datapadTFTLCD;
};

#endif