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
    }
};

BasicGridDDS::BasicGridDDS(MCUFRIEND_kbv *tftlcd) : StandByDDS(tftlcd) { _tftlcd = tftlcd; };

void BasicGridDDS::show()
{
    StandByDDS::show();
    BasicGridDDSHelper *basicGridDDSHelper = new BasicGridDDSHelper();
    basicGridDDSHelper->drawBasicGrid(_tftlcd);
};