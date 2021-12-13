//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadButtonsControler.h"

DatapadButtonsControler::DatapadButtonsControler(IDatapadLED &smallWhiteDatapadLED, IDatapadLED &redDatapadLED, IDatapadLED &whiteDatapadLED, IDatapadLED &yellowDatapadLED, IDatapadSoundPlayer &datapadSoundPlayer) : IDatapadButtonsControler(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED, datapadSoundPlayer) {}

IDatapadLED &DatapadButtonsControler::getSmallWhiteDatapadLED()
{
    return _smallWhiteDatapadLED;
}

IDatapadLED &DatapadButtonsControler::getRedDatapadLED()
{
    return _redDatapadLED;
}

IDatapadLED &DatapadButtonsControler::getWhiteDatapadLED()
{
    return _whiteDatapadLED;
}

IDatapadLED &DatapadButtonsControler::getYellowDatapadLED()
{
    return _yellowDatapadLED;
}

void DatapadButtonsControler::turnOnOffButtons(){};

void DatapadButtonsControler::reset()
{
    _smallWhiteDatapadLED.turnOff();
    _redDatapadLED.turnOff();
    _whiteDatapadLED.turnOff();
    _yellowDatapadLED.turnOff();
}