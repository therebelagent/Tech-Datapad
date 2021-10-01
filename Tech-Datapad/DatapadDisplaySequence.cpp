//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadDisplaySequence.h"
#include "DatapadDisplaySequenceConstants.h"

DatapadDisplaySequence::DatapadDisplaySequence(DatapadTFTLCD &datapadTFTLCD) : _datapadTFTLCD(datapadTFTLCD) {}

void DatapadDisplaySequence::reset()
{
    int16_t height = (((_datapadTFTLCD.width() / 2) + 12) * 2);
    int16_t topY = (_datapadTFTLCD.height() / 2) - (height / 2) + 1;
    _datapadTFTLCD.fillRect(0, topY, _datapadTFTLCD.width(), height, DISPLAY_BACK_COLOR);
}