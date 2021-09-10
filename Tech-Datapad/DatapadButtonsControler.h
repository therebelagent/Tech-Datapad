//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadButtonsControler_h
#define DatapadButtonsControler_h

#include <stdint.h>
#include "DatapadLED.h"

class DatapadButtonsControler
{
public:
    DatapadButtonsControler(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin);
    DatapadLED &getSmallWhiteDatapadLED();
    DatapadLED &getRedDatapadLED();
    DatapadLED &getWhiteDatapadLED();
    DatapadLED &getYellowDatapadLED();
    virtual void turnOnOffButtons();
    void reset();

private:
    DatapadLED _smallWhiteDatapadLED, _redDatapadLED, _whiteDatapadLED, _yellowDatapadLED;
};

#endif