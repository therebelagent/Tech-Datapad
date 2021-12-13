//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef ExplosiveChargesDA_h
#define ExplosiveChargesDA_h

#include "DatapadAction.h"

class ExplosiveChargesDA : public DatapadAction
{
public:
    ExplosiveChargesDA(IDatapadDisplaySequence &datapadDisplaySequence, IDatapadButtonsControler &datapadButtonsControler);
    void play();
};

#endif