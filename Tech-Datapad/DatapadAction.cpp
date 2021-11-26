//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadAction.h"

DatapadAction::DatapadAction(IDatapadDisplaySequence &datapadDisplaySequence, IDatapadButtonsControler &datapadButtonsControler) : IDatapadAction(datapadDisplaySequence, datapadButtonsControler) {}

void DatapadAction::play()
{
    _datapadButtonsControler.turnOnOffButtons();
    _datapadDisplaySequence.show();
}

void DatapadAction::reset()
{
    _datapadButtonsControler.reset();
    _datapadDisplaySequence.reset();
}