//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef LifeformAnalyzerDDS_h
#define LifeformAnalyzerDDS_h

#include "StandByDDS.h"

class LifeformAnalyzerDDS : public StandByDDS
{
public:
    LifeformAnalyzerDDS(DatapadTFTLCD &datapadTFTLCD);
    void show();

private:
    DatapadTFTLCD &_datapadTFTLCD;
};

#endif