//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DDSSoundPlayer.h"

DDSSoundPlayer::DDSSoundPlayer(IDatapadSoundPlayer &datapadSoundPlayer) : _datapadSoundPlayer(datapadSoundPlayer)
{
    //Button DatapadTone Setup
    _buttonDatapadTone.frequency = 2000;
    _buttonDatapadTone.duration = 100;
    //Display Button DatapadTone Setup
    _displayButtonDatapadTone.frequency = 2500;
    _displayButtonDatapadTone.duration = 75;
}

void DDSSoundPlayer::playButtonTone()
{
    _datapadSoundPlayer.playTone(_buttonDatapadTone);
}

void DDSSoundPlayer::playDisplayButtonTone()
{
    _datapadSoundPlayer.playTone(_displayButtonDatapadTone);
}