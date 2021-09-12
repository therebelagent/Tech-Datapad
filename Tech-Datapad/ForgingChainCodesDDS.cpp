//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "ForgingChainCodesDDS.h"
#include "DDSGraphicalUtility.h"
#include "DatapadDisplaySequenceConstants.h"
#include "Fonts/Aurebesh3pt7b.h"

class TextPrinter
{
public:
    TextPrinter(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t width, int16_t height, int16_t lineHeight, int16_t lineVerticalGap, int16_t backColour) : _tftlcd(tftlcd), _x(x), _y(y), _width(width), _height(height), _lineHeight(lineHeight), _lineVerticalGap(lineVerticalGap), _backColor(backColour) {}

    void print(const char *const paragraph[], byte paragraphSize)
    {
        int16_t lineTop = _y;
        int16_t x1, y1;
        reset();
        paragraphSize = getParagraphSize(paragraphSize);
        for (int16_t line = 0; line < paragraphSize; line++)
        {
            strcpy_P(_buffer, (char *)pgm_read_word(&(paragraph[line])));
            print(_x, lineTop, _buffer);
            lineTop += _lineHeight + _lineVerticalGap;
        }
    }

    void scroll(const char *const paragraph[], byte paragraphSize, int16_t steps = 1)
    {
        bool paragraphScrolled = false;
        int16_t currentLineTop = _y;
        int16_t previousTop;
        reset();
        paragraphSize = getParagraphSize(paragraphSize);
        for (int16_t lineCounter = 1; lineCounter <= _height; lineCounter += steps)
        {
            int16_t lineTop = currentLineTop;
            for (int16_t line = 0; line < paragraphSize; line++)
            {
                previousTop = _paragraphPreviousTop[line];
                if (previousTop > 0)
                {
                    _tftlcd.fillRect(_x, previousTop - _lineHeight, _width, _lineHeight + _lineVerticalGap, _backColor);
                }
            }
            for (int16_t line = 0; line < paragraphSize; line++)
            {
                if (lineTop + _lineHeight + _lineVerticalGap > _y + _height)
                {
                    _tftlcd.fillRect(_x, _y + _height - _lineHeight * 1.5, _width, -_lineHeight, _backColor);
                    if (line == 0)
                        paragraphScrolled = true;
                    break;
                }
                strcpy_P(_buffer, (char *)pgm_read_word(&(paragraph[line])));
                print(_x, lineTop, _buffer);
                _paragraphPreviousTop[line] = lineTop;
                lineTop += _lineHeight + _lineVerticalGap;
            }
            currentLineTop += steps + _lineVerticalGap;
            if (paragraphScrolled)
            {
                break;
            }
            delay(50);
        }
        _tftlcd.fillRect(_x, _y + _height - _lineHeight * 2, _width, -_lineHeight, _backColor);
    }

private:
    MCUFRIEND_kbv &_tftlcd;
    const int16_t _x, _y, _width, _height, _lineHeight, _lineVerticalGap, _backColor;
    int16_t _paragraphPreviousTop[FORGING_CHAIN_CODES_PARAGRAPH_MAX_ITEMS];
    char _buffer[FORGING_CHAIN_CODES_SENTENCE_BUFFER_SIZE];

    void print(int16_t x, int16_t y, const char *text)
    {
        _tftlcd.setCursor(x, y);
        _tftlcd.print(text);
    }

    byte getParagraphSize(byte currentParagraphSize)
    {
        byte paragraphSize = currentParagraphSize;
        if (currentParagraphSize > FORGING_CHAIN_CODES_PARAGRAPH_MAX_ITEMS)
            paragraphSize = FORGING_CHAIN_CODES_PARAGRAPH_MAX_ITEMS;
        return paragraphSize;
    }

    void reset()
    {
        for (int16_t line = 0; line < FORGING_CHAIN_CODES_PARAGRAPH_MAX_ITEMS; line++)
        {
            _paragraphPreviousTop[line] = 0;
        }
        _tftlcd.fillRect(_x, _y - 3, _width, _height, _backColor);
    }
};

class ForgingChainCodesDDSHelper
{
public:
    void drawForgingChainCodes(MCUFRIEND_kbv &tftlcd)
    {
        int16_t width = tftlcd.width();
        int16_t centerX = width / 2;
        int16_t centerY = tftlcd.height() / 2;
        int16_t radius = centerX - 1;
        drawFixedScreenDetails(tftlcd, centerX, centerY, radius, width);
        //Draw Window Scroll Animation.
        int16_t windowsScrollLeft = _rectangularFrameLeft + 7;
        int16_t windowScrollWidth = _rectangularFrameWidth - 14;
        int16_t windowScrollTop = _rectangularFrameTop - 1;
        int16_t windowScrollHeight = _rectangularFrameHeight + 19;
        tftlcd.setFont(&Aurebesh3pt7b);
        tftlcd.setTextColor(DISPLAY_RING_COLOR);
        int16_t lineVerticalGap = 2;
        int16_t lineHeight = 4;
        int16_t steps = 50;
        TextPrinter textPrinter = TextPrinter(tftlcd, windowsScrollLeft, windowScrollTop, windowScrollWidth, windowScrollHeight, lineHeight, lineVerticalGap, DISPLAY_BACK_COLOR);
        textPrinter.scroll(forgingChainCodesParagraph1, sizeof(forgingChainCodesParagraph1) / sizeof(forgingChainCodesParagraph1[0]), steps);
        textPrinter.scroll(forgingChainCodesParagraph2, sizeof(forgingChainCodesParagraph2) / sizeof(forgingChainCodesParagraph2[0]), steps);
        textPrinter.scroll(forgingChainCodesParagraph3, sizeof(forgingChainCodesParagraph3) / sizeof(forgingChainCodesParagraph3[0]), steps);
        textPrinter.scroll(forgingChainCodesParagraph4, sizeof(forgingChainCodesParagraph4) / sizeof(forgingChainCodesParagraph4[0]), steps);
        textPrinter.scroll(forgingChainCodesParagraph5, sizeof(forgingChainCodesParagraph5) / sizeof(forgingChainCodesParagraph5[0]), steps);
    }

private:
    int16_t _rectangularFrameHeight, _rectangularFrameTop, _rectangularFrameLeft, _rectangularFrameWidth;

    DDSGraphicalUtility _ddsGraphicalUtility;

    void drawFixedScreenDetails(MCUFRIEND_kbv &tftlcd, int16_t centerX, int16_t centerY, int16_t radius, int16_t width)
    {
        //Draw Rounded Frame.
        _ddsGraphicalUtility.drawRoundFrame(tftlcd, centerX, centerY, radius, 45, false);
        //Draw Fixed Rectangular Frame
        _rectangularFrameHeight = width * 0.62;
        _rectangularFrameTop = centerY - _rectangularFrameHeight / 2;
        _rectangularFrameWidth = width * 0.6;
        _rectangularFrameLeft = centerX - _rectangularFrameWidth / 2;
        _ddsGraphicalUtility.drawFastVerticalLine(tftlcd, _rectangularFrameLeft + 1, _rectangularFrameTop, _rectangularFrameHeight, 3, FORGING_CHAIN_CODES_RECTANGULAR_FRAME_COLOR);
        _ddsGraphicalUtility.drawFastVerticalLine(tftlcd, _rectangularFrameLeft + _rectangularFrameWidth - 2, _rectangularFrameTop, _rectangularFrameHeight, 3, FORGING_CHAIN_CODES_RECTANGULAR_FRAME_COLOR);
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
            _ddsGraphicalUtility.drawFastHorizontalLine(tftlcd, leftDashedBarLeft, dashedBarTop, dashedBarLineWidth * -1, 2, FORGING_CHAIN_CODES_RECTANGULAR_FRAME_COLOR);
            _ddsGraphicalUtility.drawFastHorizontalLine(tftlcd, rightDashedBarLeft, dashedBarTop, dashedBarLineWidth, 2, FORGING_CHAIN_CODES_RECTANGULAR_FRAME_COLOR);
            dashedBarTop = dashedBarTop + dashedBarLineHeight + 1;
        }
    }
};

ForgingChainCodesDDS::ForgingChainCodesDDS(MCUFRIEND_kbv &tftlcd) : StandByDDS(tftlcd), _tftlcd(tftlcd) {}

void ForgingChainCodesDDS::show()
{
    StandByDDS::show();
    ForgingChainCodesDDSHelper forgingChainCodesDDSHelper;
    forgingChainCodesDDSHelper.drawForgingChainCodes(_tftlcd);
}