//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "StandByDDS.h"
#include "DatapadDisplaySequenceConstants.h"

StandByDDS::StandByDDS(DatapadTFTLCD &datapadTFTLCD) : DatapadDisplaySequence(datapadTFTLCD), _datapadTFTLCD(datapadTFTLCD) {}

void StandByDDS::show()
{
    int16_t centerX = _datapadTFTLCD.width() / 2;
    int16_t centerY = _datapadTFTLCD.height() / 2;
    int16_t radius = centerX - 1;
    _datapadTFTLCD.drawInnerCircle(centerX, centerY, radius, GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
}