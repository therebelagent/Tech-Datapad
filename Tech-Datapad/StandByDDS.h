//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef StandByDDS_h
#define StandByDDS_h

#include "DatapadDisplaySequence.h"

class StandByDDS : public DatapadDisplaySequence
{
public:
    StandByDDS(DatapadTFTLCD &datapadTFTLCD);
    void show();

private:
    DatapadTFTLCD &_datapadTFTLCD;
};

#endif