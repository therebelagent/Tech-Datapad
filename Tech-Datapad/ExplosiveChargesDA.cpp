#include "ExplosiveChargesDA.h"

ExplosiveChargesDA::ExplosiveChargesDA(DatapadDisplaySequence *datapadDisplaySequence, DatapadButtonsControler *datapadButtonsControler) : DatapadAction(datapadDisplaySequence, datapadButtonsControler)
{
    _datapadDisplaySequence = datapadDisplaySequence;
    _datapadButtonsControler = datapadButtonsControler;
}

void ExplosiveChargesDA::play()
{
    _datapadDisplaySequence->show();
    _datapadButtonsControler->turnOnOffButtons();
}