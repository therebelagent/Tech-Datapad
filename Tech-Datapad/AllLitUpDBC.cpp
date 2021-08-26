//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "AllLitUpDBC.h"

AllLitUpDBC::AllLitUpDBC(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin) : DatapadButtonsControler(smallWhiteButtonPin, redButtonPin, whiteButtonPin, yellowButtonPin) {}

void AllLitUpDBC::turnOnOffButtons()
{
    getSmallWhiteDatapadLED()->turnOn();
    getRedDatapadLED()->turnOn();
    getWhiteDatapadLED()->turnOn();
    getYellowDatapadLED()->turnOn();
}