//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "AllLitUpDBC.h"

AllLitUpDBC::AllLitUpDBC(IDatapadLED &smallWhiteDatapadLED, IDatapadLED &redDatapadLED, IDatapadLED &whiteDatapadLED, IDatapadLED &yellowDatapadLED, IDatapadSoundPlayer &datapadSoundPlayer) : DatapadButtonsControler(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED, datapadSoundPlayer) {}

void AllLitUpDBC::turnOnOffButtons()
{
    getSmallWhiteDatapadLED().turnOn();
    getRedDatapadLED().turnOn();
    getWhiteDatapadLED().turnOn();
    getYellowDatapadLED().turnOn();
}