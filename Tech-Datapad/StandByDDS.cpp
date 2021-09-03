//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "StandByDDS.h"
#include "DDSGraphicalUtility.h"
#include "DatapadDisplaySequenceConstants.h"

StandByDDS::StandByDDS(MCUFRIEND_kbv &tftlcd) : DatapadDisplaySequence(tftlcd), _tftlcd(tftlcd) {}

void StandByDDS::show()
{
    reset();
    int16_t centerX = _tftlcd.width() / 2;
    int16_t centerY = _tftlcd.height() / 2;
    int16_t radius = centerX - 1;
    _tftlcd.drawCircle(centerX, centerY, radius, TFT_WHITE);
    DDSGraphicalUtility ddsGraphicalUtility;
    ddsGraphicalUtility.drawInnerCircle(_tftlcd, centerX, centerY, radius - 1, GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
}