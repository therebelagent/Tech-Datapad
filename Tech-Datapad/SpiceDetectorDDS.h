//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef SpiceDetectorDDS_h
#define SpiceDetectorDDS_h

#include "BasicGridDDS.h"

class SpiceDetectorDDS : public BasicGridDDS
{
public:
    SpiceDetectorDDS(DatapadTFTLCD &datapadTFTLCD);
    void show();

private:
    DatapadTFTLCD &_datapadTFTLCD;
};

#endif