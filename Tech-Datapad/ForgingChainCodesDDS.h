//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef ForgingChainCodesDDS_h
#define ForgingChainCodesDDS_h

#include "StandByDDS.h"

class ForgingChainCodesDDS : public StandByDDS
{
public:
    ForgingChainCodesDDS(DatapadTFTLCD &datapadTFTLCD);
    void show();

private:
    DatapadTFTLCD &_datapadTFTLCD;
};

#endif