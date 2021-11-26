//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef Datapad_h
#define Datapad_h

#include "IDatapad.h"

class Datapad: public IDatapad
{
public:
    Datapad(IDatapadNavigationMenu &datapadNavigationMenu, IDatapadTouchScreen &datapadTouchScreen);
    void update();
};

#endif