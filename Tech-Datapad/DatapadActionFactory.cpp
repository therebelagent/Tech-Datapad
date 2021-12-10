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
#include "SpiceDetectorDDS.h"
#include "LifeformAnalyzerDDS.h"
#include "InhibitorChipDetectorDDS.h"
#include "DiagnosticDDS.h"
#include "DiagnosticDBC.h"
#include "StandByDBC.h"
#include "AllLitUpDBC.h"
#include "ExplosiveChargesDBC.h"
#include "ExplosiveChargesDA.h"

DatapadActionFactory::DatapadActionFactory() {}

IDatapadAction *DatapadActionFactory::getDatapadAction(DatapadActionType datapadActionType, IDatapadActionSetup &datapadActionSetup)
{
    IDatapadAction *datapadAction;
    DatapadLED smallWhiteDatapadLED = DatapadLED(datapadActionSetup.getSmallWhiteButtonPin());
    DatapadLED redDatapadLED = DatapadLED(datapadActionSetup.getRedButtonPin());
    DatapadLED whiteDatapadLED = DatapadLED(datapadActionSetup.getWhiteButtonPin());
    DatapadLED yellowDatapadLED = DatapadLED(datapadActionSetup.getYellowButtonPin());
    switch (datapadActionType)
    {
    case DatapadActionType::Diagnostic:
        datapadAction = new ExplosiveChargesDA(*new DiagnosticDDS(datapadActionSetup.getDatapadTFTLCD(), datapadActionSetup.getDatapadSoundPlayer()), *new DiagnosticDBC(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED));
        break;
    case DatapadActionType::StandBy:
        datapadAction = new DatapadAction(*new StandByDDS(datapadActionSetup.getDatapadTFTLCD(), datapadActionSetup.getDatapadSoundPlayer()), *new StandByDBC(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED));
        break;
    case DatapadActionType::CannonPoweringUp:
        datapadAction = new DatapadAction(*new CannonPoweringUpDDS(datapadActionSetup.getDatapadTFTLCD(), datapadActionSetup.getDatapadSoundPlayer()), *new AllLitUpDBC(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED));
        break;
    case DatapadActionType::EnemyTargets:
        datapadAction = new DatapadAction(*new EnemyTargetsDDS(datapadActionSetup.getDatapadTFTLCD(), datapadActionSetup.getDatapadSoundPlayer()), *new StandByDBC(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED));
        break;
    case DatapadActionType::ExplosiveCharges:
        datapadAction = new ExplosiveChargesDA(*new ExplosiveChargesDDS(datapadActionSetup.getDatapadTFTLCD(), datapadActionSetup.getDatapadSoundPlayer()), *new ExplosiveChargesDBC(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED));
        break;
    case DatapadActionType::RearAxleStabilizerCalibration:
        datapadAction = new DatapadAction(*new RearAxleStabilizerCalibrationDDS(datapadActionSetup.getDatapadTFTLCD(), datapadActionSetup.getDatapadSoundPlayer()), *new AllLitUpDBC(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED));
        break;
    case DatapadActionType::ForgingChainCodes:
        datapadAction = new DatapadAction(*new ForgingChainCodesDDS(datapadActionSetup.getDatapadTFTLCD(), datapadActionSetup.getDatapadSoundPlayer()), *new AllLitUpDBC(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED));
        break;
    case DatapadActionType::CommSignalTracker:
        datapadAction = new DatapadAction(*new CommSignalTrackerDDS(datapadActionSetup.getDatapadTFTLCD(), datapadActionSetup.getDatapadSoundPlayer()), *new AllLitUpDBC(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED));
        break;
    case DatapadActionType::DoorLockHacking:
        datapadAction = new DatapadAction(*new DoorLockHackingDDS(datapadActionSetup.getDatapadTFTLCD(), datapadActionSetup.getDatapadSoundPlayer()), *new StandByDBC(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED));
        break;
    case DatapadActionType::SpiceDetector:
        datapadAction = new DatapadAction(*new SpiceDetectorDDS(datapadActionSetup.getDatapadTFTLCD(), datapadActionSetup.getDatapadSoundPlayer()), *new StandByDBC(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED));
        break;
    case DatapadActionType::LifeformAnalyzer:
        datapadAction = new DatapadAction(*new LifeformAnalyzerDDS(datapadActionSetup.getDatapadTFTLCD(), datapadActionSetup.getDatapadSoundPlayer()), *new StandByDBC(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED));
        break;
    case DatapadActionType::InhibitorChipDetector:
        datapadAction = new DatapadAction(*new InhibitorChipDetectorDDS(datapadActionSetup.getDatapadTFTLCD(), datapadActionSetup.getDatapadSoundPlayer()), *new AllLitUpDBC(smallWhiteDatapadLED, redDatapadLED, whiteDatapadLED, yellowDatapadLED));
        break;
    }
    return datapadAction;
}