//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include <Arduino.h>
#include "DiagnosticDBC.h"

DiagnosticDBC::DiagnosticDBC(IDatapadLED &smallWhiteDatapadLED, IDatapadLED &redDatapadLED, IDatapadLED &whiteDatapadLED, IDatapadLED &yellowDatapadLED) : DatapadButtonsControler(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED) {}
void DiagnosticDBC::turnOnOffButtons()
{
    getSmallWhiteDatapadLED().turnOn();
    delay(500);
    getRedDatapadLED().turnOn();
    delay(500);
    getWhiteDatapadLED().turnOn();
    delay(500);
    getYellowDatapadLED().turnOn();
    delay(500);
    reset();
}