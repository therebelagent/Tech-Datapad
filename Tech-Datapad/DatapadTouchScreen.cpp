//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "Arduino.h"
#include "DatapadTouchScreen.h"
#include "TouchScreenConstants.h"

DatapadTouchScreen::DatapadTouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx) : TouchScreen(xp, yp, xm, ym, rx)
{
    _xm = xm;
    _yp = yp;
}

bool DatapadTouchScreen::isTouching()
{
    bool result = false;

    TSPoint point = TouchScreen::getPoint();
    pinMode(_xm, OUTPUT);
    pinMode(_yp, OUTPUT);
    if (point.z > MINPRESSURE && point.z < MAXPRESSURE)
    {
        result = true;
    }
    return result;
}
