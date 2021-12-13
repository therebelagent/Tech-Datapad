//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include <Arduino.h>
#include "DiagnosticDBC.h"
#include "DDSSoundPlayer.h"

DiagnosticDBC::DiagnosticDBC(IDatapadLED &smallWhiteDatapadLED, IDatapadLED &redDatapadLED, IDatapadLED &whiteDatapadLED, IDatapadLED &yellowDatapadLED, IDatapadSoundPlayer &datapadSoundPlayer) : DatapadButtonsControler(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED, datapadSoundPlayer) {}
void DiagnosticDBC::turnOnOffButtons()
{
    DDSSoundPlayer ddsSoundPlayer = DDSSoundPlayer(_datapadSoundPlayer);
    ddsSoundPlayer.playButtonTone();
    getSmallWhiteDatapadLED().turnOn();
    delay(500);
    ddsSoundPlayer.playButtonTone();
    getRedDatapadLED().turnOn();
    delay(500);
    ddsSoundPlayer.playButtonTone();
    getWhiteDatapadLED().turnOn();
    delay(500);
    ddsSoundPlayer.playButtonTone();
    getYellowDatapadLED().turnOn();
    delay(500);
    reset();
}