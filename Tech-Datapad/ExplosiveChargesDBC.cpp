//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "ExplosiveChargesDBC.h"

ExplosiveChargesDBC::ExplosiveChargesDBC(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin) : DatapadButtonsControler(smallWhiteButtonPin, redButtonPin, whiteButtonPin, yellowButtonPin) {}

void ExplosiveChargesDBC::turnOnOffButtons()
{
    getSmallWhiteDatapadLED()->turnOff();
    getRedDatapadLED()->turnOn();
    getWhiteDatapadLED()->turnOff();
    getYellowDatapadLED()->turnOff();
}