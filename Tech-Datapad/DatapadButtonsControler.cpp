//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadButtonsControler.h"

DatapadButtonsControler::DatapadButtonsControler(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin)
    : _smallWhiteDatapadLED(DatapadLED(smallWhiteButtonPin)),
      _redDatapadLED(DatapadLED(redButtonPin)),
      _whiteDatapadLED(DatapadLED(whiteButtonPin)),
      _yellowDatapadLED(DatapadLED(yellowButtonPin)) {}

DatapadLED &DatapadButtonsControler::getSmallWhiteDatapadLED()
{
    return _smallWhiteDatapadLED;
}

DatapadLED &DatapadButtonsControler::getRedDatapadLED()
{
    return _redDatapadLED;
}

DatapadLED &DatapadButtonsControler::getWhiteDatapadLED()
{
    return _whiteDatapadLED;
}

DatapadLED &DatapadButtonsControler::getYellowDatapadLED()
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