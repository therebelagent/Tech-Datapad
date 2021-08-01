#include <MCUFRIEND_kbv.h>
#include "DatapadDisplaySequence.h"
#include "SlideshowDDS.h"
#include <TouchScreen.h>
#include "TouchScreenConstants.h"
#include "DatapadTouchScreen.h"

MCUFRIEND_kbv tftlcd;
DatapadTouchScreen datapadTouchScreen = DatapadTouchScreen(XP, YP, XM, YM, 300);
DatapadDisplaySequence *datapadDisplaySequence;

void setup()
{
    uint16_t ID = tftlcd.readID();
    tftlcd.begin(ID);
    tftlcd.setRotation(0);
    tftlcd.fillScreen(TFT_BLACK);
    datapadDisplaySequence = new SlideshowDDS(&tftlcd);
    datapadDisplaySequence->show();
}

void loop()
{
    if (datapadTouchScreen.isTouching())
    {
        datapadDisplaySequence->show();
    }
}
