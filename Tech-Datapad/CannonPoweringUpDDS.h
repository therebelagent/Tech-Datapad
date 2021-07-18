#ifndef CannonPoweringUpDDS_h
#define CannonPoweringUpDDS_h

#include "BasicGridDDS.h"

class CannonPoweringUpDDS : public BasicGridDDS
{
public:
    CannonPoweringUpDDS(MCUFRIEND_kbv *tftlcd);
    void show();

private:
    MCUFRIEND_kbv *_tftlcd;
};

#endif