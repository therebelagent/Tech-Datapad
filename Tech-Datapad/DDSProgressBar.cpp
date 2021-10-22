//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DDSProgressBar.h"

DDSProgressBar::DDSProgressBar(DatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t width, int16_t height, int16_t color, int16_t backColor, float initialProgressLevel, float increment = 1) : _datapadTFTLCD(datapadTFTLCD), _x(x), _y(y), _width(width), _height(height), _color(color), _backColor(backColor), _initialProgressLevel(initialProgressLevel), _increment(increment)
{
    if (initialProgressLevel > 100)
        _initialProgressLevel = 100;
}

void DDSProgressBar::show() { drawRectangle(); }

void DDSProgressBar::update()
{
    if (_raising)
    {
        _initialProgressLevel = _initialProgressLevel + _increment;
    }
    else
    {
        _initialProgressLevel = _initialProgressLevel - _increment;
    }
    if (_initialProgressLevel > 100)
    {
        _initialProgressLevel = 100;
        _raising = false;
    }
    else if (_initialProgressLevel < 0)
    {
        _initialProgressLevel = 0;
        _raising = true;
    }
    drawRectangle();
}

void DDSProgressBar::drawRectangle()
{
    int16_t activeRectangleHeight = _height * (_initialProgressLevel / 100);
    int16_t inactiveRectangleHeight = _height - activeRectangleHeight;
    int16_t activeRectangleTop = _y + _height - activeRectangleHeight;
    _datapadTFTLCD.fillRect(_x, _y, _width, inactiveRectangleHeight, _backColor);
    _datapadTFTLCD.fillRect(_x, activeRectangleTop, _width, activeRectangleHeight, _color);
}