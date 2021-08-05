#include "Arduino.h"
#include "ExplosiveChargesDBC.h"

ExplosiveChargesDBC::ExplosiveChargesDBC(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin) : DatapadButtonsControler(smallWhiteButtonPin, redButtonPin, whiteButtonPin, yellowButtonPin) {}

void ExplosiveChargesDBC::turnOnOffButtons()
{
    getSmallWhiteDatapadLED()->turnOff();
    getRedDatapadLED()->turnOn();
    getWhiteDatapadLED()->turnOff();
    getYellowDatapadLED()->turnOff();
}