//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef CommSignalTrackerDDS_h
#define CommSignalTrackerDDS_h

#include "DatapadDisplaySequence.h"

class CommSignalTrackerDDS : public DatapadDisplaySequence
{
public:
    CommSignalTrackerDDS(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer);
    void show();
};

#endif