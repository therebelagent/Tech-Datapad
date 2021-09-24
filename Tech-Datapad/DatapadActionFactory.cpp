//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadActionFactory.h"
#include "StandByDDS.h"
#include "ExplosiveChargesDDS.h"
#include "EnemyTargetsDDS.h"
#include "CannonPoweringUpDDS.h"
#include "RearAxleStabilizerCalibrationDDS.h"
#include "ForgingChainCodesDDS.h"
#include "CommSignalTrackerDDS.h"
#include "DoorLockHackingDDS.h"
#include "DiagnosticDBC.h"
#include "StandByDBC.h"
#include "AllLitUpDBC.h"
#include "ExplosiveChargesDBC.h"
#include "ExplosiveChargesDA.h"

DatapadActionFactory::DatapadActionFactory() {}

DatapadAction *DatapadActionFactory::getDatapadAction(DatapadActionType datapadActionType, DatapadActionSetup &datapadActionSetup)
{
    DatapadAction *datapadAction;
    switch (datapadActionType)
    {
    case DatapadActionType::Diagnostic:
        datapadAction = new ExplosiveChargesDA(*new StandByDDS(datapadActionSetup.getTftlcd()), *new DiagnosticDBC(datapadActionSetup.getSmallWhiteButtonPin(), datapadActionSetup.getRedButtonPin(), datapadActionSetup.getWhiteButtonPin(), datapadActionSetup.getYellowButtonPin()));
        break;
    case DatapadActionType::StandBy:
        datapadAction = new DatapadAction(*new StandByDDS(datapadActionSetup.getTftlcd()), *new StandByDBC(datapadActionSetup.getSmallWhiteButtonPin(), datapadActionSetup.getRedButtonPin(), datapadActionSetup.getWhiteButtonPin(), datapadActionSetup.getYellowButtonPin()));
        break;
    case DatapadActionType::CannonPoweringUp:
        datapadAction = new DatapadAction(*new CannonPoweringUpDDS(datapadActionSetup.getTftlcd()), *new AllLitUpDBC(datapadActionSetup.getSmallWhiteButtonPin(), datapadActionSetup.getRedButtonPin(), datapadActionSetup.getWhiteButtonPin(), datapadActionSetup.getYellowButtonPin()));
        break;
    case DatapadActionType::EnemyTargets:
        datapadAction = new DatapadAction(*new EnemyTargetsDDS(datapadActionSetup.getTftlcd()), *new StandByDBC(datapadActionSetup.getSmallWhiteButtonPin(), datapadActionSetup.getRedButtonPin(), datapadActionSetup.getWhiteButtonPin(), datapadActionSetup.getYellowButtonPin()));
        break;
    case DatapadActionType::ExplosiveCharges:
        datapadAction = new ExplosiveChargesDA(*new ExplosiveChargesDDS(datapadActionSetup.getTftlcd()), *new ExplosiveChargesDBC(datapadActionSetup.getSmallWhiteButtonPin(), datapadActionSetup.getRedButtonPin(), datapadActionSetup.getWhiteButtonPin(), datapadActionSetup.getYellowButtonPin()));
        break;
    case DatapadActionType::RearAxleStabilizerCalibration:
        datapadAction = new DatapadAction(*new RearAxleStabilizerCalibrationDDS(datapadActionSetup.getTftlcd()), *new AllLitUpDBC(datapadActionSetup.getSmallWhiteButtonPin(), datapadActionSetup.getRedButtonPin(), datapadActionSetup.getWhiteButtonPin(), datapadActionSetup.getYellowButtonPin()));
        break;
    case DatapadActionType::ForgingChainCodes:
        datapadAction = new DatapadAction(*new ForgingChainCodesDDS(datapadActionSetup.getTftlcd()), *new AllLitUpDBC(datapadActionSetup.getSmallWhiteButtonPin(), datapadActionSetup.getRedButtonPin(), datapadActionSetup.getWhiteButtonPin(), datapadActionSetup.getYellowButtonPin()));
        break;
    case DatapadActionType::CommSignalTracker:
        datapadAction = new DatapadAction(*new CommSignalTrackerDDS(datapadActionSetup.getTftlcd()), *new AllLitUpDBC(datapadActionSetup.getSmallWhiteButtonPin(), datapadActionSetup.getRedButtonPin(), datapadActionSetup.getWhiteButtonPin(), datapadActionSetup.getYellowButtonPin()));
        break;
    case DatapadActionType::DoorLockHacking:
        datapadAction = new DatapadAction(*new DoorLockHackingDDS(datapadActionSetup.getTftlcd()), *new StandByDBC(datapadActionSetup.getSmallWhiteButtonPin(), datapadActionSetup.getRedButtonPin(), datapadActionSetup.getWhiteButtonPin(), datapadActionSetup.getYellowButtonPin()));
        break;
    }
    return datapadAction;
}