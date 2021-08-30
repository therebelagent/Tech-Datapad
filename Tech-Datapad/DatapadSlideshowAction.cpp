//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadSlideshowAction.h"
#include "StandByDDS.h"
#include "ExplosiveChargesDDS.h"
#include "EnemyTargetsDDS.h"
#include "CannonPoweringUpDDS.h"
#include "DiagnosticDBC.h"
#include "StandByDBC.h"
#include "AllLitUpDBC.h"
#include "ExplosiveChargesDBC.h"
#include "ExplosiveChargesDA.h"

DatapadSlideshowAction::DatapadSlideshowAction(DatapadActionSetup *datapadActionSetup)
{
    _datapadActionSetup = datapadActionSetup;
}

void DatapadSlideshowAction::play()
{
    DatapadAction *datapadAction;
    switch (_currentDatapadActionType)
    {
    case DatapadActionType::Diagnostic:
        datapadAction = new ExplosiveChargesDA(new StandByDDS(&_datapadActionSetup->getTftlcd()), new DiagnosticDBC(_datapadActionSetup->getSmallWhiteButtonPin(), _datapadActionSetup->getRedButtonPin(), _datapadActionSetup->getWhiteButtonPin(), _datapadActionSetup->getYellowButtonPin()));
        _currentDatapadActionType = DatapadActionType::CannonPoweringUp;
        break;
    case DatapadActionType::StandBy:
        datapadAction = new DatapadAction(new StandByDDS(&_datapadActionSetup->getTftlcd()), new StandByDBC(_datapadActionSetup->getSmallWhiteButtonPin(), _datapadActionSetup->getRedButtonPin(), _datapadActionSetup->getWhiteButtonPin(), _datapadActionSetup->getYellowButtonPin()));
        _currentDatapadActionType = DatapadActionType::CannonPoweringUp;
        break;
    case DatapadActionType::CannonPoweringUp:
        datapadAction = new DatapadAction(new CannonPoweringUpDDS(&_datapadActionSetup->getTftlcd()), new AllLitUpDBC(_datapadActionSetup->getSmallWhiteButtonPin(), _datapadActionSetup->getRedButtonPin(), _datapadActionSetup->getWhiteButtonPin(), _datapadActionSetup->getYellowButtonPin()));
        _currentDatapadActionType = DatapadActionType::EnemyTargets;
        break;
    case DatapadActionType::EnemyTargets:
        datapadAction = new DatapadAction(new EnemyTargetsDDS(&_datapadActionSetup->getTftlcd()), new StandByDBC(_datapadActionSetup->getSmallWhiteButtonPin(), _datapadActionSetup->getRedButtonPin(), _datapadActionSetup->getWhiteButtonPin(), _datapadActionSetup->getYellowButtonPin()));
        _currentDatapadActionType = DatapadActionType::ExplosiveCharges;
        break;
    case DatapadActionType::ExplosiveCharges:
        datapadAction = new ExplosiveChargesDA(new ExplosiveChargesDDS(&_datapadActionSetup->getTftlcd()), new ExplosiveChargesDBC(_datapadActionSetup->getSmallWhiteButtonPin(), _datapadActionSetup->getRedButtonPin(), _datapadActionSetup->getWhiteButtonPin(), _datapadActionSetup->getYellowButtonPin()));
        datapadAction->reset();
        _currentDatapadActionType = DatapadActionType::StandBy;
        break;
    }
    datapadAction->play();
}