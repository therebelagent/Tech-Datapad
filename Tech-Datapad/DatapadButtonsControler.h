#ifndef DatapadButtonsControler_h
#define DatapadButtonsControler_h

#include <stdint.h>
#include "DatapadLED.h"

class DatapadButtonsControler
{
public:
    DatapadButtonsControler(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin);
    DatapadLED *getSmallWhiteDatapadLED();
    DatapadLED *getRedDatapadLED();
    DatapadLED *getWhiteDatapadLED();
    DatapadLED *getYellowDatapadLED();
    virtual void turnOnOffButtons();
    void reset();

private:
    DatapadLED *_smallWhiteDatapadLED, *_redDatapadLED, *_whiteDatapadLED, *_yellowDatapadLED;
};

#endif