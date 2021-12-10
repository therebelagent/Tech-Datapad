//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadDisplayButton.h"

class DatapadDisplayButtonHelper
{
public:
    void drawTriangle(IDatapadTFTLCD *datapadTFTLCD, DatapadDisplayPoint aDatapadDisplayPoint, DatapadDisplayPoint bDatapadDisplayPoint, DatapadDisplayPoint cDatapadDisplayPoint, int16_t height, const char *text, uint16_t color, uint16_t backColor, int16_t textY, const GFXfont *gfxFont = NULL)
    {
        datapadTFTLCD->fillTriangle(aDatapadDisplayPoint.x, aDatapadDisplayPoint.y, bDatapadDisplayPoint.x, bDatapadDisplayPoint.y, cDatapadDisplayPoint.x, cDatapadDisplayPoint.y, backColor);
        datapadTFTLCD->drawTriangle(aDatapadDisplayPoint.x, aDatapadDisplayPoint.y, bDatapadDisplayPoint.x, bDatapadDisplayPoint.y, cDatapadDisplayPoint.x, cDatapadDisplayPoint.y, color);
        datapadTFTLCD->printCenteredText(text, gfxFont, bDatapadDisplayPoint.x, textY, color);
    }

    void drawFilledTriangle(IDatapadTFTLCD *datapadTFTLCD, DatapadDisplayPoint aDatapadDisplayPoint, DatapadDisplayPoint bDatapadDisplayPoint, DatapadDisplayPoint cDatapadDisplayPoint, int16_t height, const char *text, uint16_t color, uint16_t textColor, int16_t textY, const GFXfont *gfxFont = NULL)
    {
        datapadTFTLCD->fillTriangle(aDatapadDisplayPoint.x, aDatapadDisplayPoint.y, bDatapadDisplayPoint.x, bDatapadDisplayPoint.y, cDatapadDisplayPoint.x, cDatapadDisplayPoint.y, color);
        datapadTFTLCD->printCenteredText(text, gfxFont, bDatapadDisplayPoint.x, textY, textColor);
    }

    bool isPointInTriangle(DatapadDisplayPoint searchDatapadDisplayPoint, DatapadDisplayPoint aDatapadDisplayPoint, DatapadDisplayPoint bDatapadDisplayPoint, DatapadDisplayPoint cDatapadDisplayPoint)
    {
        int16_t as_x = searchDatapadDisplayPoint.x - aDatapadDisplayPoint.x;
        int16_t as_y = searchDatapadDisplayPoint.y - aDatapadDisplayPoint.y;
        bool s_ab = (bDatapadDisplayPoint.x - aDatapadDisplayPoint.x) * as_y - (bDatapadDisplayPoint.y - aDatapadDisplayPoint.y) * as_x > 0;
        if ((cDatapadDisplayPoint.x - aDatapadDisplayPoint.x) * as_y - (cDatapadDisplayPoint.y - aDatapadDisplayPoint.y) * as_x > 0 == s_ab)
            return false;
        if ((cDatapadDisplayPoint.x - bDatapadDisplayPoint.x) * (searchDatapadDisplayPoint.y - bDatapadDisplayPoint.y) - (cDatapadDisplayPoint.y - bDatapadDisplayPoint.y) * (searchDatapadDisplayPoint.x - bDatapadDisplayPoint.x) > 0 != s_ab)
            return false;
        return true;
    }
};

DatapadDisplayButton::DatapadDisplayButton()
{
    _datapadTone.frequency = 2500;
    _datapadTone.duration = 75;
}

void DatapadDisplayButton::initialize(IDatapadTFTLCD *datapadTFTLCD, IDatapadSoundPlayer *datapadSoundPlayer, DatapadActionType datapadActionType, int16_t x, int16_t y, uint16_t width, const char *text, uint16_t color, uint16_t backColor, uint16_t pressColor, const GFXfont *gfxFont = NULL)
{
    _datapadTFTLCD = datapadTFTLCD;
    _datapadSoundPlayer = datapadSoundPlayer;
    _datapadActionType = datapadActionType;
    _x = x;
    _y = y;
    _width = width;
    _text = text;
    _color = color;
    _backColor = backColor;
    _pressColor = pressColor;
    _gfxFont = gfxFont;
    _height = (sqrt(3) * _width) / 2;
}

void DatapadDisplayButton::draw()
{
    _aDatapadDisplayPoint.x = _x;
    _aDatapadDisplayPoint.y = _y;
    _bDatapadDisplayPoint.x = _x + (_width / 2);
    _bDatapadDisplayPoint.y = _y - _height;
    _cDatapadDisplayPoint.x = _x + _width;
    _cDatapadDisplayPoint.y = _y;
    _textY = _aDatapadDisplayPoint.y - (_height - (_height * 2) / 3);
    DatapadDisplayButtonHelper datapadDisplayButtonHelper;
    datapadDisplayButtonHelper.drawTriangle(_datapadTFTLCD, _aDatapadDisplayPoint, _bDatapadDisplayPoint, _cDatapadDisplayPoint, _height, _text, _color, _backColor, _textY, _gfxFont);
}

void DatapadDisplayButton::drawInverted()
{
    _aDatapadDisplayPoint.x = _x - (_width / 2);
    _aDatapadDisplayPoint.y = _y - _height;
    _bDatapadDisplayPoint.x = _x;
    _bDatapadDisplayPoint.y = _y;
    _cDatapadDisplayPoint.x = _x + (_width / 2);
    _cDatapadDisplayPoint.y = _y - _height;
    _textY = _bDatapadDisplayPoint.y - ((_height * 2) / 3);
    DatapadDisplayButtonHelper datapadDisplayButtonHelper;
    datapadDisplayButtonHelper.drawTriangle(_datapadTFTLCD, _aDatapadDisplayPoint, _bDatapadDisplayPoint, _cDatapadDisplayPoint, _height, _text, _color, _backColor, _textY, _gfxFont);
}

bool DatapadDisplayButton::contains(DatapadDisplayPoint datapadDisplayPoint)
{
    DatapadDisplayButtonHelper datapadDisplayButtonHelper;
    return datapadDisplayButtonHelper.isPointInTriangle(datapadDisplayPoint, _aDatapadDisplayPoint, _bDatapadDisplayPoint, _cDatapadDisplayPoint);
}

void DatapadDisplayButton::press()
{
    _datapadSoundPlayer->playTone(_datapadTone);
    DatapadDisplayButtonHelper datapadDisplayButtonHelper;
    datapadDisplayButtonHelper.drawFilledTriangle(_datapadTFTLCD, _aDatapadDisplayPoint, _bDatapadDisplayPoint, _cDatapadDisplayPoint, _height, _text, _pressColor, _backColor, _textY, _gfxFont);
    delay(250);
    datapadDisplayButtonHelper.drawTriangle(_datapadTFTLCD, _aDatapadDisplayPoint, _bDatapadDisplayPoint, _cDatapadDisplayPoint, _height, _text, _color, _backColor, _textY, _gfxFont);
}

DatapadActionType DatapadDisplayButton::getDatapadActionType() { return _datapadActionType; }