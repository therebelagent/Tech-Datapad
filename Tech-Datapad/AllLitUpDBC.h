//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

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