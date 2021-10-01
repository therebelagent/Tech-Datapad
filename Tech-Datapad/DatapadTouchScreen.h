//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadTouchScreen_h
#define DatapadTouchScreen_h

#include "TouchScreen.h"

struct DatapadDisplayPoint
{
    int16_t x;
    int16_t y;
};

class DatapadTouchScreen : public TouchScreen
{
public:
    DatapadTouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx);
    bool isTouching();
    DatapadDisplayPoint getDatapadDisplayPoint();

private:
    const uint8_t _xm;
    const uint8_t _yp;
    DatapadDisplayPoint _datapadDisplayPoint;
};

#endif