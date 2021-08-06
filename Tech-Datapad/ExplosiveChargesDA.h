#ifndef ExplosiveChargesDA_h
#define ExplosiveChargesDA_h

#include "DatapadAction.h"

class ExplosiveChargesDA : public DatapadAction
{
public:
    ExplosiveChargesDA(DatapadDisplaySequence *datapadDisplaySequence, DatapadButtonsControler *datapadButtonsControler);
    virtual void play();

private:
    DatapadDisplaySequence *_datapadDisplaySequence;
    DatapadButtonsControler *_datapadButtonsControler;
};

#endif