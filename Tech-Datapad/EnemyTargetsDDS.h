//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef EnemyTargetsDDS_h
#define EnemyTargetsDDS_h

#include "BasicGridDDS.h"

class EnemyTargetsDDS : public BasicGridDDS
{
public:
    EnemyTargetsDDS(MCUFRIEND_kbv &tftlcd);
    void show();

private:
    MCUFRIEND_kbv &_tftlcd;
};

#endif