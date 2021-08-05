#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include "TouchScreenConstants.h"
#include "DatapadTouchScreen.h"
#include "DatapadActionSetup.h"
#include "DatapadSlideshowAction.h"
#include "DatapadPinsConstants.h"

MCUFRIEND_kbv tftlcd;
DatapadActionSetup datapadActionSetup = DatapadActionSetup(&tftlcd, SMALL_WHITE_BUTTON_PIN, RED_BUTTON_PIN, WHITE_BUTTON_PIN, YELLOW_BUTTON_PIN);
DatapadSlideshowAction datapadSlideshowAction = DatapadSlideshowAction(&datapadActionSetup);
DatapadTouchScreen datapadTouchScreen = DatapadTouchScreen(XP, YP, XM, YM, 300);

void setup()
{
    uint16_t ID = tftlcd.readID();
    tftlcd.begin(ID);
    tftlcd.setRotation(0);
    tftlcd.fillScreen(TFT_BLACK);
    datapadSlideshowAction.play();
}

void loop()
{
    if (datapadTouchScreen.isTouching())
    {
        datapadSlideshowAction.play();
    }
}