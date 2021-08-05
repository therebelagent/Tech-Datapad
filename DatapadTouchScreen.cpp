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