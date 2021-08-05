#include "DatapadAction.h"

DatapadAction::DatapadAction(DatapadDisplaySequence *datapadDisplaySequence, DatapadButtonsControler *datapadButtonsControler)
{
    _datapadDisplaySequence = datapadDisplaySequence;
    _datapadButtonsControler = datapadButtonsControler;
}

void DatapadAction::play()
{
    _datapadButtonsControler->turnOnOffButtons();
    _datapadDisplaySequence->show();
}

void DatapadAction::reset()
{
    _datapadButtonsControler->reset();
    _datapadDisplaySequence->reset();
}
