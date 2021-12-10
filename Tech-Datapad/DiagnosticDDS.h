//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DiagnosticDDS_h
#define DiagnosticDDS_h

#include "StandByDDS.h"

class DiagnosticDDS : public StandByDDS
{
public:
    DiagnosticDDS(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer);
    void show();
};

#endif