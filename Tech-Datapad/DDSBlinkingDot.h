//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadTFTLCD.h"

#ifndef DDSBlinkingDot_h
#define DDSBlinkingDot_h

class DDSBlinkingDot
{
public:
    DDSBlinkingDot(IDatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t radius, uint16_t colour, uint16_t backColour);
    void update();

private:
    IDatapadTFTLCD &_datapadTFTLCD;
    const int16_t _x, _y, _radius;
    const uint16_t _colour, _backColor;
    int16_t _state = 0, _elapsed = 0;
    unsigned long _previousMillis = 0;
};

#endif