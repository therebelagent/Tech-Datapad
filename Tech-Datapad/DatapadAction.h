//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadAction_h
#define DatapadAction_h

#include "IDatapadAction.h"

class DatapadAction : public IDatapadAction
{
public:
    DatapadAction(IDatapadDisplaySequence &datapadDisplaySequence, IDatapadButtonsControler &datapadButtonsControler);
    virtual void play();
    void reset();
};

#endif