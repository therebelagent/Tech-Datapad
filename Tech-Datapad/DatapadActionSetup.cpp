//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadActionSetup.h"

DatapadActionSetup::DatapadActionSetup(MCUFRIEND_kbv *tftlcd, uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin)
{
    _tftlcd = tftlcd;
    _smallWhiteButtonPin = smallWhiteButtonPin;
    _redButtonPin = redButtonPin;
    _whiteButtonPin = whiteButtonPin;
    _yellowButtonPin = yellowButtonPin;
}

MCUFRIEND_kbv DatapadActionSetup::getTftlcd() { return *_tftlcd; }

uint8_t DatapadActionSetup::getSmallWhiteButtonPin() { return _smallWhiteButtonPin; }

uint8_t DatapadActionSetup::getRedButtonPin() { return _redButtonPin; }

uint8_t DatapadActionSetup::getWhiteButtonPin() { return _whiteButtonPin; }

uint8_t DatapadActionSetup::getYellowButtonPin() { return _yellowButtonPin; }