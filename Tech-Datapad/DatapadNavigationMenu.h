//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadNavigationMenu_h
#define DatapadNavigationMenu_h

#include "DatapadSoundPlayer.h"
#include "IDatapadNavigationMenu.h"
#include "IDatapadActionSetup.h"
#include "DatapadDisplayButton.h"

class DatapadNavigationMenu : public IDatapadNavigationMenu
{

public:
    DatapadNavigationMenu(IDatapadActionSetup &datapadActionSetup);
    virtual void clicked(DatapadDisplayPoint datapadDisplayPoint);
    virtual bool isInactive();
    virtual void reset();

private:
    DatapadDisplayButton _datapadDisplayButtons[NAVIGATION_MENU_BUTTONS_ITEMS];
    int16_t _inactivityInterval = DISPLAY_INACTIVY_INTERVAL * 1000;
    unsigned long _previousMillis = 0;
    bool _playing = false;
};

#endif