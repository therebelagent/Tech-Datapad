//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadTFTLCD.h"

#ifndef DDSProgressBar_h
#define DDSProgressBar_h

class DDSProgressBar
{
public:
    DDSProgressBar(DatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t width, int16_t height, int16_t color, int16_t backColor, float initialProgressLevel, float increment = 1);
    void show();
    void update();

private:
    DatapadTFTLCD &_datapadTFTLCD;
    int16_t _x, _y, _width, _height;
    int16_t _color, _backColor;
    float _initialProgressLevel = 0, _increment = 1;
    bool _raising = true;
    void drawRectangle();
};

#endif