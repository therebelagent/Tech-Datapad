//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadSlideshowAction.h"
#include "DatapadActionFactory.h"

DatapadSlideshowAction::DatapadSlideshowAction(DatapadActionSetup &datapadActionSetup) : _datapadActionSetup(datapadActionSetup) {}

void DatapadSlideshowAction::play()
{
    DatapadActionFactory datapadActionFactory;
    DatapadAction *datapadAction = datapadActionFactory.getDatapadAction(_currentDatapadActionType, _datapadActionSetup);
    switch (_currentDatapadActionType)
    {
    case DatapadActionType::Diagnostic:
        _currentDatapadActionType = DatapadActionType::ForgingChainCodes;
        break;
    case DatapadActionType::StandBy:
        _currentDatapadActionType = DatapadActionType::ForgingChainCodes;
        break;
    case DatapadActionType::ForgingChainCodes:
        _currentDatapadActionType = DatapadActionType::RearAxleStabilizerCalibration;
        break;
    case DatapadActionType::RearAxleStabilizerCalibration:
        _currentDatapadActionType = DatapadActionType::CannonPoweringUp;
        break;
    case DatapadActionType::CannonPoweringUp:
        _currentDatapadActionType = DatapadActionType::EnemyTargets;
        break;
    case DatapadActionType::EnemyTargets:
        _currentDatapadActionType = DatapadActionType::ExplosiveCharges;
        break;
    case DatapadActionType::ExplosiveCharges:
        datapadAction->reset();
        _currentDatapadActionType = DatapadActionType::StandBy;
        break;
    }
    datapadAction->play();
    delete datapadAction;
}