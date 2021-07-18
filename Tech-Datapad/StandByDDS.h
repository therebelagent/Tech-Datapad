#ifndef StandByDDS_h
#define StandByDDS_h

#include "DatapadDisplaySequence.h"

class StandByDDS : public DatapadDisplaySequence
{
public:
    StandByDDS(MCUFRIEND_kbv *tftlcd);
    void show();

private:
    MCUFRIEND_kbv *_tftlcd;
};

#endif