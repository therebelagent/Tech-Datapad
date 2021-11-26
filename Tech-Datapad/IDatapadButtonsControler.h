//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef IDatapadButtonsControler_h
#define IDatapadButtonsControler_h

#include "IDatapadLED.h"

class IDatapadButtonsControler
{
public:
    IDatapadButtonsControler(IDatapadLED &smallWhiteDatapadLED, IDatapadLED &redDatapadLED, IDatapadLED &whiteDatapadLED, IDatapadLED &yellowDatapadLED) : _smallWhiteDatapadLED(smallWhiteDatapadLED), _redDatapadLED(redDatapadLED), _whiteDatapadLED(whiteDatapadLED), _yellowDatapadLED(yellowDatapadLED) {}
    virtual IDatapadLED &getSmallWhiteDatapadLED() = 0;
    virtual IDatapadLED &getRedDatapadLED() = 0;
    virtual IDatapadLED &getWhiteDatapadLED() = 0;
    virtual IDatapadLED &getYellowDatapadLED() = 0;
    virtual void turnOnOffButtons() = 0;
    virtual void reset() = 0;

protected:
    IDatapadLED &_smallWhiteDatapadLED, &_redDatapadLED, &_whiteDatapadLED, &_yellowDatapadLED;
};

#endif