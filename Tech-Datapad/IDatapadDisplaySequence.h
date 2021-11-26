//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef IDatapadDisplaySequence_h
#define IDatapadDisplaySequence_h

#include "DatapadTFTLCD.h"
#include "DatapadDisplaySequenceConstants.h"

class IDatapadDisplaySequence
{

public:
    IDatapadDisplaySequence(IDatapadTFTLCD &datapadTFTLCD) : _datapadTFTLCD(datapadTFTLCD) {}
    virtual void show() = 0;
    virtual void reset() = 0;

protected:
    IDatapadTFTLCD &_datapadTFTLCD;
};

#endif