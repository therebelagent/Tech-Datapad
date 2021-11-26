//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "Datapad.h"

Datapad::Datapad(IDatapadNavigationMenu &datapadNavigationMenu, IDatapadTouchScreen &datapadTouchScreen) : IDatapad(datapadNavigationMenu, datapadTouchScreen) {}

void Datapad::update()
{
    if (_datapadTouchScreen.isTouching())
    {
        _datapadNavigationMenu.clicked(_datapadTouchScreen.getDatapadDisplayPoint());
    }
    else if (_datapadNavigationMenu.isInactive())
    {
        _datapadNavigationMenu.reset();
    }
}