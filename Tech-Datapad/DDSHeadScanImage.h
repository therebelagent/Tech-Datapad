//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DDSImage.h"

#ifndef DDSHeadScanImage_h
#define DDSHeadScanImage_h

class DDSHeadScanImage : DDSImage
{
public:
    DDSHeadScanImage(DatapadTFTLCD &datapadTFTLCD);
    void drawImage(int16_t x, int16_t y);
    int16_t width();
    int16_t height();

private:
    DatapadTFTLCD &_datapadTFTLCD;
};

#endif