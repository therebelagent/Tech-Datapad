#ifndef DatapadActionFactory_h
#define DatapadActionFactory_h

#include "DatapadAction.h"
#include "DatapadActionSetup.h"

enum class DatapadActionType
{
    StandBy,
    CannonPoweringUp,
    EnemyTargets,
    ExplosiveCharges
};

class DatapadActionFactory
{

public:
    DatapadActionFactory();
    DatapadAction *getDatapadAction(DatapadActionType datapadActionType, DatapadActionSetup *datapadActionSetup);
};

#endif