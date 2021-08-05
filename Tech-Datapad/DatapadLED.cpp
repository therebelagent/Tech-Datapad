#include "Arduino.h"
#include "DatapadLED.h"

DatapadLED::DatapadLED(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
}

void DatapadLED::turnOn() { digitalWrite(_pin, HIGH); }

void DatapadLED::turnOff() { digitalWrite(_pin, LOW); }