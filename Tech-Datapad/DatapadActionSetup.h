#ifndef DatapadActionSetup_h
#define DatapadActionSetup_h

#include <MCUFRIEND_kbv.h>

class DatapadActionSetup
{
public:
    DatapadActionSetup(MCUFRIEND_kbv *tftlcd, uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin);
    MCUFRIEND_kbv getTftlcd();
    uint8_t getSmallWhiteButtonPin();
    uint8_t getRedButtonPin();
    uint8_t getWhiteButtonPin();
    uint8_t getYellowButtonPin();

private:
    MCUFRIEND_kbv *_tftlcd;
    uint8_t _smallWhiteButtonPin, _redButtonPin, _whiteButtonPin, _yellowButtonPin;
};

#endif