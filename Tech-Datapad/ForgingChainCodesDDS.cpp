//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "ForgingChainCodesDDS.h"
#include "DDSTextPrinter.h"
#include "Fonts/Aurebesh3pt7b.h"

class ForgingChainCodesDDSHelper
{
public:
    void drawForgingChainCodes(DatapadTFTLCD &datapadTFTLCD)
    {
        int16_t width = datapadTFTLCD.width();
        int16_t centerX = width / 2;
        int16_t centerY = datapadTFTLCD.height() / 2;
        int16_t radius = centerX - 1;
        drawFixedScreenDetails(datapadTFTLCD, centerX, centerY, radius, width);
        //Draw Window Scroll Animation.
        datapadTFTLCD.setFont(&Aurebesh3pt7b);
        datapadTFTLCD.setTextColor(DISPLAY_RING_COLOR);
        int16_t lineVerticalGap = 2;
        int16_t lineHeight = 4;
        int16_t windowsScrollLeft = _rectangularFrameLeft + 7;
        int16_t windowScrollWidth = _rectangularFrameWidth - 14;
        int16_t windowScrollTop = _rectangularFrameTop - lineHeight;
        int16_t windowScrollHeight = _rectangularFrameHeight + 19;
        int16_t steps = 50;
        DDSTextPrinter ddsTextPrinter = DDSTextPrinter(datapadTFTLCD, windowsScrollLeft, windowScrollTop, windowScrollWidth, windowScrollHeight, lineHeight, lineVerticalGap, DISPLAY_BACK_COLOR);
        ddsTextPrinter.scrollDown(forgingChainCodesParagraph1, sizeof(forgingChainCodesParagraph1) / sizeof(forgingChainCodesParagraph1[0]), steps);
        ddsTextPrinter.scrollDown(forgingChainCodesParagraph2, sizeof(forgingChainCodesParagraph2) / sizeof(forgingChainCodesParagraph2[0]), steps);
        ddsTextPrinter.scrollDown(forgingChainCodesParagraph3, sizeof(forgingChainCodesParagraph3) / sizeof(forgingChainCodesParagraph3[0]), steps);
        ddsTextPrinter.scrollDown(forgingChainCodesParagraph4, sizeof(forgingChainCodesParagraph4) / sizeof(forgingChainCodesParagraph4[0]), steps);
        ddsTextPrinter.scrollDown(forgingChainCodesParagraph5, sizeof(forgingChainCodesParagraph5) / sizeof(forgingChainCodesParagraph5[0]), steps);
    }

private:
    int16_t _rectangularFrameHeight, _rectangularFrameTop, _rectangularFrameLeft, _rectangularFrameWidth;

    void drawFixedScreenDetails(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius, int16_t width)
    {
        //Draw Rounded Frame.
        datapadTFTLCD.drawRoundFrame(centerX, centerY, radius, 45, false, GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR, DISPLAY_BACK_COLOR);
        //Draw Fixed Rectangular Frame
        _rectangularFrameHeight = width * 0.62;
        _rectangularFrameTop = centerY - _rectangularFrameHeight / 2;
        _rectangularFrameWidth = width * 0.6;
        _rectangularFrameLeft = centerX - _rectangularFrameWidth / 2;
        datapadTFTLCD.drawFastVerticalLine(_rectangularFrameLeft + 1, _rectangularFrameTop, _rectangularFrameHeight, 3, FORGING_CHAIN_CODES_RECTANGULAR_FRAME_COLOR);
        datapadTFTLCD.drawFastVerticalLine(_rectangularFrameLeft + _rectangularFrameWidth - 2, _rectangularFrameTop, _rectangularFrameHeight, 3, FORGING_CHAIN_CODES_RECTANGULAR_FRAME_COLOR);
        //Draw External Dashed Bar.
        int16_t dashedBarHeight = width * 0.39;
        int16_t dashedBarTop = centerY - (dashedBarHeight / 2);
        int16_t leftDashedBarLeft = _rectangularFrameLeft - 3;
        int16_t rightDashedBarLeft = (_rectangularFrameLeft + _rectangularFrameWidth - 2) + 5;
        int16_t dashedBarLines = 31;
        int16_t dashedBarLineHeight = (dashedBarHeight / dashedBarLines) - 1;
        int16_t dashedBarLineWidth;
        for (int16_t counter = 1; counter <= dashedBarLines; counter++)
        {
            if (counter == 1 || counter == 11 || counter == 21 || counter == 31)
            {
                dashedBarLineWidth = width * 0.03;
            }
            else
            {
                dashedBarLineWidth = width * 0.02;
            }
            datapadTFTLCD.drawFastHorizontalLine(leftDashedBarLeft, dashedBarTop, dashedBarLineWidth * -1, 2, FORGING_CHAIN_CODES_RECTANGULAR_FRAME_COLOR);
            datapadTFTLCD.drawFastHorizontalLine(rightDashedBarLeft, dashedBarTop, dashedBarLineWidth, 2, FORGING_CHAIN_CODES_RECTANGULAR_FRAME_COLOR);
            dashedBarTop = dashedBarTop + dashedBarLineHeight + 1;
        }
    }
};

ForgingChainCodesDDS::ForgingChainCodesDDS(DatapadTFTLCD &datapadTFTLCD) : StandByDDS(datapadTFTLCD), _datapadTFTLCD(datapadTFTLCD) {}

void ForgingChainCodesDDS::show()
{
    StandByDDS::show();
    ForgingChainCodesDDSHelper forgingChainCodesDDSHelper;
    forgingChainCodesDDSHelper.drawForgingChainCodes(_datapadTFTLCD);
}