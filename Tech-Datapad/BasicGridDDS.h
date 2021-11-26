//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef BasicGridDDS_h
#define BasicGridDDS_h

#include "StandByDDS.h"

class BasicGridDDS : public StandByDDS
{
public:
    BasicGridDDS(IDatapadTFTLCD &datapadTFTLCD);
    void show();
};

#endif