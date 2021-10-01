//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadDisplaySequence_h
#define DatapadDisplaySequence_h

#include "DatapadTFTLCD.h"

class DatapadDisplaySequence
{

public:
    DatapadDisplaySequence(DatapadTFTLCD &datapadTFTLCD);
    virtual void show();
    void reset();

private:
    DatapadTFTLCD &_datapadTFTLCD;
};

#endif