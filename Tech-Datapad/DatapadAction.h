//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadAction_h
#define DatapadAction_h

#include "DatapadDisplaySequence.h"
#include "DatapadButtonsControler.h"

class DatapadAction
{
public:
    DatapadAction(DatapadDisplaySequence &datapadDisplaySequence, DatapadButtonsControler &datapadButtonsControler);
    virtual void play();
    void reset();

private:
    DatapadDisplaySequence &_datapadDisplaySequence;
    DatapadButtonsControler &_datapadButtonsControler;
};

#endif