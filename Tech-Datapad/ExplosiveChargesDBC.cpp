#include "Arduino.h"
#include "ExplosiveChargesDBC.h"

ExplosiveChargesDBC::ExplosiveChargesDBC(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin) : DatapadButtonsControler(smallWhiteButtonPin, redButtonPin, whiteButtonPin, yellowButtonPin){}

void ExplosiveChargesDBC::turnOnOffButtons()
{
    digitalWrite(DatapadButtonsControler::getSmallWhiteButtonPin(), LOW);
    digitalWrite(DatapadButtonsControler::getRedButtonPin(), HIGH);
    digitalWrite(DatapadButtonsControler::getWhiteButtonPin(), LOW);
    digitalWrite(DatapadButtonsControler::getYellowButtonPin(), LOW);
}