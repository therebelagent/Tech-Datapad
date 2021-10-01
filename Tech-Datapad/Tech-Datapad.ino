//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadTFTLCD.h"
#include "DatapadActionSetup.h"
#include "DatapadNavigationMenu.h"
#include "DatapadTouchScreen.h"
#include "DatapadPinsConstants.h"

DatapadNavigationMenu *datapadNavigationMenu;
DatapadTouchScreen *datapadTouchScreen;

void setup()
{
    DatapadTFTLCD datapadTFTLCD = DatapadTFTLCD();
    DatapadActionSetup datapadActionSetup = DatapadActionSetup(datapadTFTLCD, SMALL_WHITE_BUTTON_PIN, RED_BUTTON_PIN, WHITE_BUTTON_PIN, YELLOW_BUTTON_PIN);
    datapadNavigationMenu = new DatapadNavigationMenu(datapadActionSetup);
    datapadNavigationMenu->setup();
    datapadTouchScreen = new DatapadTouchScreen(XP, YP, XM, YM, 300);
}

void loop()
{
    if (datapadTouchScreen->isTouching())
    {
        datapadNavigationMenu->clicked(datapadTouchScreen->getDatapadDisplayPoint());
    }
    else if (datapadNavigationMenu->isInactive())
    {
        datapadNavigationMenu->reset();
    }
}