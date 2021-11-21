//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadNavigationMenu.h"
#include "DatapadDisplayButton.h"
#include "DatapadActionFactory.h"
#include "Fonts/Aurebesh8pt7b.h"

class DatapadNavigationMenuHelper
{
public:
    void playDatapadaAction(DatapadActionType datapadActionType, DatapadActionSetup datapadActionSetup)
    {
        DatapadAction *datapadAction = _datapadActionFactory.getDatapadAction(datapadActionType, datapadActionSetup);
        datapadAction->reset();
        datapadAction->play();
        delete datapadAction;
    }

    void navigationMenuSetup(DatapadTFTLCD &datapadTFTLCD, const GFXfont *gfxFont, DatapadDisplayButton datapadDisplayButtons[])
    {
        int16_t centerX = datapadTFTLCD.width() / 2;
        int16_t centerY = datapadTFTLCD.height() / 2;
        int16_t buttonSeparation = getButtonSeparation();
        int16_t buttonWidth = getButtonWidth(datapadTFTLCD.width());
        int16_t totalWidth = (buttonWidth * 3) + (buttonSeparation * 4);
        int16_t buttonLeft = centerX - (totalWidth / 2);
        int16_t buttonHeight = getButtonHeight(buttonWidth);
        int16_t totalHeight = (buttonHeight * 2) + (buttonSeparation * 2);
        int16_t buttonTop = getButtonTop(centerY);
        //Calculate First Row Of Buttons Positions.
        datapadDisplayButtons[0].initialize(&datapadTFTLCD, DatapadActionType::EnemyTargets, buttonLeft, buttonTop, buttonWidth, NAVIGATION_MENU_BUTTON_5_TEXT, NAVIGATION_MENU_BUTTON_COLOR, NAVIGATION_MENU_BUTTON_BACK_COLOR, NAVIGATION_MENU_BUTTON_PRESS_COLOR, gfxFont);
        int16_t nextButtonLeft = buttonLeft + buttonWidth + buttonSeparation;
        datapadDisplayButtons[1].initialize(&datapadTFTLCD, DatapadActionType::DoorLockHacking, nextButtonLeft, buttonTop, buttonWidth, NAVIGATION_MENU_BUTTON_0_TEXT, NAVIGATION_MENU_BUTTON_COLOR, NAVIGATION_MENU_BUTTON_BACK_COLOR, NAVIGATION_MENU_BUTTON_PRESS_COLOR, gfxFont);
        nextButtonLeft += buttonSeparation;
        datapadDisplayButtons[2].initialize(&datapadTFTLCD, DatapadActionType::ExplosiveCharges, nextButtonLeft, buttonTop, buttonWidth, NAVIGATION_MENU_BUTTON_6_TEXT, NAVIGATION_MENU_BUTTON_COLOR, NAVIGATION_MENU_BUTTON_BACK_COLOR, NAVIGATION_MENU_BUTTON_PRESS_COLOR, gfxFont);
        nextButtonLeft += buttonWidth + buttonSeparation;
        datapadDisplayButtons[3].initialize(&datapadTFTLCD, DatapadActionType::ForgingChainCodes, nextButtonLeft, buttonTop, buttonWidth, NAVIGATION_MENU_BUTTON_2_TEXT, NAVIGATION_MENU_BUTTON_COLOR, NAVIGATION_MENU_BUTTON_BACK_COLOR, NAVIGATION_MENU_BUTTON_PRESS_COLOR, gfxFont);
        nextButtonLeft += buttonSeparation;
        datapadDisplayButtons[4].initialize(&datapadTFTLCD, DatapadActionType::InhibitorChipDetector, nextButtonLeft, buttonTop, buttonWidth, NAVIGATION_MENU_BUTTON_9_TEXT, NAVIGATION_MENU_BUTTON_COLOR, NAVIGATION_MENU_BUTTON_BACK_COLOR, NAVIGATION_MENU_BUTTON_PRESS_COLOR, gfxFont);
        //Calculate Second Row Of Buttons Positions.
        buttonLeft = centerX - (totalWidth / 2) + (buttonWidth / 2);
        buttonTop += buttonSeparation + buttonHeight;
        datapadDisplayButtons[5].initialize(&datapadTFTLCD, DatapadActionType::CannonPoweringUp, buttonLeft, buttonTop, buttonWidth, NAVIGATION_MENU_BUTTON_4_TEXT, NAVIGATION_MENU_BUTTON_COLOR, NAVIGATION_MENU_BUTTON_BACK_COLOR, NAVIGATION_MENU_BUTTON_PRESS_COLOR, gfxFont);
        nextButtonLeft = buttonLeft + buttonSeparation;
        datapadDisplayButtons[6].initialize(&datapadTFTLCD, DatapadActionType::RearAxleStabilizerCalibration, nextButtonLeft, buttonTop, buttonWidth, NAVIGATION_MENU_BUTTON_3_TEXT, NAVIGATION_MENU_BUTTON_COLOR, NAVIGATION_MENU_BUTTON_BACK_COLOR, NAVIGATION_MENU_BUTTON_PRESS_COLOR, gfxFont);
        nextButtonLeft += buttonWidth + buttonSeparation;
        datapadDisplayButtons[7].initialize(&datapadTFTLCD, DatapadActionType::SpiceDetector, nextButtonLeft, buttonTop, buttonWidth, NAVIGATION_MENU_BUTTON_7_TEXT, NAVIGATION_MENU_BUTTON_COLOR, NAVIGATION_MENU_BUTTON_BACK_COLOR, NAVIGATION_MENU_BUTTON_PRESS_COLOR, gfxFont);
        nextButtonLeft += buttonSeparation;
        datapadDisplayButtons[8].initialize(&datapadTFTLCD, DatapadActionType::LifeformAnalyzer, nextButtonLeft, buttonTop, buttonWidth, NAVIGATION_MENU_BUTTON_8_TEXT, NAVIGATION_MENU_BUTTON_COLOR, NAVIGATION_MENU_BUTTON_BACK_COLOR, NAVIGATION_MENU_BUTTON_PRESS_COLOR, gfxFont);
        nextButtonLeft += buttonWidth + buttonSeparation;
        datapadDisplayButtons[9].initialize(&datapadTFTLCD, DatapadActionType::CommSignalTracker, nextButtonLeft, buttonTop, buttonWidth, NAVIGATION_MENU_BUTTON_1_TEXT, NAVIGATION_MENU_BUTTON_COLOR, NAVIGATION_MENU_BUTTON_BACK_COLOR, NAVIGATION_MENU_BUTTON_PRESS_COLOR, gfxFont);
    }

    void refreshNavigationMenu(DatapadTFTLCD &datapadTFTLCD, const GFXfont *gfxFont, DatapadDisplayButton datapadDisplayButtons[])
    {
        //Draw Top Banner.
        int16_t centerX = datapadTFTLCD.width() / 2;
        int16_t centerY = datapadTFTLCD.height() / 2;
        int16_t width = datapadTFTLCD.width();
        int16_t bannerWidth = width * 0.48;
        int16_t bannerHeight = width * 0.09;
        int16_t bannerTop = centerY - 131;
        datapadTFTLCD.drawBanner(centerX, bannerTop, bannerHeight, bannerWidth, TFT_DARKCYAN, NAVIGATION_MENU_BANNER_TEXT, gfxFont);
        //Draw Datapad Navigation Menu Buttons.
        int16_t buttonSeparation = getButtonSeparation();
        int16_t buttonWidth = getButtonWidth(width);
        int16_t buttonHeight = getButtonHeight(buttonWidth);
        int16_t buttonTop = getButtonTop(centerY);
        datapadTFTLCD.drawFastHorizontalLine(0, buttonTop - buttonHeight - buttonSeparation, width, 2, DISPLAY_RING_COLOR);
        //Draw First Line.
        datapadDisplayButtons[0].draw();
        datapadDisplayButtons[1].drawInverted();
        datapadDisplayButtons[2].draw();
        datapadDisplayButtons[3].drawInverted();
        datapadDisplayButtons[4].draw();
        //Draw Second Line.
        datapadDisplayButtons[5].drawInverted();
        datapadDisplayButtons[6].draw();
        datapadDisplayButtons[7].drawInverted();
        datapadDisplayButtons[8].draw();
        datapadDisplayButtons[9].drawInverted();
        datapadTFTLCD.drawFastHorizontalLine(0, buttonTop + buttonHeight + buttonSeparation + buttonSeparation, width, 2, DISPLAY_RING_COLOR);
    }

    int16_t getButtonSeparation() { return 12; }
    int16_t getButtonWidth(int16_t width) { return width * 0.26; }
    int16_t getButtonHeight(int16_t buttonWidth) { return (sqrt(3) * buttonWidth) / 2; }
    int16_t getButtonTop(int16_t y) { return y - (getButtonSeparation() / 2); }

private:
    DatapadActionFactory _datapadActionFactory;
};

DatapadNavigationMenu::DatapadNavigationMenu(DatapadActionSetup &datapadActionSetup) : _datapadActionSetup(datapadActionSetup) {}

void DatapadNavigationMenu::setup()
{
    _datapadActionSetup.getDatapadTFTLCD().setRotation(0);
    _datapadActionSetup.getDatapadTFTLCD().fillScreen(TFT_BLACK);
    DatapadNavigationMenuHelper datapadNavigationMenuHelper;
    datapadNavigationMenuHelper.playDatapadaAction(DatapadActionType::Diagnostic, _datapadActionSetup);
    datapadNavigationMenuHelper.navigationMenuSetup(_datapadActionSetup.getDatapadTFTLCD(), &Aurebesh8pt7b, _datapadDisplayButtons);
    datapadNavigationMenuHelper.refreshNavigationMenu(_datapadActionSetup.getDatapadTFTLCD(), &Aurebesh8pt7b, _datapadDisplayButtons);
}

void DatapadNavigationMenu::clicked(DatapadDisplayPoint datapadDisplayPoint)
{
    if (!_playing)
    {
        for (int16_t counter = 0; counter < NAVIGATION_MENU_BUTTONS_ITEMS; counter++)
        {
            if (_datapadDisplayButtons[counter].contains(datapadDisplayPoint))
            {
                _playing = true;
                _datapadDisplayButtons[counter].press();
                DatapadNavigationMenuHelper datapadNavigationMenuHelper;
                datapadNavigationMenuHelper.playDatapadaAction(_datapadDisplayButtons[counter].getDatapadActionType(), _datapadActionSetup);
                _previousMillis = millis();
                break;
            }
        }
    }
    else
    {
        reset();
    }
}

bool DatapadNavigationMenu::isInactive()
{
    bool result = false;
    if (_playing)
    {
        if (millis() - _previousMillis > _inactivityInterval)
        {
            _playing = false;
            result = true;
        }
    }
    return result;
}

void DatapadNavigationMenu::reset()
{
    _playing = false;
    _previousMillis = 0;
    DatapadNavigationMenuHelper datapadNavigationMenuHelper;
    datapadNavigationMenuHelper.playDatapadaAction(DatapadActionType::StandBy, _datapadActionSetup);
    datapadNavigationMenuHelper.refreshNavigationMenu(_datapadActionSetup.getDatapadTFTLCD(), &Aurebesh8pt7b, _datapadDisplayButtons);
}