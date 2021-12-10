//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include <Arduino.h>
#include "DatapadSoundPlayer.h"

DatapadSoundPlayer::DatapadSoundPlayer(uint8_t pin) : IDatapadSoundPlayer(pin) {}

void DatapadSoundPlayer::playTone(DatapadTone datapadTone) { tone(_pin, datapadTone.frequency, datapadTone.duration); }