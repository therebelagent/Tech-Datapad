//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "BasicGridDDS.h"
#include "DDSGraphicalUtility.h"
#include "DatapadDisplaySequenceConstants.h"

BasicGridDDS::BasicGridDDS(MCUFRIEND_kbv &tftlcd) : StandByDDS(tftlcd), _tftlcd(tftlcd) {}

void BasicGridDDS::show()
{
    StandByDDS::show();
    int16_t centerX = _tftlcd.width() / 2;
    int16_t centerY = _tftlcd.height() / 2;
    int16_t radius = centerX - 1;
    DDSGraphicalUtility ddsGraphicalUtility;
    ddsGraphicalUtility.drawGrid(_tftlcd, centerX - 1, centerY, radius);
}