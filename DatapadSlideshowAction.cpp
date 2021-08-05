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

    switch (_currentDatapadDisplaySequence)
    {
    case 1:
        datapadAction = datapadActionFactory.getDatapadAction(DatapadActionType::StandBy, _datapadActionSetup);
        _currentDatapadDisplaySequence = 2;
        break;
    case 2:
        datapadAction = datapadActionFactory.getDatapadAction(DatapadActionType::CannonPoweringUp, _datapadActionSetup);
        _currentDatapadDisplaySequence = 3;
        break;
    case 3:
        datapadAction = datapadActionFactory.getDatapadAction(DatapadActionType::EnemyTargets, _datapadActionSetup);
        _currentDatapadDisplaySequence = 4;
        break;
    case 4:
        datapadAction = datapadActionFactory.getDatapadAction(DatapadActionType::ExplosiveCharges, _datapadActionSetup);
        datapadAction->reset();
        _currentDatapadDisplaySequence = 1;
        break;
    }
    datapadAction->play();
}