#include "StandByDBC.h"

StandByDBC::StandByDBC(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin) : DatapadButtonsControler(smallWhiteButtonPin, redButtonPin, whiteButtonPin, yellowButtonPin){}

void StandByDBC::turnOnOffButtons()
{
    DatapadButtonsControler::reset();
}