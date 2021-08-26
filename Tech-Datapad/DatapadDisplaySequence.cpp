//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadDisplaySequence.h"
#include "DatapadDisplaySequenceConstants.h"

DatapadDisplaySequence::DatapadDisplaySequence(MCUFRIEND_kbv *tftlcd) { _tftlcd = tftlcd; }

void DatapadDisplaySequence::reset()
{
    int16_t height = (((_tftlcd->width() / 2) + 12) * 2);
    int16_t topY = (_tftlcd->height() / 2) - (height / 2) + 1;
    _tftlcd->fillRect(0, topY, _tftlcd->width(), height, DISPLAY_BACK_COLOR);
}