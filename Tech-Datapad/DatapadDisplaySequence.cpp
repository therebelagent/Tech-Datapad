//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadDisplaySequence.h"

DatapadDisplaySequence::DatapadDisplaySequence(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer) : IDatapadDisplaySequence(datapadTFTLCD, datapadSoundPlayer) {}

void DatapadDisplaySequence::reset()
{
    _datapadTFTLCD.fillScreen(DISPLAY_BACK_COLOR);
}