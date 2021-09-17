//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadLED_h
#define DatapadLED_h

class DatapadLED
{
public:
    DatapadLED(uint8_t pin);
    void turnOn();
    void turnOff();

private:
    const uint8_t _pin;
};

#endif