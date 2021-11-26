//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DiagnosticDBC_h
#define DiagnosticDBC_h

#include "DatapadButtonsControler.h"

class DiagnosticDBC : public DatapadButtonsControler
{
public:
    DiagnosticDBC(IDatapadLED &smallWhiteDatapadLED, IDatapadLED &redDatapadLED, IDatapadLED &whiteDatapadLED, IDatapadLED &yellowDatapadLED);
    void turnOnOffButtons();
};

#endif