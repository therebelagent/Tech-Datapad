#ifndef DatapadTouchScreen_h
#define DatapadTouchScreen_h

#include "TouchScreen.h"

class DatapadTouchScreen : public TouchScreen
{
public:
    DatapadTouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx);
    bool isTouching();

private:
    uint8_t _xm;
    uint8_t _yp;
};

#endif