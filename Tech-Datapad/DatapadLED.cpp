//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include <Arduino.h>
#include "DatapadLED.h"

DatapadLED::DatapadLED(uint8_t pin) : IDatapadLED(pin)
{
    pinMode(_pin, OUTPUT);
}

void DatapadLED::turnOn() { digitalWrite(_pin, HIGH); }

void DatapadLED::turnOff() { digitalWrite(_pin, LOW); }