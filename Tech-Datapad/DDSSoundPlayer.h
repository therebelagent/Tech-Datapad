//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DDSSoundPlayer_h
#define DDSSoundPlayer_h

#include "IDatapadSoundPlayer.h"

class DDSSoundPlayer
{
public:
    DDSSoundPlayer(IDatapadSoundPlayer &datapadSoundPlayer);
    void playButtonTone();
    void playDisplayButtonTone();

private:
    IDatapadSoundPlayer &_datapadSoundPlayer;
    DatapadTone _buttonDatapadTone;
    DatapadTone _displayButtonDatapadTone;
};

#endif