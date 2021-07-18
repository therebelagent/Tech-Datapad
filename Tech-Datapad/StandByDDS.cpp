#include "StandByDDS.h"
#include "DDSGraphicalUtility.h"
#include "DatapadDisplaySequenceConstants.h"

class StandByDDSHelper
{
public:
    void drawStandByFrame(MCUFRIEND_kbv *tftlcd)
    {
        int16_t centerX = tftlcd->width() / 2;
        int16_t centerY = tftlcd->height() / 2;
        int16_t radius = centerX - 1;
        DDSGraphicalUtility *ddsGraphicalUtility = new DDSGraphicalUtility();
        ddsGraphicalUtility->drawInnerCircle(tftlcd, centerX, centerY, radius, GRID_OUTTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
    }

private:
};

StandByDDS::StandByDDS(MCUFRIEND_kbv *tftlcd) : DatapadDisplaySequence(tftlcd) { _tftlcd = tftlcd; };

void StandByDDS::show()
{
    reset();
    StandByDDSHelper *standByDDSHelper = new StandByDDSHelper();
    standByDDSHelper->drawStandByFrame(_tftlcd);
};
