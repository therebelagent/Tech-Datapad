//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "LifeformAnalyzerDDS.h"
#include "DDSIrlingBImage.h"
#include "DDSIrlingAImage.h"
#include "DDSTextPrinter.h"
#include "DDSBlinkingDot.h"
#include "DDSProgressBar.h"
#include "Fonts/Aurebesh2pt7b.h"
#include "Fonts/Aurebesh4pt7b.h"
#include "Fonts/Aurebesh6pt7b.h"
#include "Fonts/Aurebesh10pt7b.h"

class CreatureAnalyzerDDSHelper
{
public:
    void drawCreatureAnalyzer(IDatapadTFTLCD &datapadTFTLCD)
    {
        int16_t width = datapadTFTLCD.width();
        int16_t centerX = width / 2;
        int16_t centerY = datapadTFTLCD.height() / 2;
        int16_t radius = centerX - 1;
        drawIrlingAScreenAnalyzer(datapadTFTLCD, centerX, centerY, radius, width);
        datapadTFTLCD.fillScreen(DISPLAY_BACK_COLOR);
        drawIrlingBScreenAnalyzer(datapadTFTLCD, centerX, centerY, radius, width);
    }

private:
    DDSBlinkingDot *_ddsBlinkingDot;
    DDSProgressBar *_progressBar0, *_progressBar1, *_progressBar2, *_progressBar3, *_progressBar4;
    int16_t _innerBoxWidth, _innerBoxHeight, _innerBoxTop, _innerBoxLeft;
    int16_t _dotRadius, _dotTop, _dotALeft, _dotBLeft;
    int16_t _lineWidth = 2;

    void drawIrlingAScreenAnalyzer(IDatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t radius, int16_t width)
    {
        //Draw Irling A.
        DDSIrlingAImage ddsIrlingAImage = DDSIrlingAImage(datapadTFTLCD);
        ddsIrlingAImage.drawImage(x - (ddsIrlingAImage.width() / 2), y - (width * 0.33));
        //Draw Fixed Screen Details.
        drawFixedScreenDetails(datapadTFTLCD, x, y, radius, width);
        drawIrlingAFixedScreenDetails(datapadTFTLCD, x, y, radius, width);
        nonBlockingDelay(500);
        swapDotColors(datapadTFTLCD);
        remarkCreatureNameBanner(datapadTFTLCD, LIFEFORM_ANALYZER_CREATURE_NAME_L1_COLOR, true);
        nonBlockingDelay(75);
        remarkCreatureNameBanner(datapadTFTLCD, LIFEFORM_ANALYZER_CREATURE_NAME_L2_COLOR, true);
        nonBlockingDelay(75);
        remarkCreatureNameBanner(datapadTFTLCD, LIFEFORM_ANALYZER_CREATURE_NAME_L3_COLOR, true);
        nonBlockingDelay(75);
        remarkCreatureNameBanner(datapadTFTLCD, LIFEFORM_ANALYZER_CREATURE_NAME_L4_COLOR, true);
        nonBlockingDelay(750);
    }

    void drawIrlingAFixedScreenDetails(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius, int16_t width)
    {
        //Draw Blue Inner Boxes.
        int16_t blueBoxTop = centerY - (width * 0.295);
        int16_t blueBoxLeft = centerX + (width * 0.03);
        int16_t blueBoxHeight = width * 0.17;
        int16_t blueBoxWidth = width * 0.3;
        datapadTFTLCD.drawRectangle(blueBoxLeft, blueBoxTop, blueBoxWidth, blueBoxHeight, _lineWidth, DISPLAY_RING_COLOR);
        int16_t innerBoxHeight = width * 0.14;
        int16_t innerBoxWidth = width * 0.27;
        int16_t innerBoxTop = (blueBoxTop + (blueBoxHeight / 2)) - (innerBoxHeight / 2);
        int16_t innerBoxLeft = (blueBoxLeft + (blueBoxWidth / 2)) - (innerBoxWidth / 2);
        datapadTFTLCD.drawRectangle(innerBoxLeft, innerBoxTop, innerBoxWidth, innerBoxHeight, _lineWidth, DISPLAY_RING_COLOR);
        innerBoxWidth = width * 0.17;
        innerBoxLeft = (blueBoxLeft + (blueBoxWidth / 2)) - (innerBoxWidth / 2) - (_lineWidth / 2);
        datapadTFTLCD.fillRect(innerBoxLeft, blueBoxTop, innerBoxWidth, blueBoxHeight, DISPLAY_BACK_COLOR);
        innerBoxHeight = width * 0.08;
        innerBoxTop = (blueBoxTop + (blueBoxHeight / 2)) - (innerBoxHeight / 2);
        innerBoxLeft = blueBoxLeft - (_lineWidth / 2);
        datapadTFTLCD.fillRect(innerBoxLeft, innerBoxTop, blueBoxWidth, innerBoxHeight, DISPLAY_BACK_COLOR);
        //Draw Red Box.
        _innerBoxWidth = width * 0.26;
        _innerBoxHeight = width * 0.08;
        _innerBoxTop = (blueBoxTop + (blueBoxHeight / 2)) - (_innerBoxHeight / 2);
        _innerBoxLeft = (blueBoxLeft + (blueBoxWidth / 2)) - (_innerBoxWidth / 2) - (_lineWidth / 2);
        remarkCreatureNameBanner(datapadTFTLCD, LIFEFORM_ANALYZER_CREATURE_NAME_L0_COLOR, false);
        //Draw White Half Moon.
        int16_t whiteBoxHeight = width * 0.17;
        int16_t whiteTopLineTop = centerY + (width * 0.19);
        int16_t whiteTopLineWidth = width * 0.74;
        int16_t whiteTopLineLeft = centerX - (whiteTopLineWidth / 2);
        datapadTFTLCD.drawFastHorizontalLine(whiteTopLineLeft, whiteTopLineTop, whiteTopLineWidth, _lineWidth, TFT_WHITE);
        int16_t whiteBottomLineTop = whiteTopLineTop + whiteBoxHeight;
        int16_t whiteBottomLineWidth = width * 0.44;
        int16_t whiteBottomLineLeft = centerX - (whiteBottomLineWidth / 2);
        datapadTFTLCD.drawFastHorizontalLine(whiteBottomLineLeft, whiteBottomLineTop, whiteBottomLineWidth, _lineWidth, TFT_WHITE);
        int16_t whiteArcLineRadius = radius - (width * 0.08);
        datapadTFTLCD.fillArc(centerX, centerY, 117, 11, whiteArcLineRadius, whiteArcLineRadius, 1, TFT_WHITE);
        datapadTFTLCD.fillArc(centerX, centerY, 210, 11, whiteArcLineRadius, whiteArcLineRadius, 1, TFT_WHITE);
        //Print Gleg Description.
        datapadTFTLCD.setCursor(whiteTopLineLeft + (width * 0.06), whiteTopLineTop + (width * 0.04));
        datapadTFTLCD.setFont(&Aurebesh6pt7b);
        datapadTFTLCD.setTextColor(LIFEFORM_ANALYZER_CREATURE_NAME_L0_COLOR);
        datapadTFTLCD.print(LIFEFORM_ANALYZER_CREATURE_NAME_TEXT);
        int16_t textBoxHeight = width * 0.11;
        int16_t textBoxWidth = whiteBottomLineWidth + (width * 0.03);
        int16_t textBoxLeft = centerX - (textBoxWidth / 2);
        int16_t textBoxTop = whiteBottomLineTop - textBoxHeight;
        datapadTFTLCD.setFont(&Aurebesh4pt7b);
        datapadTFTLCD.setTextColor(TFT_WHITE);
        DDSTextPrinter ddsTextPrinter = DDSTextPrinter(datapadTFTLCD, textBoxLeft, textBoxTop, textBoxWidth, textBoxHeight, 5, 2, DISPLAY_BACK_COLOR);
        ddsTextPrinter.print(lifeformAnalyzerParagraph3, sizeof(lifeformAnalyzerParagraph3) / sizeof(lifeformAnalyzerParagraph3[0]), true);
        //Draw Red & White Dots.
        _dotRadius = width * 0.017;
        _dotTop = whiteTopLineTop - (width * 0.055);
        _dotALeft = whiteTopLineLeft + whiteTopLineWidth - _dotRadius;
        datapadTFTLCD.fillCircle(_dotALeft, _dotTop, _dotRadius, TFT_WHITE);
        _dotBLeft = _dotALeft - width * 0.05;
        datapadTFTLCD.fillCircle(_dotBLeft, _dotTop, _dotRadius, LIFEFORM_ANALYZER_CREATURE_NAME_L0_COLOR);
        //Draw Indicator Line.
        int16_t lineX0Left = centerX - (width * 0.16);
        int16_t lineY0Top = whiteTopLineTop - (width * 0.15);
        int16_t lineX1Left = centerX - (width * 0.08);
        int16_t lineY1Top = whiteTopLineTop;
        datapadTFTLCD.drawLine(lineX0Left, lineY0Top, lineX1Left, lineY1Top, _lineWidth, TFT_WHITE);
    }

    void swapDotColors(IDatapadTFTLCD &datapadTFTLCD)
    {
        datapadTFTLCD.fillCircle(_dotALeft, _dotTop, _dotRadius, LIFEFORM_ANALYZER_CREATURE_NAME_L0_COLOR);
        datapadTFTLCD.fillCircle(_dotBLeft, _dotTop, _dotRadius, TFT_WHITE);
    }

    void remarkCreatureNameBanner(IDatapadTFTLCD &datapadTFTLCD, uint16_t color, boolean drawRemark)
    {
        if (drawRemark)
            datapadTFTLCD.drawRectangle(_innerBoxLeft, _innerBoxTop, _innerBoxWidth, _innerBoxHeight, _lineWidth, LIFEFORM_ANALYZER_CREATURE_NAME_L0_COLOR);
        datapadTFTLCD.printCenteredText(LIFEFORM_ANALYZER_CREATURE_NAME_TEXT, &Aurebesh10pt7b, _innerBoxLeft + (_innerBoxWidth / 2), _innerBoxTop + (_innerBoxHeight / 2), color);
    }

    void drawIrlingBScreenAnalyzer(IDatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t radius, int16_t width)
    {
        //Draw Irling B.
        DDSIrlingBImage ddsIrlingBImage = DDSIrlingBImage(datapadTFTLCD);
        ddsIrlingBImage.drawImage(x - (ddsIrlingBImage.width() / 2), y - (ddsIrlingBImage.height() / 2));
        //Draw Fixed Screen Details.
        drawFixedScreenDetails(datapadTFTLCD, x, y, radius, width);
        drawIrlingBFixedScreenDetails(datapadTFTLCD, x, y, width);
        //Start Animation.
        _progressBar0->show();
        _progressBar1->show();
        _progressBar2->show();
        _progressBar3->show();
        _progressBar4->show();
        int16_t elapsed = 0;
        int16_t interval = 5000;
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

    void drawFixedScreenDetails(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius, int16_t width)
    {
        //Round Frame.
        datapadTFTLCD.drawInnerCircle(centerX, centerY, radius, GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawRoundFrame(centerX, centerY, radius, 90, true, GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR, DISPLAY_BACK_COLOR);
        int16_t recatangleLeft = centerX - 4;
        int16_t recatangleHeight = 8;
        datapadTFTLCD.fillRect(recatangleLeft, centerY - radius, recatangleHeight, 14, DISPLAY_BACK_COLOR);
        datapadTFTLCD.fillRect(recatangleLeft, centerY + radius + 1, recatangleHeight, -13, DISPLAY_BACK_COLOR);
        drawBothRoudedFrameDetails(datapadTFTLCD, centerX, centerY, width);
    }

    void drawBothRoudedFrameDetails(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t width)
    {
        int16_t roundedFrameDetailHeight = width * 0.39;
        int16_t roundedFrameDetailTop = centerY - roundedFrameDetailHeight;
        drawRoudedFrameDetail(datapadTFTLCD, centerX, roundedFrameDetailTop, width, false);
        roundedFrameDetailTop = centerY + roundedFrameDetailHeight;
        drawRoudedFrameDetail(datapadTFTLCD, centerX, roundedFrameDetailTop, width, true);
    }

    void drawIrlingBFixedScreenDetails(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t width)
    {
        int16_t lineWidth = _lineWidth;
        //Draw Red Dot.
        _ddsBlinkingDot = new DDSBlinkingDot(datapadTFTLCD, centerX - (width * 0.28), centerY - (width * 0.3), width * 0.017, LIFEFORM_ANALYZER_CREATURE_NAME_L0_COLOR, DISPLAY_BACK_COLOR);
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
        datapadTFTLCD.setTextColor(LIFEFORM_ANALYZER_CREATURE_NAME_L0_COLOR);
        datapadTFTLCD.setCursor(rightRectangleLeft + leftTextPadding, rightRectangleTop + topTextPadding);
        datapadTFTLCD.print(LIFEFORM_ANALYZER_TITLE_A_TEXT);
        datapadTFTLCD.setTextColor(TFT_WHITE);
        DDSTextPrinter *ddsTextPrinter = new DDSTextPrinter(datapadTFTLCD, rightRectangleLeft + leftTextPadding + 1, rightRectangleTop + topTextPadding + lineSeparation, rightRectanglewidth, rightRectangleHeight, textHeight, lineSeparation, DISPLAY_BACK_COLOR);
        ddsTextPrinter->print(lifeformAnalyzerParagraph1, sizeof(lifeformAnalyzerParagraph1) / sizeof(lifeformAnalyzerParagraph1[0]), true);
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
        datapadTFTLCD.setTextColor(LIFEFORM_ANALYZER_CREATURE_NAME_L0_COLOR);
        datapadTFTLCD.setCursor(leftRectangleLeft + leftTextPadding, leftRectangleTop + topTextPadding);
        datapadTFTLCD.print(LIFEFORM_ANALYZER_TITLE_B_TEXT);
        datapadTFTLCD.setTextColor(TFT_WHITE);
        ddsTextPrinter = new DDSTextPrinter(datapadTFTLCD, leftRectangleLeft + leftTextPadding + 1, leftRectangleTop + topTextPadding + lineSeparation, leftRectanglewidth, leftRectangleHeight, textHeight, lineSeparation, DISPLAY_BACK_COLOR);
        ddsTextPrinter->print(lifeformAnalyzerParagraph2, sizeof(lifeformAnalyzerParagraph2) / sizeof(lifeformAnalyzerParagraph2[0]), true);
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
        _progressBar0 = new DDSProgressBar(datapadTFTLCD, lineLeft, lineTop - progressBarHeight, lineWidth, progressBarHeight, LIFEFORM_ANALYZER_CREATURE_NAME_L0_COLOR, DISPLAY_BACK_COLOR, random(75, 95), 0.25);
        lineSeparation = (width * 0.009);
        lineLeft = lineLeft + lineWidth + lineSeparation;
        _progressBar1 = new DDSProgressBar(datapadTFTLCD, lineLeft, lineTop - progressBarHeight, lineWidth, progressBarHeight, LIFEFORM_ANALYZER_CREATURE_NAME_L0_COLOR, DISPLAY_BACK_COLOR, random(35, 55), 0.30);
        lineLeft = lineLeft + lineWidth + lineSeparation;
        _progressBar2 = new DDSProgressBar(datapadTFTLCD, lineLeft, lineTop - progressBarHeight, lineWidth, progressBarHeight, LIFEFORM_ANALYZER_CREATURE_NAME_L0_COLOR, DISPLAY_BACK_COLOR, random(55, 85), 0.40);
        lineLeft = lineLeft + lineWidth + (width * 0.012);
        _progressBar3 = new DDSProgressBar(datapadTFTLCD, lineLeft, lineTop - progressBarHeight, lineWidth, progressBarHeight, LIFEFORM_ANALYZER_CREATURE_NAME_L0_COLOR, DISPLAY_BACK_COLOR, random(25, 55), 0.25);
        lineLeft = lineLeft + lineWidth + (width * 0.015);
        _progressBar4 = new DDSProgressBar(datapadTFTLCD, lineLeft, lineTop - progressBarHeight, lineWidth, progressBarHeight, LIFEFORM_ANALYZER_CREATURE_NAME_L0_COLOR, DISPLAY_BACK_COLOR, random(45, 75), 0.40);
    }

    void drawRoudedFrameDetail(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t y, int16_t width, bool inverted)
    {
        int16_t halfLineWidth = _lineWidth / 2;
        int16_t mutiplier = 1;
        int16_t substractor = 1;
        if (inverted)
        {
            mutiplier = -1;
            substractor = 0;
        }
        int16_t lineOffset = _lineWidth * mutiplier;
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
        datapadTFTLCD.drawRectangle(rectangleLeft, rectangleTop, rectangleWidth, rectangleHeight, _lineWidth, DISPLAY_RING_COLOR);
        //Draw bigger base rectangle.
        int16_t segmentWidth = getWidth(width, 0.07);
        int16_t subSegmentWidth = getWidth(width, 0.02) * mutiplier;
        rectangleWidth = getWidth(width, 0.26);
        rectangleHeight = getWidth(width, 0.045) * mutiplier;
        rectangleTop = baseLineTop - rectangleHeight + lineOffset;
        rectangleLeft = centerX - (rectangleWidth / 2) - halfLineWidth;
        datapadTFTLCD.fillRect(rectangleLeft, rectangleTop, _lineWidth, rectangleHeight, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillRect(rectangleLeft, rectangleTop, segmentWidth, lineOffset, DISPLAY_RING_COLOR);
        if (!inverted)
        {
            datapadTFTLCD.drawLine(rectangleLeft + segmentWidth, rectangleTop, rectangleLeft + segmentWidth + subSegmentWidth, rectangleTop + subSegmentWidth, _lineWidth, DISPLAY_RING_COLOR);
        }
        else
        {
            datapadTFTLCD.drawLine(rectangleLeft + segmentWidth, rectangleTop + lineOffset, rectangleLeft + segmentWidth - subSegmentWidth, rectangleTop + subSegmentWidth + lineOffset, _lineWidth, DISPLAY_RING_COLOR);
        }
        rectangleLeft = rectangleLeft + rectangleWidth - halfLineWidth;
        datapadTFTLCD.fillRect(rectangleLeft, rectangleTop, _lineWidth, rectangleHeight, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillRect(rectangleLeft - segmentWidth + _lineWidth, rectangleTop, segmentWidth, lineOffset, DISPLAY_RING_COLOR);
        if (!inverted)
        {
            datapadTFTLCD.drawLine(rectangleLeft - segmentWidth, rectangleTop, rectangleLeft - segmentWidth - subSegmentWidth, rectangleTop + subSegmentWidth, _lineWidth, DISPLAY_RING_COLOR);
        }
        else
        {
            datapadTFTLCD.drawLine(rectangleLeft + subSegmentWidth - segmentWidth, rectangleTop + subSegmentWidth + lineOffset, rectangleLeft - segmentWidth, rectangleTop + lineOffset, _lineWidth, DISPLAY_RING_COLOR);
        }
        //Draw little external line.
        rectangleWidth = getWidth(width, 0.32);
        rectangleHeight = getWidth(width, 0.03) * mutiplier;
        rectangleTop = baseLineTop - rectangleHeight + lineOffset;
        rectangleLeft = centerX - (rectangleWidth / 2) - halfLineWidth;
        datapadTFTLCD.fillRect(rectangleLeft, rectangleTop, _lineWidth, rectangleHeight, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillRect(rectangleLeft + rectangleWidth - halfLineWidth, rectangleTop, _lineWidth, rectangleHeight, DISPLAY_RING_COLOR);
        //Draw bigger external line.
        rectangleWidth = getWidth(width, 0.36);
        rectangleHeight = getWidth(width, 0.0175) * mutiplier;
        rectangleTop = baseLineTop - rectangleHeight + lineOffset;
        rectangleLeft = centerX - (rectangleWidth / 2) - halfLineWidth;
        datapadTFTLCD.fillRect(rectangleLeft, rectangleTop, _lineWidth, rectangleHeight, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillRect(rectangleLeft + rectangleWidth - halfLineWidth, rectangleTop, _lineWidth, rectangleHeight, DISPLAY_RING_COLOR);
    }

    int16_t getWidth(int16_t reference, float percentage)
    {
        int16_t result = reference * percentage;
        if (result % 2 != 0)
            result--;
        return result;
    }

    void nonBlockingDelay(int16_t interval)
    {
        int16_t elapsed = 0;
        unsigned long previousMillis = millis();
        do
        {
            elapsed += millis() - previousMillis;
            previousMillis = millis();
        } while (elapsed < interval);
    }
};

LifeformAnalyzerDDS::LifeformAnalyzerDDS(IDatapadTFTLCD &datapadTFTLCD) : DatapadDisplaySequence(datapadTFTLCD) {}

void LifeformAnalyzerDDS::show()
{
    CreatureAnalyzerDDSHelper creatureAnalyzerDDSHelper;
    creatureAnalyzerDDSHelper.drawCreatureAnalyzer(_datapadTFTLCD);
}