#ifndef BasicGridDDS_h
#define BasicGridDDS_h

#include "StandByDDS.h"

class BasicGridDDS : public StandByDDS
{
public:
    BasicGridDDS(MCUFRIEND_kbv *tftlcd);
    void show();

private:
    MCUFRIEND_kbv *_tftlcd;
};

#endif