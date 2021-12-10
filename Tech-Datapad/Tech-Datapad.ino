//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "Datapad.h"
#include "DatapadTFTLCD.h"
#include "DatapadSoundPlayer.h"
#include "DatapadActionSetup.h"
#include "DatapadNavigationMenu.h"
#include "DatapadTouchScreen.h"
#include "DatapadPinsConstants.h"

IDatapadNavigationMenu *datapadNavigationMenu;
IDatapadTouchScreen *datapadTouchScreen;
IDatapad *datapad;

void setup()
{
    datapadTouchScreen = new DatapadTouchScreen(XP, YP, XM, YM, 300);
    DatapadTFTLCD datapadTFTLCD = DatapadTFTLCD();
    DatapadSoundPlayer datapadSoundPlayer = DatapadSoundPlayer(SOUND_PLAYER_PIN);
    DatapadActionSetup datapadActionSetup = DatapadActionSetup(datapadTFTLCD, datapadSoundPlayer, SMALL_WHITE_BUTTON_PIN, RED_BUTTON_PIN, WHITE_BUTTON_PIN, YELLOW_BUTTON_PIN);
    datapadNavigationMenu = new DatapadNavigationMenu(datapadActionSetup);
    datapad = new Datapad(*datapadNavigationMenu, *datapadTouchScreen);
}

void loop()
{
    datapad->update();
}