//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef IDatapad_h
#define IDatapad_h

#include "IDatapadNavigationMenu.h"
#include "IDatapadTouchScreen.h"

class IDatapad
{
public:
    IDatapad(IDatapadNavigationMenu &datapadNavigationMenu, IDatapadTouchScreen &datapadTouchScreen) : _datapadNavigationMenu(datapadNavigationMenu), _datapadTouchScreen(datapadTouchScreen) {}
    virtual void update() = 0;

protected:
    IDatapadNavigationMenu &_datapadNavigationMenu;
    IDatapadTouchScreen &_datapadTouchScreen;
};

#endif