//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadDisplayButton_h
#define DatapadDisplayButton_h

#include "DatapadTFTLCD.h"
#include "IDatapadSoundPlayer.h"
#include "DatapadTouchScreen.h"
#include "DatapadActionFactory.h"
#include "DDSSoundPlayer.h"

class DatapadDisplayButton
{

public:
    DatapadDisplayButton();
    virtual void initialize(IDatapadTFTLCD *datapadTFTLCD, IDatapadSoundPlayer *datapadSoundPlayer, DatapadActionType datapadActionType, int16_t x, int16_t y, uint16_t width, const char *text, uint16_t color, uint16_t backColor, uint16_t pressColor, const GFXfont *gfxFont = NULL);
    virtual void draw();
    virtual void drawInverted();
    virtual bool contains(DatapadDisplayPoint datapadDisplayPoint);
    virtual void press();
    virtual DatapadActionType getDatapadActionType();

private:
    IDatapadTFTLCD *_datapadTFTLCD = nullptr;
    DDSSoundPlayer *_ddsSoundPlayer = nullptr;
    DatapadActionType _datapadActionType;
    int16_t _x, _y, _width, _height, _textY;
    DatapadDisplayPoint _aDatapadDisplayPoint, _bDatapadDisplayPoint, _cDatapadDisplayPoint;
    const char *_text = nullptr;
    uint16_t _color, _backColor, _pressColor;
    const GFXfont *_gfxFont = nullptr;
};

#endif