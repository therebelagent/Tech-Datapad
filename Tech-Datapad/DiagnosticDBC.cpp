//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include <Arduino.h>
#include "DiagnosticDBC.h"

DiagnosticDBC::DiagnosticDBC(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin) : DatapadButtonsControler(smallWhiteButtonPin, redButtonPin, whiteButtonPin, yellowButtonPin) {}

void DiagnosticDBC::turnOnOffButtons()
{
    getSmallWhiteDatapadLED()->turnOn();
    delay(500);
    getRedDatapadLED()->turnOn();
    delay(500);
    getWhiteDatapadLED()->turnOn();
    delay(500);
    getYellowDatapadLED()->turnOn();
    delay(500);
    reset();
}