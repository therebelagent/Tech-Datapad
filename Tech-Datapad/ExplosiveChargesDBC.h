//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef ExplosiveChargesDBC_h
#define ExplosiveChargesDBC_h

#include "DatapadButtonsControler.h"

class ExplosiveChargesDBC : public DatapadButtonsControler
{
public:
    ExplosiveChargesDBC(IDatapadLED &smallWhiteDatapadLED, IDatapadLED &redDatapadLED, IDatapadLED &whiteDatapadLED, IDatapadLED &yellowDatapadLED);
    void turnOnOffButtons();
};

#endif