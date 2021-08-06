#include "DatapadActionFactory.h"
#include "StandByDDS.h"
#include "ExplosiveChargesDDS.h"
#include "EnemyTargetsDDS.h"
#include "CannonPoweringUpDDS.h"
#include "StandByDBC.h"
#include "AllLitUpDBC.h"
#include "ExplosiveChargesDBC.h"
#include "ExplosiveChargesDA.h"

DatapadActionFactory::DatapadActionFactory(){}

DatapadAction *DatapadActionFactory::getDatapadAction(DatapadActionType datapadActionType, DatapadActionSetup *datapadActionSetup)
{
    DatapadAction *datapadAction;

    switch (datapadActionType)
    {
    case DatapadActionType::StandBy:
        datapadAction = new DatapadAction(new StandByDDS(&datapadActionSetup->getTftlcd()), new StandByDBC(datapadActionSetup->getSmallWhiteButtonPin(), datapadActionSetup->getRedButtonPin(), datapadActionSetup->getWhiteButtonPin(), datapadActionSetup->getYellowButtonPin()));
        break;
    case DatapadActionType::CannonPoweringUp:
        datapadAction = new DatapadAction(new CannonPoweringUpDDS(&datapadActionSetup->getTftlcd()), new AllLitUpDBC(datapadActionSetup->getSmallWhiteButtonPin(), datapadActionSetup->getRedButtonPin(), datapadActionSetup->getWhiteButtonPin(), datapadActionSetup->getYellowButtonPin()));
        break;
    case DatapadActionType::EnemyTargets:
        datapadAction = new DatapadAction(new EnemyTargetsDDS(&datapadActionSetup->getTftlcd()), new StandByDBC(datapadActionSetup->getSmallWhiteButtonPin(), datapadActionSetup->getRedButtonPin(), datapadActionSetup->getWhiteButtonPin(), datapadActionSetup->getYellowButtonPin()));
        break;
    case DatapadActionType::ExplosiveCharges:
        datapadAction = new ExplosiveChargesDA(new ExplosiveChargesDDS(&datapadActionSetup->getTftlcd()), new ExplosiveChargesDBC(datapadActionSetup->getSmallWhiteButtonPin(), datapadActionSetup->getRedButtonPin(), datapadActionSetup->getWhiteButtonPin(), datapadActionSetup->getYellowButtonPin()));
        break;
    }
    return datapadAction;
}