//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef IDatapadAction_h
#define IDatapadAction_h

#include "IDatapadDisplaySequence.h"
#include "IDatapadButtonsControler.h"

class IDatapadAction
{
public:
    IDatapadAction(IDatapadDisplaySequence &datapadDisplaySequence, IDatapadButtonsControler &datapadButtonsControler) : _datapadDisplaySequence(datapadDisplaySequence), _datapadButtonsControler(datapadButtonsControler) {}
    virtual void play() = 0;
    virtual void reset() = 0;

protected:
    IDatapadDisplaySequence &_datapadDisplaySequence;
    IDatapadButtonsControler &_datapadButtonsControler;
};

#endif