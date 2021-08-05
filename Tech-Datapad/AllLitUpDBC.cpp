#include "Arduino.h"
#include "AllLitUpDBC.h"

AllLitUpDBC::AllLitUpDBC(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin) : DatapadButtonsControler(smallWhiteButtonPin, redButtonPin, whiteButtonPin, yellowButtonPin) {}

void AllLitUpDBC::turnOnOffButtons()
{
    digitalWrite(DatapadButtonsControler::getSmallWhiteButtonPin(), HIGH);
    digitalWrite(DatapadButtonsControler::getRedButtonPin(), HIGH);
    digitalWrite(DatapadButtonsControler::getWhiteButtonPin(), HIGH);
    digitalWrite(DatapadButtonsControler::getYellowButtonPin(), HIGH);
}