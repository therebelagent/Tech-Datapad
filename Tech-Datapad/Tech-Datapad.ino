#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include "DatapadDisplaySequence.h"
#include "SlideshowDDS.h"
#include "TouchScreenConstants.h"

MCUFRIEND_kbv tftlcd;
TouchScreen touchScreen = TouchScreen(XP, YP, XM, YM, 300);
DatapadDisplaySequence *datapadDisplaySequence;

void setup()
{
    uint16_t ID = tftlcd.readID();
    tftlcd.begin(ID);
    tftlcd.setRotation(0);
    tftlcd.fillScreen(TFT_BLACK);
    datapadDisplaySequence = new SlideshowDDS(&tftlcd);
    datapadDisplaySequence->show();
    pinMode(13, OUTPUT);
}

void loop()
{
    digitalWrite(13, HIGH);
    TSPoint point = touchScreen.getPoint();
    digitalWrite(13, LOW);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if (point.z > MINPRESSURE && point.z < MAXPRESSURE)
    {
        datapadDisplaySequence->show();
    }
}
