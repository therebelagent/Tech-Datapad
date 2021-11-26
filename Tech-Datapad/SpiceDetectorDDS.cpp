//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "SpiceDetectorDDS.h"
#include "DDSTextPrinter.h"
#include "DDSProgressBar.h"
#include "Fonts/Aurebesh2pt7b.h"
#include "Fonts/Aurebesh6pt7b.h"

class SpiceDetectorDDSHelper
{
public:
    void drawSpiceDetectorDDS(IDatapadTFTLCD &datapadTFTLCD)
    {
        int16_t width = datapadTFTLCD.width();
        int16_t centerX = width / 2;
        int16_t centerY = datapadTFTLCD.height() / 2;
        int16_t radius = centerX - 1;
        drawFixedScreenDetails(datapadTFTLCD, centerX, centerY, radius, width);
        RunProgressBarAnimations();
    }

    void drawFixedScreenDetails(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius, int16_t width)
    {
        //Draw Inner Arcs.
        int16_t innerRadius = radius * 0.95;
        int16_t thickInnerCircleWidth = width * 0.042;
        int16_t thinInnerCirclesWidth = width * 0.03;
        int16_t detailInnerCirclesWidth = thickInnerCircleWidth - thinInnerCirclesWidth;
        int16_t detailInnerRadius = innerRadius - thinInnerCirclesWidth;
        //Top Arc.
        datapadTFTLCD.fillArc(centerX, centerY, 321, 26, innerRadius, innerRadius, thinInnerCirclesWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 321, 5, detailInnerRadius, detailInnerRadius, detailInnerCirclesWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 24, 5, detailInnerRadius, detailInnerRadius, detailInnerCirclesWidth, DISPLAY_RING_COLOR);
        //Right Arc.
        datapadTFTLCD.fillArc(centerX, centerY, 40, 36, innerRadius, innerRadius, thinInnerCirclesWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 40, 2, detailInnerRadius, detailInnerRadius, detailInnerCirclesWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 55, 2, detailInnerRadius, detailInnerRadius, detailInnerCirclesWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 102, 1, detailInnerRadius, detailInnerRadius, detailInnerCirclesWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 107, 1, detailInnerRadius, detailInnerRadius, detailInnerCirclesWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 130, 6, detailInnerRadius, detailInnerRadius, detailInnerCirclesWidth, DISPLAY_RING_COLOR);
        //Bottom Arc.
        datapadTFTLCD.fillArc(centerX, centerY, 150, 20, innerRadius, innerRadius, thickInnerCircleWidth, DISPLAY_RING_COLOR);
        //Left Arc.
        datapadTFTLCD.fillArc(centerX, centerY, 212, 36, innerRadius, innerRadius, thinInnerCirclesWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 212, 6, detailInnerRadius, detailInnerRadius, detailInnerCirclesWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 250, 1, detailInnerRadius, detailInnerRadius, detailInnerCirclesWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 255, 1, detailInnerRadius, detailInnerRadius, detailInnerCirclesWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 299, 2, detailInnerRadius, detailInnerRadius, detailInnerCirclesWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 314, 2, detailInnerRadius, detailInnerRadius, detailInnerCirclesWidth, DISPLAY_RING_COLOR);
        //Draw Top Banner.
        int16_t bannerTop = centerY - (width * 0.245);
        int16_t bannerWidth = width * 0.54;
        int16_t bannerHeight = width * 0.09;
        datapadTFTLCD.drawBanner(centerX, bannerTop, bannerHeight, bannerWidth, TFT_DARKCYAN, SPICE_DETECTOR_BANNER_TEXT, &Aurebesh6pt7b);
        //Draw Rectangle.
        int16_t rectangleWidth = width * 0.66;
        int16_t rectangleHeight = width * 0.36;
        int16_t rectangleLeft = centerX - (rectangleWidth / 2) + 1;
        int16_t rectangleTop = centerY - (width * 0.11);
        datapadTFTLCD.drawRectangle(rectangleLeft, rectangleTop, rectangleWidth, rectangleHeight, 2, DISPLAY_RING_COLOR);
        int16_t rectangleLineLeft = rectangleLeft + rectangleWidth - (width * 0.38);
        datapadTFTLCD.drawFastVerticalLine(rectangleLineLeft, rectangleTop, rectangleHeight, 2, DISPLAY_RING_COLOR);
        //Draw Paragraph Sentences.
        datapadTFTLCD.setFont(&Aurebesh2pt7b);
        datapadTFTLCD.setTextColor(TFT_WHITE);
        int16_t lineVerticalGap = 1;
        int16_t lineHeight = 3;
        int16_t windowsScrollLeft = rectangleLeft + 2;
        int16_t windowScrollWidth = rectangleLineLeft - rectangleLeft - 4;
        int16_t windowScrollTop = rectangleTop + 2;
        int16_t windowScrollHeight = rectangleHeight - 4;
        DDSTextPrinter ddsTextPrinter = DDSTextPrinter(datapadTFTLCD, windowsScrollLeft, windowScrollTop, windowScrollWidth, windowScrollHeight, lineHeight, lineVerticalGap, DISPLAY_BACK_COLOR);
        ddsTextPrinter.print(spiceDetectorParagraph, sizeof(spiceDetectorParagraph) / sizeof(spiceDetectorParagraph[0]), true);
        //Draw Progress Bars.
        int16_t progressBarHeight = width * 0.33;
        int16_t progressBarWidth = width * 0.08;
        int16_t progressBarSeparation = width * 0.013;
        int16_t progressBarLeft = rectangleLineLeft + progressBarSeparation;
        int16_t progressBarTop = rectangleTop + rectangleHeight - progressBarHeight - 4;
        randomSeed(millis());
        _progressBar0 = new DDSProgressBar(datapadTFTLCD, progressBarLeft, progressBarTop, progressBarWidth, progressBarHeight, PROGRESS_BAR_COLOR, DISPLAY_BACK_COLOR, random(80, 100), random(1, 2));
        progressBarLeft = +progressBarLeft + progressBarWidth + progressBarSeparation;
        _progressBar1 = new DDSProgressBar(datapadTFTLCD, progressBarLeft, progressBarTop, progressBarWidth, progressBarHeight, PROGRESS_BAR_COLOR, DISPLAY_BACK_COLOR, random(35, 55), random(1, 3));
        progressBarLeft = +progressBarLeft + progressBarWidth + progressBarSeparation;
        _progressBar2 = new DDSProgressBar(datapadTFTLCD, progressBarLeft, progressBarTop, progressBarWidth, progressBarHeight, PROGRESS_BAR_COLOR, DISPLAY_BACK_COLOR, random(55, 75), random(1, 2));
        progressBarLeft = +progressBarLeft + progressBarWidth + progressBarSeparation;
        _progressBar3 = new DDSProgressBar(datapadTFTLCD, progressBarLeft, progressBarTop, progressBarWidth, progressBarHeight, TFT_WHITE, DISPLAY_BACK_COLOR, random(15, 35), random(1, 3));
        //Draw Rectangle Solid Background.
        datapadTFTLCD.fillRect(rectangleLineLeft + 2, rectangleTop + 2, (rectangleWidth - windowScrollWidth) - 9, rectangleHeight - 4, DISPLAY_BACK_COLOR);
    }

    void RunProgressBarAnimations()
    {
        _progressBar0->show();
        _progressBar1->show();
        _progressBar2->show();
        _progressBar3->show();
        //Run Progress Bars Animations.
        int16_t elapsed = 0;
        int16_t interval = 5000;
        unsigned long previousMillis = millis();
        do
        {
            _progressBar0->update();
            _progressBar1->update();
            _progressBar2->update();
            _progressBar3->update();
            elapsed += millis() - previousMillis;
            previousMillis = millis();
        } while (elapsed < interval);
        delete _progressBar0;
        delete _progressBar1;
        delete _progressBar2;
        delete _progressBar3;
    }

private:
    DDSProgressBar *_progressBar0, *_progressBar1, *_progressBar2, *_progressBar3;
};

SpiceDetectorDDS::SpiceDetectorDDS(IDatapadTFTLCD &datapadTFTLCD) : BasicGridDDS(datapadTFTLCD) {}

void SpiceDetectorDDS::show()
{
    BasicGridDDS::show();
    SpiceDetectorDDSHelper spiceDetectorDDSHelper;
    spiceDetectorDDSHelper.drawSpiceDetectorDDS(_datapadTFTLCD);
}