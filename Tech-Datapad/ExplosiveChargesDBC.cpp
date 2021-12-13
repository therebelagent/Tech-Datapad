//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "ExplosiveChargesDBC.h"
#include "DDSSoundPlayer.h"

ExplosiveChargesDBC::ExplosiveChargesDBC(IDatapadLED &smallWhiteDatapadLED, IDatapadLED &redDatapadLED, IDatapadLED &whiteDatapadLED, IDatapadLED &yellowDatapadLED, IDatapadSoundPlayer &datapadSoundPlayer) : DatapadButtonsControler(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED, datapadSoundPlayer) {}

void ExplosiveChargesDBC::turnOnOffButtons()
{
    getSmallWhiteDatapadLED().turnOff();
    DDSSoundPlayer ddsSoundPlayer = DDSSoundPlayer(_datapadSoundPlayer);
    ddsSoundPlayer.playButtonTone();
    getRedDatapadLED().turnOn();
    getWhiteDatapadLED().turnOff();
    getYellowDatapadLED().turnOff();
}