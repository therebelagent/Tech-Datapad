//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadButtonsControler_h
#define DatapadButtonsControler_h

#include <stdint.h>
#include "IDatapadButtonsControler.h"
#include "IDatapadLED.h"
#include "DatapadLED.h"

class DatapadButtonsControler : public IDatapadButtonsControler
{
public:
    DatapadButtonsControler(IDatapadLED &smallWhiteDatapadLED, IDatapadLED &redDatapadLED, IDatapadLED &whiteDatapadLED, IDatapadLED &yellowDatapadLED);
    IDatapadLED &getSmallWhiteDatapadLED();
    IDatapadLED &getRedDatapadLED();
    IDatapadLED &getWhiteDatapadLED();
    IDatapadLED &getYellowDatapadLED();
    virtual void turnOnOffButtons();
    void reset();
};

#endif