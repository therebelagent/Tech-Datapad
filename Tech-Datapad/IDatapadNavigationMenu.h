//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef IDatapadNavigationMenu_h
#define IDatapadNavigationMenu_h

#include "IDatapadActionSetup.h"
#include "DatapadTouchScreen.h"

class IDatapadNavigationMenu
{

public:
    IDatapadNavigationMenu(IDatapadActionSetup &datapadActionSetup) : _datapadActionSetup(datapadActionSetup) {}
    virtual void clicked(DatapadDisplayPoint datapadDisplayPoint) = 0;
    virtual bool isInactive() = 0;
    virtual void reset() = 0;

protected:
    IDatapadActionSetup &_datapadActionSetup;
};

#endif