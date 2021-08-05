#ifndef DatapadAction_h
#define DatapadAction_h

#include "DatapadDisplaySequence.h"
#include "DatapadButtonsControler.h"

class DatapadAction
{
public:
    DatapadAction(DatapadDisplaySequence *datapadDisplaySequence, DatapadButtonsControler *datapadButtonsControler);
    void play();
    void reset();

private:
    DatapadDisplaySequence *_datapadDisplaySequence;
    DatapadButtonsControler *_datapadButtonsControler;
};

#endif