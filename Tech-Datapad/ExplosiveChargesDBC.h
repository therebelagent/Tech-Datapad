#ifndef ExplosiveChargesDBC_h
#define ExplosiveChargesDBC_h

#include "DatapadButtonsControler.h"

class ExplosiveChargesDBC : public DatapadButtonsControler
{
public:
    ExplosiveChargesDBC(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin);
    void turnOnOffButtons();
};

#endif