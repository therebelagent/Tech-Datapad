//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "ExplosiveChargesDA.h"

ExplosiveChargesDA::ExplosiveChargesDA(IDatapadDisplaySequence &datapadDisplaySequence, IDatapadButtonsControler &datapadButtonsControler) : DatapadAction(datapadDisplaySequence, datapadButtonsControler) {}

void ExplosiveChargesDA::play()
{
    _datapadDisplaySequence.show();
    _datapadButtonsControler.turnOnOffButtons();
}