//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadSoundPlayer_h
#define DatapadSoundPlayer_h

#include "IDatapadSoundPlayer.h"

class DatapadSoundPlayer : public IDatapadSoundPlayer
{
public:
    DatapadSoundPlayer(uint8_t pin);
    void playTone(DatapadTone datapadTone);
};

#endif