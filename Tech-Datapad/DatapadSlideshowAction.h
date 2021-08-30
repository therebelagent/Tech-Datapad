//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadSlideshowAction_h
#define DatapadSlideshowAction_h

#include "DatapadActionSetup.h"

enum class DatapadActionType
{
    Diagnostic = 0,
    StandBy = 2,
    CannonPoweringUp = 4,
    EnemyTargets = 8,
    ExplosiveCharges = 16
};

class DatapadSlideshowAction
{
public:
    DatapadSlideshowAction(DatapadActionSetup *datapadActionSetup);
    void play();

private:
    DatapadActionSetup *_datapadActionSetup;
    DatapadActionType _currentDatapadActionType = DatapadActionType::Diagnostic;
};

#endif