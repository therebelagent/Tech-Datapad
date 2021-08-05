#ifndef EnemyTargetsDDS_h
#define EnemyTargetsDDS_h

#include "BasicGridDDS.h"

class EnemyTargetsDDS: public BasicGridDDS
{
public:
    EnemyTargetsDDS(MCUFRIEND_kbv *tftlcd);
    void show();

private:
    MCUFRIEND_kbv *_tftlcd;
};

#endif