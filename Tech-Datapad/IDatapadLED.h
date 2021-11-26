//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef IDatapadLED_h
#define IDatapadLED_h

class IDatapadLED
{
public:
    IDatapadLED(uint8_t pin) : _pin(pin) {}
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;

protected:
    const uint8_t _pin;
};

#endif