//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DDSBlinkingDot.h"

DDSBlinkingDot::DDSBlinkingDot(IDatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t radius, uint16_t colour, uint16_t backColour) : _datapadTFTLCD(datapadTFTLCD), _x(x), _y(y), _radius(radius), _colour(colour), _backColor(backColour) {}

DDSBlinkingDot::DDSBlinkingDot(IDatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t radius, uint16_t colour, uint16_t backColour, IDatapadSoundPlayer *datapadSoundPlayer, DatapadTone datapadTone) : _datapadTFTLCD(datapadTFTLCD), _x(x), _y(y), _radius(radius), _colour(colour), _backColor(backColour), _datapadSoundPlayer(datapadSoundPlayer), _datapadTone(datapadTone) {}

void DDSBlinkingDot::update()
{
    if (_previousMillis > 0)
    {
        _elapsed += millis() - _previousMillis;
        if (_elapsed < 100)
        {
            _state = 0;
        }
        else if (_elapsed < 650)
        {
            _state = 1;
        }
        else if (_elapsed < 1500)
        {
            _state = 2;
        }
        else if (_elapsed < 2000)
        {
            _elapsed = 0;
        }
    }
    _previousMillis = millis();
    int16_t colour;
    switch (_state)
    {
    case 0:
        colour = TFT_DARKGREY;
        break;
    case 1:
        if (_datapadSoundPlayer != nullptr)
        {
            _datapadSoundPlayer->playTone(_datapadTone);
        }
        colour = _colour;
        break;
    case 2:
        colour = _backColor;
        break;
    }
    _datapadTFTLCD.fillCircle(_x, _y, _radius, colour);
}