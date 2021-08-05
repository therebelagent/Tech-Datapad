#ifndef DatapadButtonsControler_h
#define DatapadButtonsControler_h

#include <stdint.h>

class DatapadButtonsControler
{
public:
    DatapadButtonsControler(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin);
    virtual uint8_t getSmallWhiteButtonPin();
    virtual uint8_t getRedButtonPin();
    virtual uint8_t getWhiteButtonPin();
    virtual uint8_t getYellowButtonPin();
    virtual void turnOnOffButtons();
    virtual void reset();

private:
    uint8_t _smallWhiteButtonPin, _redButtonPin, _whiteButtonPin, _yellowButtonPin;
};

#endif