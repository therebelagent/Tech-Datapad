//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DoorLockHackingDDS.h"
#include "DDSTextPrinter.h"
#include "Fonts/Aurebesh15pt7b.h"

class DoorLockHackingDDSHelper
{
public:
    void drawDoorLockHacking(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer)
    {
        int16_t width = datapadTFTLCD.width();
        int16_t centerX = width / 2;
        int16_t centerY = datapadTFTLCD.height() / 2;
        drawFixedScreenDetails(datapadTFTLCD, centerX, centerY, width);
        //Draw Window Scroll Up Animation.
        datapadTFTLCD.setFont(&Aurebesh15pt7b);
        datapadTFTLCD.setTextColor(DISPLAY_RING_COLOR);
        int16_t lineVerticalGap = 10;
        int16_t lineHeight = 20;
        int16_t offset = lineHeight;
        int16_t screenTop = width - centerY - offset;
        int16_t screnHeight = width + (offset * 2);
        int16_t steps = 3;
        DDSTextPrinter ddsTextPrinter = DDSTextPrinter(datapadTFTLCD, _screenFrameLeft, screenTop, _screenFrameWidth, screnHeight, lineHeight, lineVerticalGap, DISPLAY_BACK_COLOR);
        ddsTextPrinter.scrollUp(doorLockHackingParagraph1, sizeof(doorLockHackingParagraph1) / sizeof(doorLockHackingParagraph1[0]), steps);
        playBeeps(datapadSoundPlayer);
    }

private:
    int16_t _screenFrameWidth, _screenFrameLeft;

    void drawFixedScreenDetails(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t width)
    {
        //Right Fixed Details.
        //Trapezoid.
        int16_t trapezoidLeft = centerX + (width * 0.27);
        int16_t trapezoidHeight = width * 0.75;
        int16_t trapezoidTop = centerY - (trapezoidHeight / 2);
        int16_t trapezoidWidth = width * 0.13;
        int16_t trapezoidLineWidth = width * 0.015;
        int16_t trapezoidHTopWidth = width * 0.55;
        datapadTFTLCD.drawVerticalTrapezoid(trapezoidLeft, trapezoidTop, trapezoidHeight, trapezoidHTopWidth, trapezoidWidth, trapezoidLineWidth, DISPLAY_FIXED_DETAILS_COLOR);
        //Inner Trapezoid Rectangle.
        int16_t innerRectangleWidth = width * 0.03;
        int16_t innerRectangleLeft = centerX + (width * 0.32);
        int16_t innerRectangleHeight = width * 0.43;
        int16_t innerRectangleTop = trapezoidTop + (trapezoidHeight / 2) - (innerRectangleHeight / 2);
        datapadTFTLCD.drawRectangle(innerRectangleLeft, innerRectangleTop, innerRectangleWidth, innerRectangleHeight, 2, DISPLAY_RING_COLOR);
        //Small Trapezoid & Small Rectangle.
        int16_t smallTrapezoidLeft = centerX + (width * 0.43);
        int16_t smallTrapezoidHeight = width * 0.13;
        int16_t smallTrapezoidTop = trapezoidTop + (trapezoidHeight / 2) - (smallTrapezoidHeight / 2);
        int16_t smallTrapezoidWidth = width * 0.06;
        int16_t smallTrapezoidTopWidth = width * 0.05;
        int16_t rectangleLeft = centerX + (width * 0.36);
        int16_t rectangleHeight = width * 0.31;
        int16_t rectangleTop = trapezoidTop + (trapezoidHeight / 2) - (rectangleHeight / 2);
        int16_t rectangleWidth = width * 0.09;
        datapadTFTLCD.drawRectangle(rectangleLeft, rectangleTop, rectangleWidth, rectangleHeight, trapezoidLineWidth, DISPLAY_FIXED_DETAILS_COLOR);
        datapadTFTLCD.drawVerticalTrapezoid(smallTrapezoidLeft - (trapezoidLineWidth * 1.5), smallTrapezoidTop - 2, smallTrapezoidHeight + 4, smallTrapezoidTopWidth + 2, smallTrapezoidWidth, trapezoidLineWidth, DISPLAY_FIXED_DETAILS_COLOR, true);
        datapadTFTLCD.drawVerticalTrapezoid((smallTrapezoidLeft - (trapezoidLineWidth * 1.5)) + trapezoidLineWidth, smallTrapezoidTop - 2, smallTrapezoidHeight + 4, smallTrapezoidTopWidth + 2, smallTrapezoidWidth, trapezoidLineWidth, DISPLAY_BACK_COLOR, true);
        datapadTFTLCD.fillRect(smallTrapezoidLeft + trapezoidLineWidth, smallTrapezoidTop - 2, smallTrapezoidWidth, smallTrapezoidHeight + 4, DISPLAY_BACK_COLOR);
        datapadTFTLCD.drawFastVerticalLine(rectangleLeft + rectangleWidth - trapezoidLineWidth, (rectangleTop + (rectangleHeight / 2)) - ((smallTrapezoidTopWidth + 8) / 2), smallTrapezoidTopWidth + 8, trapezoidLineWidth, DISPLAY_BACK_COLOR);
        datapadTFTLCD.drawVerticalTrapezoid(smallTrapezoidLeft, smallTrapezoidTop, smallTrapezoidHeight, smallTrapezoidTopWidth, smallTrapezoidWidth, trapezoidLineWidth, DISPLAY_RING_COLOR, true);
        //Left Fixed Details.
        //Trapezoid.
        int16_t thinTrapezoidWidth = width * 0.08;
        int16_t thinTrapezoidLeft = trapezoidLeft - (width * 0.65);
        int16_t thinTrapezoidHeight = width * 0.67;
        int16_t thinTrapezoidTop = centerY - (thinTrapezoidHeight / 2);
        int16_t thinTrapezoidTopWidth = width * 0.55;
        datapadTFTLCD.drawVerticalTrapezoid(thinTrapezoidLeft, thinTrapezoidTop, thinTrapezoidHeight, thinTrapezoidTopWidth, thinTrapezoidWidth, trapezoidLineWidth, DISPLAY_FIXED_DETAILS_COLOR, true);
        datapadTFTLCD.drawRectangle(thinTrapezoidLeft + (thinTrapezoidWidth / 2) + 1, thinTrapezoidTop, thinTrapezoidWidth / 2, 8, trapezoidLineWidth, DISPLAY_FIXED_DETAILS_COLOR);
        datapadTFTLCD.fillRect((thinTrapezoidLeft + (thinTrapezoidWidth / 2) + 3), thinTrapezoidTop + trapezoidLineWidth, 4, 8, DISPLAY_BACK_COLOR);
        //Small Rectangle.
        rectangleLeft = thinTrapezoidLeft - (width * 0.05);
        datapadTFTLCD.drawRectangle(rectangleLeft, rectangleTop, rectangleWidth, rectangleHeight, trapezoidLineWidth, DISPLAY_FIXED_DETAILS_COLOR);
        smallTrapezoidLeft = rectangleLeft - trapezoidLineWidth - 2;
        datapadTFTLCD.drawVerticalTrapezoid(smallTrapezoidLeft, smallTrapezoidTop - 2, smallTrapezoidHeight + 4, smallTrapezoidTopWidth + 2, smallTrapezoidWidth, trapezoidLineWidth, DISPLAY_FIXED_DETAILS_COLOR);
        datapadTFTLCD.drawVerticalTrapezoid(smallTrapezoidLeft - trapezoidLineWidth, smallTrapezoidTop - 2, smallTrapezoidHeight + 4, smallTrapezoidTopWidth + 2, smallTrapezoidWidth, trapezoidLineWidth, DISPLAY_BACK_COLOR);
        datapadTFTLCD.fillRect(rectangleLeft - smallTrapezoidWidth - 2, smallTrapezoidTop - 2, smallTrapezoidWidth, smallTrapezoidHeight + 4, DISPLAY_BACK_COLOR);
        datapadTFTLCD.drawFastVerticalLine(rectangleLeft, (rectangleTop + (rectangleHeight / 2)) - ((smallTrapezoidTopWidth + 13) / 2), smallTrapezoidTopWidth + 13, trapezoidLineWidth, DISPLAY_BACK_COLOR);
        //Red Dot.
        int16_t redDotRadius = width * 0.035;
        int16_t redDotLeft = rectangleLeft - (width * 0.02);
        datapadTFTLCD.fillCircle(redDotLeft, rectangleTop + (rectangleHeight / 2), redDotRadius, TFT_RED);
        //Screen Frame.
        _screenFrameWidth = (width * 0.35) + 1;
        _screenFrameLeft = ((thinTrapezoidWidth + thinTrapezoidLeft + (((width - (thinTrapezoidWidth + thinTrapezoidLeft)) - (width - trapezoidLeft)) / 2)) - (_screenFrameWidth / 2)) - 1;
    }

    void playBeeps(IDatapadSoundPlayer &datapadSoundPlayer)
    {
        DatapadTone datapadTone;
        datapadTone.frequency = 5000;
        datapadTone.duration = 30;
        for (size_t counter = 0; counter < 10; counter++)
        {
            datapadSoundPlayer.playTone(datapadTone);
            delay(40);
        }
    }
};

DoorLockHackingDDS::DoorLockHackingDDS(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer) : DatapadDisplaySequence(datapadTFTLCD, datapadSoundPlayer) {}

void DoorLockHackingDDS::show()
{
    DoorLockHackingDDSHelper doorLockHackingDDSHelper = DoorLockHackingDDSHelper();
    doorLockHackingDDSHelper.drawDoorLockHacking(_datapadTFTLCD, _datapadSoundPlayer);
}