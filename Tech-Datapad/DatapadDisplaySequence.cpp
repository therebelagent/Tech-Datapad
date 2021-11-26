//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadDisplaySequence.h"

DatapadDisplaySequence::DatapadDisplaySequence(IDatapadTFTLCD &datapadTFTLCD) : IDatapadDisplaySequence(datapadTFTLCD) {}

void DatapadDisplaySequence::reset()
{
    _datapadTFTLCD.fillScreen(DISPLAY_BACK_COLOR);
}