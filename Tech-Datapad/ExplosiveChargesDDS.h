//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef ExplosiveChargesDDS_h
#define ExplosiveChargesDDS_h

#include "DatapadDisplaySequence.h"

class ExplosiveChargesDDS : public DatapadDisplaySequence
{
public:
    ExplosiveChargesDDS(IDatapadTFTLCD &datapadTFTLCD);
    void show();
};

#endif