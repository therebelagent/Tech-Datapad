//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadSlideshowAction.h"
#include "DatapadActionFactory.h"

DatapadSlideshowAction::DatapadSlideshowAction(DatapadActionSetup *datapadActionSetup)
{
    _datapadActionSetup = datapadActionSetup;
}

void DatapadSlideshowAction::play()
{
    DatapadActionFactory datapadActionFactory = DatapadActionFactory();
    DatapadAction *datapadAction;

    switch (_currentDatapadActionType)
    {
    case DatapadActionType::Diagnostic:
        datapadAction = datapadActionFactory.getDatapadAction(DatapadActionType::Diagnostic, _datapadActionSetup);
        _currentDatapadActionType = DatapadActionType::CannonPoweringUp;
        break;
    case DatapadActionType::StandBy:
        datapadAction = datapadActionFactory.getDatapadAction(DatapadActionType::StandBy, _datapadActionSetup);
        _currentDatapadActionType = DatapadActionType::CannonPoweringUp;
        break;
    case DatapadActionType::CannonPoweringUp:
        datapadAction = datapadActionFactory.getDatapadAction(DatapadActionType::CannonPoweringUp, _datapadActionSetup);
        _currentDatapadActionType = DatapadActionType::EnemyTargets;
        break;
    case DatapadActionType::EnemyTargets:
        datapadAction = datapadActionFactory.getDatapadAction(DatapadActionType::EnemyTargets, _datapadActionSetup);
        _currentDatapadActionType = DatapadActionType::ExplosiveCharges;
        break;
    case DatapadActionType::ExplosiveCharges:
        datapadAction = datapadActionFactory.getDatapadAction(DatapadActionType::ExplosiveCharges, _datapadActionSetup);
        datapadAction->reset();
        _currentDatapadActionType = DatapadActionType::StandBy;
        break;
    }
    datapadAction->play();
}