//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DiagnosticDDS.h"

DiagnosticDDS::DiagnosticDDS(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer) : StandByDDS(datapadTFTLCD, datapadSoundPlayer) {}

void DiagnosticDDS::show()
{
    StandByDDS::show();
    DatapadTone datapadTone;
    datapadTone.frequency = 2500;
    datapadTone.duration = 75;
    for (size_t counter = 0; counter < 4; counter++)
    {
        _datapadSoundPlayer.playTone(datapadTone);
        delay(95);
    }
}