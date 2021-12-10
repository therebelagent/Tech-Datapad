//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef IDatapadSoundPlayer_h
#define IDatapadSoundPlayer_h

#include "stdint.h"

struct DatapadTone
{
    unsigned int frequency;
    unsigned long duration;
};

class IDatapadSoundPlayer
{
public:
    IDatapadSoundPlayer(uint8_t pin) : _pin(pin) {}
    virtual void playTone(DatapadTone datapadTone) = 0;

protected:
    const uint8_t _pin;
};

#endif