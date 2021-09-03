//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef RearAxleStabilizerCalibrationDDS_h
#define RearAxleStabilizerCalibrationDDS_h

#include "StandByDDS.h"

class RearAxleStabilizerCalibrationDDS : public StandByDDS
{
public:
    RearAxleStabilizerCalibrationDDS(MCUFRIEND_kbv &tftlcd);
    void show();

private:
    MCUFRIEND_kbv &_tftlcd;
};

#endif