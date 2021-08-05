#include "Arduino.h"
#include "DatapadButtonsControler.h"

DatapadButtonsControler::DatapadButtonsControler(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin)
{
    _smallWhiteButtonPin = smallWhiteButtonPin;
    _redButtonPin = redButtonPin;
    _whiteButtonPin = whiteButtonPin;
    _yellowButtonPin = yellowButtonPin;
    pinMode(_smallWhiteButtonPin, OUTPUT);
    pinMode(_redButtonPin, OUTPUT);
    pinMode(_whiteButtonPin, OUTPUT);
    pinMode(_yellowButtonPin, OUTPUT);
}

uint8_t DatapadButtonsControler::getSmallWhiteButtonPin() { return _smallWhiteButtonPin; }

uint8_t DatapadButtonsControler::getRedButtonPin() { return _redButtonPin; }

uint8_t DatapadButtonsControler::getWhiteButtonPin() { return _whiteButtonPin; }

uint8_t DatapadButtonsControler::getYellowButtonPin() { return _yellowButtonPin; }

void DatapadButtonsControler::turnOnOffButtons(){};

void DatapadButtonsControler::reset()
{
    digitalWrite(_smallWhiteButtonPin, LOW);
    digitalWrite(_redButtonPin, LOW);
    digitalWrite(_whiteButtonPin, LOW);
    digitalWrite(_yellowButtonPin, LOW);
}