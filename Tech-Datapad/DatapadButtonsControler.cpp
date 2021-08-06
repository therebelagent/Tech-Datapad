#include "DatapadButtonsControler.h"

DatapadButtonsControler::DatapadButtonsControler(uint8_t smallWhiteButtonPin, uint8_t redButtonPin, uint8_t whiteButtonPin, uint8_t yellowButtonPin)
{
    _smallWhiteDatapadLED = new DatapadLED(smallWhiteButtonPin);
    _redDatapadLED = new DatapadLED(redButtonPin);
    _whiteDatapadLED = new DatapadLED(whiteButtonPin);
    _yellowDatapadLED = new DatapadLED(yellowButtonPin);
}

DatapadLED *DatapadButtonsControler::getSmallWhiteDatapadLED() { return _smallWhiteDatapadLED; }

DatapadLED *DatapadButtonsControler::getRedDatapadLED() { return _redDatapadLED; }

DatapadLED *DatapadButtonsControler::getWhiteDatapadLED() { return _whiteDatapadLED; }

DatapadLED *DatapadButtonsControler::getYellowDatapadLED() { return _yellowDatapadLED; }

void DatapadButtonsControler::turnOnOffButtons(){};

void DatapadButtonsControler::reset()
{
    _smallWhiteDatapadLED->turnOff();
    _redDatapadLED->turnOff();
    _whiteDatapadLED->turnOff();
    _yellowDatapadLED->turnOff();
}