//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DatapadActionFactory_h
#define DatapadActionFactory_h

#include "IDatapadAction.h"
#include "IDatapadActionSetup.h"

enum class DatapadActionType
{
    Diagnostic = 0,
    StandBy = 2,
    CannonPoweringUp = 4,
    EnemyTargets = 8,
    ExplosiveCharges = 16,
    RearAxleStabilizerCalibration = 32,
    ForgingChainCodes = 64,
    CommSignalTracker = 128,
    DoorLockHacking = 256,
    SpiceDetector = 512,
    LifeformAnalyzer = 1024,
    InhibitorChipDetector = 2048
};

class DatapadActionFactory
{

public:
    DatapadActionFactory();
    IDatapadAction *getDatapadAction(DatapadActionType datapadActionType, IDatapadActionSetup &datapadActionSetup);
};

#endif