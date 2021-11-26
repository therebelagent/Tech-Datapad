//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef IDatapadTouchScreen_h
#define IDatapadTouchScreen_h

#include "stdint.h"

struct DatapadDisplayPoint
{
    int16_t x;
    int16_t y;
};

class IDatapadTouchScreen
{
public:
    virtual bool isTouching() = 0;
    virtual DatapadDisplayPoint getDatapadDisplayPoint() = 0;

protected:
    DatapadDisplayPoint _datapadDisplayPoint;
};

#endif