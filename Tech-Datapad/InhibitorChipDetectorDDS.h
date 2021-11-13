//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef InhibitorChipDetectorDDS_h
#define InhibitorChipDetectorDDS_h

#include "DatapadDisplaySequence.h"

class InhibitorChipDetectorDDS : public DatapadDisplaySequence
{
public:
    InhibitorChipDetectorDDS(DatapadTFTLCD &datapadTFTLCD);
    void show();

private:
    DatapadTFTLCD &_datapadTFTLCD;
};

#endif