//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadSlideshowAction.h"
#include "DatapadActionFactory.h"

DatapadSlideshowAction::DatapadSlideshowAction(DatapadActionSetup &datapadActionSetup) : _datapadActionSetup(datapadActionSetup) {}

void DatapadSlideshowAction::setup()
{
    _datapadActionSetup.getTftlcd().begin(_datapadActionSetup.getTftlcd().readID());
    _datapadActionSetup.getTftlcd().setRotation(0);
    _datapadActionSetup.getTftlcd().fillScreen(TFT_BLACK);
    internalPlay(_datapadActionType);
    setNextDatapadActionType();
}

void DatapadSlideshowAction::play()
{
    _played = true;
    internalPlay(_datapadActionType);
    setNextDatapadActionType();
    _previousMillis = millis();
}

void DatapadSlideshowAction::reset()
{
    internalPlay(DatapadActionType::StandBy);
}

bool DatapadSlideshowAction::isInactive()
{
    bool result = false;
    if (_played)
    {
        if (millis() - _previousMillis > _inactivityInterval)
        {
            _played = false;
            result = true;
        }
    }
    return result;
}

void DatapadSlideshowAction::internalPlay(DatapadActionType datapadActionType)
{
    DatapadActionFactory datapadActionFactory;
    DatapadAction *datapadAction = datapadActionFactory.getDatapadAction(datapadActionType, _datapadActionSetup);
    datapadAction->play();
    delete datapadAction;
}

void DatapadSlideshowAction::setNextDatapadActionType()
{
    switch (_datapadActionType)
    {
    case DatapadActionType::Diagnostic:
        _datapadActionType = DatapadActionType::DoorLockHacking;
        break;
    case DatapadActionType::DoorLockHacking:
        _datapadActionType = DatapadActionType::CommSignalTracker;
        break;
    case DatapadActionType::CommSignalTracker:
        _datapadActionType = DatapadActionType::ForgingChainCodes;
        break;
    case DatapadActionType::ForgingChainCodes:
        _datapadActionType = DatapadActionType::RearAxleStabilizerCalibration;
        break;
    case DatapadActionType::RearAxleStabilizerCalibration:
        _datapadActionType = DatapadActionType::CannonPoweringUp;
        break;
    case DatapadActionType::CannonPoweringUp:
        _datapadActionType = DatapadActionType::EnemyTargets;
        break;
    case DatapadActionType::EnemyTargets:
        _datapadActionType = DatapadActionType::ExplosiveCharges;
        break;
    case DatapadActionType::ExplosiveCharges:
        _datapadActionType = DatapadActionType::DoorLockHacking;
        break;
    }
}