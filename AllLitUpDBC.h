#ifndef AllLitUpDBC_h
#define AllLitUpDBC_h

#include "DatapadButtonsControler.h"

class AllLitUpDBC : public DatapadButtonsControler
{
public:
    AllLitUpDBC(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin);
    void turnOnOffButtons();
};

#endif