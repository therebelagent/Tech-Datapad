//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DoorLockHackingDDS_h
#define DoorLockHackingDDS_h

#include "DatapadDisplaySequence.h"

class DoorLockHackingDDS : public DatapadDisplaySequence
{
public:
    DoorLockHackingDDS(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer);
    void show();
};

#endif