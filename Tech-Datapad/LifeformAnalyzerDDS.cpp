//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "LifeformAnalyzerDDS.h"
#include "DDSIrlingBDB.h"
#include "DDSTextPrinter.h"
#include "DDSBlinkingDot.h"
#include "DDSProgressBar.h"
#include "Fonts/Aurebesh2pt7b.h"

class CreatureAnalyzerDDSHelper
{
public:
    void drawCreatureAnalyzer(DatapadTFTLCD &datapadTFTLCD)
    {
        int16_t width = datapadTFTLCD.width();
        int16_t centerX = width / 2;
        int16_t centerY = datapadTFTLCD.height() / 2;
        int16_t radius = centerX - 1;
        drawFixedScreenDetails(datapadTFTLCD, centerX, centerY, radius, width);
        runCreatureAnalyzerAnimations();
    }

private:
    DDSBlinkingDot *_ddsBlinkingDot;
    DDSProgressBar *_progressBar0, *_progressBar1, *_progressBar2, *_progressBar3, *_progressBar4;

    void drawFixedScreenDetails(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius, int16_t width)
    {
        //Draw Irling B.
        DDSIrlingBDB ddsIrlingBDB = DDSIrlingBDB(datapadTFTLCD);
        ddsIrlingBDB.drawRGBBitmap(centerX - (ddsIrlingBDB.width() / 2), centerY - (ddsIrlingBDB.height() / 2));
        //Round Frame.
        datapadTFTLCD.drawRoundFrame(centerX, centerY, radius, 90, true, GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR, DISPLAY_BACK_COLOR);
        datapadTFTLCD.fillRect(centerX - 4, centerY - radius, 8, 14, DISPLAY_BACK_COLOR);
        datapadTFTLCD.fillRect(centerX - 4, centerY + radius + 1, 8, -13, DISPLAY_BACK_COLOR);
        int16_t roundedFrameDetailHeight = (width * 0.39);
        int16_t roundedFrameDetailTop = centerY - roundedFrameDetailHeight;
        int16_t lineWidth = 2;
        drawRoudedFrameDetail(datapadTFTLCD, centerX, roundedFrameDetailTop, width, false);
        roundedFrameDetailTop = centerY + roundedFrameDetailHeight;
        drawRoudedFrameDetail(datapadTFTLCD, centerX, roundedFrameDetailTop, width, true);
        //Draw Red Dot.
        _ddsBlinkingDot = new DDSBlinkingDot(datapadTFTLCD, centerX - (width * 0.28), centerY - (width * 0.3), width * 0.017, TFT_RED, DISPLAY_BACK_COLOR);
        //Draw Right Rectangle
        int16_t rightRectangleTop = centerY + (width * 0.08);
        int16_t rightRectangleLeft = centerX - (width * 0.33);
        int16_t rightRectanglewidth = width * 0.18;
        int16_t rightRectangleHeight = width * 0.22;
        datapadTFTLCD.drawRectangle(rightRectangleLeft, rightRectangleTop, rightRectanglewidth, rightRectangleHeight, 2, TFT_WHITE);
        int16_t lineLeft = rightRectangleLeft + (width * 0.14);
        datapadTFTLCD.drawFastVerticalLine(lineLeft, rightRectangleTop, -(width * 0.14), 3, TFT_WHITE);
        lineWidth = rightRectangleLeft + rightRectanglewidth - lineLeft - 1;
        int16_t lineTop = rightRectangleTop - (width * 0.02);
        datapadTFTLCD.drawFastHorizontalLine(lineLeft, lineTop, lineWidth, 3, TFT_WHITE);
        datapadTFTLCD.drawFastVerticalLine(lineLeft + lineWidth - 2, lineTop, -(width * 0.06), 3, TFT_WHITE);
        int16_t leftTextPadding = 4;
        int16_t topTextPadding = 11;
        int16_t textHeight = 4;
        int16_t lineSeparation = 4;
        datapadTFTLCD.setFont(&Aurebesh2pt7b);
        datapadTFTLCD.setTextColor(TFT_RED);
        datapadTFTLCD.setCursor(rightRectangleLeft + leftTextPadding, rightRectangleTop + topTextPadding);
        datapadTFTLCD.print(CREATURE_ANALYZER_TITLE_A_TEXT);
        datapadTFTLCD.setTextColor(TFT_WHITE);
        DDSTextPrinter *ddsTextPrinter = new DDSTextPrinter(datapadTFTLCD, rightRectangleLeft + leftTextPadding + 1, rightRectangleTop + topTextPadding + lineSeparation, rightRectanglewidth, rightRectangleHeight, textHeight, lineSeparation, DISPLAY_BACK_COLOR);
        ddsTextPrinter->print(creatureAnalyzerParagraph1, sizeof(creatureAnalyzerParagraph1) / sizeof(creatureAnalyzerParagraph1[0]), true);
        delete ddsTextPrinter;
        //Draw Left Rectangle
        int16_t leftRectangleTop = centerY + (width * 0.14);
        int16_t leftRectangleLeft = centerX + (width * 0.155);
        int16_t leftRectanglewidth = width * 0.23;
        int16_t leftRectangleHeight = width * 0.11;
        datapadTFTLCD.drawRectangle(leftRectangleLeft, leftRectangleTop, leftRectanglewidth, leftRectangleHeight, 2, TFT_WHITE);
        lineLeft = centerX + (width * 0.30);
        lineTop = (width * 0.13);
        datapadTFTLCD.drawFastVerticalLine(lineLeft, leftRectangleTop, -lineTop, 3, TFT_WHITE);
        datapadTFTLCD.drawFastHorizontalLine(lineLeft + 1, leftRectangleTop - lineTop, -(width * 0.26), 3, TFT_WHITE);
        topTextPadding = 8;
        lineSeparation = 3;
        datapadTFTLCD.setTextColor(TFT_RED);
        datapadTFTLCD.setCursor(leftRectangleLeft + leftTextPadding, leftRectangleTop + topTextPadding);
        datapadTFTLCD.print(CREATURE_ANALYZER_TITLE_B_TEXT);
        datapadTFTLCD.setTextColor(TFT_WHITE);
        ddsTextPrinter = new DDSTextPrinter(datapadTFTLCD, leftRectangleLeft + leftTextPadding + 1, leftRectangleTop + topTextPadding + lineSeparation, leftRectanglewidth, leftRectangleHeight, textHeight, lineSeparation, DISPLAY_BACK_COLOR);
        ddsTextPrinter->print(creatureAnalyzerParagraph2, sizeof(creatureAnalyzerParagraph2) / sizeof(creatureAnalyzerParagraph2[0]), true);
        delete ddsTextPrinter;
        //Draw Red Bars.
        lineLeft = centerX + (width * 0.08);
        lineTop = centerY + (width * 0.36);
        lineWidth = width * 0.15;
        datapadTFTLCD.drawFastHorizontalLine(lineLeft, lineTop, lineWidth, 3, TFT_WHITE);
        int16_t progressBarHeight = width * 0.07;
        lineLeft = lineLeft + (width * 0.007);
        lineWidth = width * 0.02;
        randomSeed(millis());
        _progressBar0 = new DDSProgressBar(datapadTFTLCD, lineLeft, lineTop - progressBarHeight, lineWidth, progressBarHeight, TFT_RED, DISPLAY_BACK_COLOR, random(75, 95), 0.25);
        lineSeparation = (width * 0.009);
        lineLeft = lineLeft + lineWidth + lineSeparation;
        _progressBar1 = new DDSProgressBar(datapadTFTLCD, lineLeft, lineTop - progressBarHeight, lineWidth, progressBarHeight, TFT_RED, DISPLAY_BACK_COLOR, random(35, 55), 0.30);
        lineLeft = lineLeft + lineWidth + lineSeparation;
        _progressBar2 = new DDSProgressBar(datapadTFTLCD, lineLeft, lineTop - progressBarHeight, lineWidth, progressBarHeight, TFT_RED, DISPLAY_BACK_COLOR, random(55, 85), 0.40);
        lineLeft = lineLeft + lineWidth + (width * 0.012);
        _progressBar3 = new DDSProgressBar(datapadTFTLCD, lineLeft, lineTop - progressBarHeight, lineWidth, progressBarHeight, TFT_RED, DISPLAY_BACK_COLOR, random(25, 55), 0.25);
        lineLeft = lineLeft + lineWidth + (width * 0.015);
        _progressBar4 = new DDSProgressBar(datapadTFTLCD, lineLeft, lineTop - progressBarHeight, lineWidth, progressBarHeight, TFT_RED, DISPLAY_BACK_COLOR, random(45, 75), 0.40);
    }

    void drawRoudedFrameDetail(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t y, int16_t width, bool inverted)
    {
        int16_t lineWidth = 2;
        int16_t halfLineWidth = lineWidth / 2;
        int16_t mutiplier = 1;
        int16_t substractor = 1;
        if (inverted)
        {
            mutiplier = -1;
            substractor = 0;
        }
        int16_t lineOffset = lineWidth * mutiplier;
        //Draw base Line.
        int16_t baseLineWidth = getWidth(width, 0.44);
        int16_t baseLineHeight = lineOffset;
        int16_t baseLineTop = y - baseLineHeight;
        int16_t baseLineLeft = centerX - (baseLineWidth / 2);
        datapadTFTLCD.fillRect(baseLineLeft, baseLineTop, baseLineWidth, baseLineHeight, DISPLAY_RING_COLOR);
        //Draw little base rectangle.
        int16_t rectangleWidth = getWidth(width, 0.21);
        int16_t rectangleHeight = getWidth(width, 0.03);
        int16_t rectangleTop = baseLineTop - (rectangleHeight * substractor) + lineOffset;
        int16_t rectangleLeft = centerX - (rectangleWidth / 2);
        datapadTFTLCD.drawRectangle(rectangleLeft, rectangleTop, rectangleWidth, rectangleHeight, lineWidth, DISPLAY_RING_COLOR);
        //Draw bigger base rectangle.
        int16_t segmentWidth = getWidth(width, 0.07);
        int16_t subSegmentWidth = getWidth(width, 0.02) * mutiplier;
        rectangleWidth = getWidth(width, 0.26);
        rectangleHeight = getWidth(width, 0.045) * mutiplier;
        rectangleTop = baseLineTop - rectangleHeight + lineOffset;
        rectangleLeft = centerX - (rectangleWidth / 2) - halfLineWidth;
        datapadTFTLCD.fillRect(rectangleLeft, rectangleTop, lineWidth, rectangleHeight, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillRect(rectangleLeft, rectangleTop, segmentWidth, lineOffset, DISPLAY_RING_COLOR);
        if (!inverted)
        {
            datapadTFTLCD.drawLine(rectangleLeft + segmentWidth, rectangleTop, rectangleLeft + segmentWidth + subSegmentWidth, rectangleTop + subSegmentWidth, lineWidth, DISPLAY_RING_COLOR);
        }
        else
        {
            datapadTFTLCD.drawLine(rectangleLeft + segmentWidth, rectangleTop + lineOffset, rectangleLeft + segmentWidth - subSegmentWidth, rectangleTop + subSegmentWidth + lineOffset, lineWidth, DISPLAY_RING_COLOR);
        }
        rectangleLeft = rectangleLeft + rectangleWidth - halfLineWidth;
        datapadTFTLCD.fillRect(rectangleLeft, rectangleTop, lineWidth, rectangleHeight, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillRect(rectangleLeft - segmentWidth + lineWidth, rectangleTop, segmentWidth, lineOffset, DISPLAY_RING_COLOR);
        if (!inverted)
        {
            datapadTFTLCD.drawLine(rectangleLeft - segmentWidth, rectangleTop, rectangleLeft - segmentWidth - subSegmentWidth, rectangleTop + subSegmentWidth, lineWidth, DISPLAY_RING_COLOR);
        }
        else
        {
            datapadTFTLCD.drawLine(rectangleLeft + subSegmentWidth - segmentWidth, rectangleTop + subSegmentWidth + lineOffset, rectangleLeft - segmentWidth, rectangleTop + lineOffset, lineWidth, DISPLAY_RING_COLOR);
        }
        //Draw little external line.
        rectangleWidth = getWidth(width, 0.32);
        rectangleHeight = getWidth(width, 0.03) * mutiplier;
        rectangleTop = baseLineTop - rectangleHeight + lineOffset;
        rectangleLeft = centerX - (rectangleWidth / 2) - halfLineWidth;
        datapadTFTLCD.fillRect(rectangleLeft, rectangleTop, lineWidth, rectangleHeight, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillRect(rectangleLeft + rectangleWidth - halfLineWidth, rectangleTop, lineWidth, rectangleHeight, DISPLAY_RING_COLOR);
        //Draw bigger external line.
        rectangleWidth = getWidth(width, 0.36);
        rectangleHeight = getWidth(width, 0.0175) * mutiplier;
        rectangleTop = baseLineTop - rectangleHeight + lineOffset;
        rectangleLeft = centerX - (rectangleWidth / 2) - halfLineWidth;
        datapadTFTLCD.fillRect(rectangleLeft, rectangleTop, lineWidth, rectangleHeight, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillRect(rectangleLeft + rectangleWidth - halfLineWidth, rectangleTop, lineWidth, rectangleHeight, DISPLAY_RING_COLOR);
    }

    int16_t getWidth(int16_t reference, float percentage)
    {
        int16_t result = 0;
        result = reference * percentage;
        if (result % 2 != 0)
            result--;
        return result;
    }

    void runCreatureAnalyzerAnimations()
    {
        _progressBar0->show();
        _progressBar1->show();
        _progressBar2->show();
        _progressBar3->show();
        _progressBar4->show();
        int16_t elapsed = 0;
        int16_t interval = 7500;
        unsigned long previousMillis = millis();
        do
        {
            _progressBar0->update();
            _progressBar1->update();
            _progressBar2->update();
            _progressBar3->update();
            _progressBar4->update();
            _ddsBlinkingDot->update();
            elapsed += millis() - previousMillis;
            previousMillis = millis();
        } while (elapsed < interval);
        delete _progressBar0;
        delete _progressBar1;
        delete _progressBar2;
        delete _progressBar3;
        delete _progressBar4;
        delete _ddsBlinkingDot;
    }
};

LifeformAnalyzerDDS::LifeformAnalyzerDDS(DatapadTFTLCD &datapadTFTLCD) : StandByDDS(datapadTFTLCD), _datapadTFTLCD(datapadTFTLCD) {}

void LifeformAnalyzerDDS::show()
{
    StandByDDS::show();
    CreatureAnalyzerDDSHelper creatureAnalyzerDDSHelper;
    creatureAnalyzerDDSHelper.drawCreatureAnalyzer(_datapadTFTLCD);
}