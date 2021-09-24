//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadSlideshowAction_h
#define DatapadSlideshowAction_h

#include "DatapadActionSetup.h"
#include "DatapadActionFactory.h"
#include "DatapadDisplaySequenceConstants.h"

class DatapadSlideshowAction
{
public:
    DatapadSlideshowAction(DatapadActionSetup &datapadActionSetup);
    void setup();
    void play();
    void reset();
    bool isInactive();

private:
    DatapadActionType _datapadActionType = DatapadActionType::Diagnostic;
    DatapadActionSetup &_datapadActionSetup;
    int16_t _inactivityInterval = DISPLAY_INACTIVY_INTERVAL * 1000;
    unsigned long _previousMillis = 0;
    bool _played = false;
    void internalPlay(DatapadActionType datapadActionType);
    void setNextDatapadActionType();
};

#endif