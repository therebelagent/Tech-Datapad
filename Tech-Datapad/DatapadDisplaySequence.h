//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadDisplaySequence_h
#define DatapadDisplaySequence_h

#include "IDatapadDisplaySequence.h"

class DatapadDisplaySequence : public IDatapadDisplaySequence
{

public:
    DatapadDisplaySequence(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer);
    void show();
    void reset();
};

#endif