#ifndef ExplosiveChargesDDS_h
#define ExplosiveChargesDDS_h

#include "DatapadDisplaySequence.h"

class ExplosiveChargesDDS : public DatapadDisplaySequence
{
public:
    ExplosiveChargesDDS(MCUFRIEND_kbv *tftlcd);
    void show();

private:
    MCUFRIEND_kbv *_tftlcd;
};

#endif