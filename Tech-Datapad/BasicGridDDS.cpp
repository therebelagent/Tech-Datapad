//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "BasicGridDDS.h"
#include "DDSGraphicalUtility.h"
#include "DatapadDisplaySequenceConstants.h"

class BasicGridDDSHelper
{
public:
    void drawBasicGrid(MCUFRIEND_kbv *tftlcd)
    {
        int16_t centerX = tftlcd->width() / 2;
        int16_t centerY = tftlcd->height() / 2;
        int16_t radius = centerX - 1;
        DDSGraphicalUtility *ddsGraphicalUtility = new DDSGraphicalUtility();
        ddsGraphicalUtility->drawGrid(tftlcd, centerX - 1, centerY, radius);
        ddsGraphicalUtility->drawInnerCircle(tftlcd, centerX, centerY, radius, GRID_OUTTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
    }
};

BasicGridDDS::BasicGridDDS(MCUFRIEND_kbv *tftlcd) : DatapadDisplaySequence(tftlcd) { _tftlcd = tftlcd; }

void BasicGridDDS::show()
{
    reset();
    BasicGridDDSHelper *basicGridDDSHelper = new BasicGridDDSHelper();
    basicGridDDSHelper->drawBasicGrid(_tftlcd);
}