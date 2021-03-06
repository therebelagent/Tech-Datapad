//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "RearAxleStabilizerCalibrationDDS.h"
#include "Fonts/Aurebesh6pt7b.h"
#include "Fonts/Aurebesh10pt7b.h"

class RearAxleStabilizerCalibrationProgressBar
{
public:
    RearAxleStabilizerCalibrationProgressBar(IDatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t width, int16_t height) : _datapadTFTLCD(datapadTFTLCD)
    {
        _x = x;
        _nextSegmentTop = y;
        _width = width;
        _nextSegmentTop = _nextSegmentTop + height - 1;
        _smallSegmentHeight = height * 0.07;
        _regularSegmentHeight = height * 0.105;
        _bigSegmentHeight = height * 0.15;
        _currentSegment = 1;
    }

    bool showNext()
    {
        bool result = false;
        if (_currentSegment <= REAR_AXLE_STABILIZER_CALIBRATION_PROGRESS_BAR_SEGMENTS)
        {
            createSegment(_currentSegment);
            _currentSegment++;
            result = true;
        }
        return result;
    }

private:
    IDatapadTFTLCD &_datapadTFTLCD;
    int16_t _x, _width;
    int16_t _smallSegmentHeight, _regularSegmentHeight, _bigSegmentHeight;
    int16_t _nextSegmentTop, _currentSegment;

    void createSegment(int16_t segment)
    {
        int16_t colour;
        int16_t segmentHeight;
        if (segment == 1)
        {
            segmentHeight = _smallSegmentHeight;
            colour = REAR_AXLE_STABILIZER_CALIBRATION_PROGRESS_BAR_SMALL_SEGMENT_COLOR;
        }
        else if (segment == 2)
        {
            segmentHeight = _regularSegmentHeight;
            colour = REAR_AXLE_STABILIZER_CALIBRATION_PROGRESS_BAR_REGULAR_SEGMENT_COLOR;
        }
        else if (segment > 2 && segment < 9)
        {
            segmentHeight = _regularSegmentHeight;
            colour = TFT_YELLOW;
        }
        else if (segment == 9)
        {
            segmentHeight = _bigSegmentHeight;
            colour = CANNON_POWERED_UP_COLOR;
        }
        for (int16_t counter = 1; counter <= segmentHeight; counter++)
        {
            delay(1);
            _datapadTFTLCD.drawFastHLine(_x, _nextSegmentTop - counter, _width, colour);
        }
        _nextSegmentTop = _nextSegmentTop - segmentHeight - 1;
    }
};

class RearAxleStabilizerCalibrationDDSHelper
{
public:
    void drawRearAxleStabilizerCalibration(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer)
    {
        int16_t width = datapadTFTLCD.width();
        int16_t centerX = width / 2;
        int16_t centerY = datapadTFTLCD.height() / 2;
        int16_t radius = centerX - 1;
        drawFixedScreenDetails(datapadTFTLCD, centerX, centerY, radius, width);
        delay(1500);
        drawProgressBarAnimation(datapadTFTLCD, width);
        delay(5);
        drawSwappedDots(datapadTFTLCD);
        delay(5);
        drawRepairingBanner(datapadTFTLCD, centerX);
        delay(5);
        drawGreenDots(datapadTFTLCD);
        delay(5);
        drawCompleteBanner(datapadTFTLCD, centerX);
        playBeeps(datapadSoundPlayer);
    }

private:
    int16_t _whiteBoxWidth, _whiteBoxTop, _whiteBoxHeight;
    int16_t _dotX, _redDotY, _whiteDotY, _dotRadius;
    int16_t _whiteULeft, _whiteUTop;

    void drawFixedScreenDetails(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius, int16_t width)
    { //Round Frame.
        datapadTFTLCD.drawRoundFrame(centerX, centerY, radius, 0, true, GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR, DISPLAY_BACK_COLOR);
        datapadTFTLCD.drawFastHorizontalLine(0, centerY, width, 8, DISPLAY_BACK_COLOR);
        //Blue Bottom Details.
        int16_t blueDetailWidth = width * 0.41;
        int16_t blueDetailLeft = centerX - blueDetailWidth / 2;
        int16_t blueDetailTop = (centerY + radius) - (radius * 2) * 0.16;
        datapadTFTLCD.drawFastHorizontalLine(blueDetailLeft, blueDetailTop, blueDetailWidth, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(centerX, blueDetailTop, 5, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(centerX + 8, blueDetailTop, 8, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(centerX + 34, blueDetailTop, 30, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(centerX + 44, blueDetailTop, 10, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(centerX + 56, blueDetailTop, 7, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(centerX - 8, blueDetailTop, 4, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(centerX - 16, blueDetailTop, 26, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(centerX - 27, blueDetailTop, 22, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(centerX - 34, blueDetailTop, 30, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(centerX - 44, blueDetailTop, 10, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(centerX - 50, blueDetailTop, 4, 3, DISPLAY_RING_COLOR);
        //White Box.
        _whiteBoxWidth = width * 0.57;
        int16_t whiteBoxLeft = (centerX - _whiteBoxWidth / 2);
        _whiteBoxHeight = width * 0.075;
        _whiteBoxTop = blueDetailTop - _whiteBoxHeight - 5;
        datapadTFTLCD.drawRectangle(whiteBoxLeft, _whiteBoxTop, _whiteBoxWidth, _whiteBoxHeight, 2, TFT_WHITE);
        //Blue Right Details.
        int16_t blueBaseLineWidth = width * 0.69;
        int16_t blueBaseLineLeft = centerX - blueBaseLineWidth / 2;
        int16_t blueBaseLinetop = _whiteBoxTop - _whiteBoxHeight / 2;
        int16_t blueBaseLineHorizontalOffset = 5;
        datapadTFTLCD.drawFastHorizontalLine(blueBaseLineLeft, blueBaseLinetop, blueBaseLineWidth, 2, DISPLAY_RING_COLOR);
        int16_t blueVerticalLineLeft = blueBaseLineLeft + blueBaseLineWidth - width * 0.27 - blueBaseLineHorizontalOffset;
        datapadTFTLCD.drawFastVerticalLine(blueVerticalLineLeft, blueBaseLinetop, (width * 0.52) * -1, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastHorizontalLine(blueVerticalLineLeft + (width * 0.08), blueBaseLinetop - (width * 0.26), (width * 0.09), 4, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastHorizontalLine(blueVerticalLineLeft, blueBaseLinetop - (width * 0.45), (width * 0.21), 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawLine(blueVerticalLineLeft, blueBaseLinetop - (width * 0.52), blueVerticalLineLeft + (width * 0.036), blueBaseLinetop - (width * 0.52) - 12, 3, DISPLAY_RING_COLOR);
        blueVerticalLineLeft = blueVerticalLineLeft + (width * 0.04);
        datapadTFTLCD.drawFastVerticalLine(blueVerticalLineLeft, blueBaseLinetop, (width * 0.61) * -1, 3, DISPLAY_RING_COLOR);
        blueVerticalLineLeft = blueBaseLineLeft + blueBaseLineWidth - blueBaseLineHorizontalOffset;
        datapadTFTLCD.drawFastVerticalLine(blueVerticalLineLeft, blueBaseLinetop, (width * 0.39) * -1, 3, DISPLAY_RING_COLOR);
        //Small Inner Grid.
        int16_t smallGridHeight = (width * 0.14);
        int16_t smallGridLineHeight = (smallGridHeight / 5) + 1;
        int16_t smallGridWidth = (width * 0.23) * -1;
        int16_t smallGridLineWidth = smallGridWidth / 7;
        for (int16_t counter = 1; counter <= 5; counter++)
        {
            datapadTFTLCD.drawFastHLine(blueVerticalLineLeft, blueBaseLinetop - smallGridLineHeight * counter, smallGridWidth, DISPLAY_RING_COLOR);
        }
        for (int16_t counter = 1; counter <= 7; counter++)
        {
            datapadTFTLCD.drawFastVLine(blueVerticalLineLeft + smallGridLineWidth * counter, blueBaseLinetop, smallGridHeight * -1, DISPLAY_RING_COLOR);
        }
        datapadTFTLCD.drawFastHorizontalLine(blueVerticalLineLeft, blueBaseLinetop - smallGridHeight, smallGridWidth, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawLine(blueVerticalLineLeft - 1, blueBaseLinetop - (width * 0.39), blueVerticalLineLeft - (width * 0.06), blueBaseLinetop - (width * 0.45), 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(blueVerticalLineLeft - (width * 0.044), blueBaseLinetop - smallGridLineHeight * 2, (width * 0.26) * -1, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(blueVerticalLineLeft - (width * 0.07), blueBaseLinetop - smallGridLineHeight * 4, (width * 0.056) * -1, 3, DISPLAY_RING_COLOR);
        //Small White Details.
        int16_t whiteHorizontalLineLeft = centerX + (width * 0.11);
        int16_t whiteHorizontalLineTop = blueBaseLinetop - (smallGridLineHeight / 2) - 2;
        datapadTFTLCD.drawFastHorizontalLine(whiteHorizontalLineLeft, whiteHorizontalLineTop, (width * 0.21), 2, TFT_WHITE);
        int16_t whiteVerticalLineWidth = width * 0.02;
        whiteHorizontalLineLeft = whiteHorizontalLineLeft + 7;
        datapadTFTLCD.drawFastVerticalLine(whiteHorizontalLineLeft, whiteHorizontalLineTop, (width * 0.076) * -1, whiteVerticalLineWidth, TFT_WHITE);
        whiteHorizontalLineLeft = whiteHorizontalLineLeft + (width * 0.04);
        datapadTFTLCD.drawFastVerticalLine(whiteHorizontalLineLeft, whiteHorizontalLineTop, (width * 0.044) * -1, whiteVerticalLineWidth, TFT_WHITE);
        whiteHorizontalLineLeft = whiteHorizontalLineLeft + (width * 0.04);
        datapadTFTLCD.drawFastVerticalLine(whiteHorizontalLineLeft, whiteHorizontalLineTop, (width * 0.023) * -1, whiteVerticalLineWidth, TFT_WHITE);
        //Vertical White Box Details.
        whiteHorizontalLineLeft = centerX + (width * 0.13);
        int16_t whiteBoxHeightTop = whiteHorizontalLineTop - (width * 0.40);
        datapadTFTLCD.drawRectangle(whiteHorizontalLineLeft + 2, whiteBoxHeightTop, (width * 0.039), (width * 0.25), 2, TFT_WHITE);
        whiteHorizontalLineLeft = whiteHorizontalLineLeft + (width * 0.039);
        whiteBoxHeightTop = whiteBoxHeightTop + 5;
        datapadTFTLCD.drawFastHorizontalLine(whiteHorizontalLineLeft, whiteBoxHeightTop, (width * 0.033), 2, TFT_WHITE);
        whiteBoxHeightTop = whiteBoxHeightTop + 6;
        datapadTFTLCD.drawFastHorizontalLine(whiteHorizontalLineLeft, whiteBoxHeightTop, (width * 0.095), 2, TFT_WHITE);
        whiteBoxHeightTop = whiteBoxHeightTop + 8;
        datapadTFTLCD.drawFastHorizontalLine(whiteHorizontalLineLeft, whiteBoxHeightTop, (width * 0.033), 2, TFT_WHITE);
        whiteBoxHeightTop = whiteBoxHeightTop + 9;
        datapadTFTLCD.drawFastHorizontalLine(whiteHorizontalLineLeft, whiteBoxHeightTop, (width * 0.013), 2, TFT_WHITE);
        //Vertical White Line.
        datapadTFTLCD.drawFastVerticalLine(centerX + (width * 0.35), whiteHorizontalLineTop, (width * 0.35) * -1, 3, TFT_WHITE);
        //White U Details.
        int16_t whiteULeft = centerX + (width * 0.01);
        _whiteUTop = blueBaseLinetop - (width * 0.026);
        int16_t whiteUWidth = (width * 0.32);
        datapadTFTLCD.drawFastVerticalLine(whiteULeft, _whiteUTop, (width * 0.23) * -1, 3, TFT_WHITE);
        _whiteULeft = whiteULeft - whiteUWidth + 3;
        datapadTFTLCD.drawFastVerticalLine(_whiteULeft, _whiteUTop, (width * 0.23) * -1, 3, TFT_WHITE);
        datapadTFTLCD.drawFastHorizontalLine(whiteULeft - whiteUWidth + 2, _whiteUTop, whiteUWidth, 3, TFT_WHITE);
        whiteULeft = blueBaseLineLeft + 4;
        int16_t whiteUHeight = blueBaseLinetop - (width * 0.14) - 1;
        datapadTFTLCD.drawFastVerticalLine(whiteULeft, blueBaseLinetop - 1, (width * 0.14) * -1, 4, TFT_WHITE);
        datapadTFTLCD.drawLine(whiteULeft - 1, whiteUHeight, whiteULeft + (width * 0.03), whiteUHeight - (width * 0.046), 3, TFT_WHITE);
        //Dots.
        _dotX = centerX + (width * 0.13) + (width * 0.039) / 2;
        _redDotY = whiteHorizontalLineTop - (width * 0.49);
        _whiteDotY = _redDotY - (width * 0.033);
        _dotRadius = (width * 0.031) / 2;
        datapadTFTLCD.fillCircle(_dotX, _redDotY, _dotRadius, TFT_RED);
        datapadTFTLCD.fillCircle(_dotX, _whiteDotY, _dotRadius, TFT_WHITE);
    }

    void drawProgressBarAnimation(IDatapadTFTLCD &datapadTFTLCD, int16_t width)
    {
        int16_t progressBarLeft = _whiteULeft + 2;
        int16_t progressBarWidth = width * 0.093;
        int16_t progressBarHeight = width * 0.44;
        int16_t progressBarTop = _whiteUTop - progressBarHeight;
        RearAxleStabilizerCalibrationProgressBar aRearAxleStabilizerCalibrationProgressBar = RearAxleStabilizerCalibrationProgressBar(datapadTFTLCD, progressBarLeft, progressBarTop, progressBarWidth, progressBarHeight);
        progressBarLeft = progressBarLeft + progressBarWidth + width * 0.013 + 1;
        RearAxleStabilizerCalibrationProgressBar bRearAxleStabilizerCalibrationProgressBar = RearAxleStabilizerCalibrationProgressBar(datapadTFTLCD, progressBarLeft, progressBarTop, progressBarWidth, progressBarHeight);
        progressBarLeft = progressBarLeft + progressBarWidth + width * 0.01 + 1;
        RearAxleStabilizerCalibrationProgressBar cRearAxleStabilizerCalibrationProgressBar = RearAxleStabilizerCalibrationProgressBar(datapadTFTLCD, progressBarLeft, progressBarTop, progressBarWidth, progressBarHeight);

        while (aRearAxleStabilizerCalibrationProgressBar.showNext())
        {
            delay(15);
            bRearAxleStabilizerCalibrationProgressBar.showNext();
            delay(15);
            cRearAxleStabilizerCalibrationProgressBar.showNext();
            delay(15);
        }
    }

    void drawSwappedDots(IDatapadTFTLCD &datapadTFTLCD)
    {
        datapadTFTLCD.fillCircle(_dotX, _redDotY, _dotRadius, TFT_WHITE);
        datapadTFTLCD.fillCircle(_dotX, _whiteDotY, _dotRadius, TFT_RED);
    }

    void drawGreenDots(IDatapadTFTLCD &datapadTFTLCD)
    {
        datapadTFTLCD.fillCircle(_dotX, _redDotY, _dotRadius, CANNON_POWERED_UP_COLOR);
        datapadTFTLCD.fillCircle(_dotX, _whiteDotY, _dotRadius, CANNON_POWERED_UP_COLOR);
    }

    void drawRepairingBanner(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX)
    {
        int16_t textLeft = centerX - _whiteBoxWidth / 5;
        datapadTFTLCD.printCenteredText(REAR_AXLE_STABILIZER_CALIBRATION_REPAIRING, &Aurebesh6pt7b, textLeft, (_whiteBoxTop + _whiteBoxHeight / 2) - 1, TFT_RED);
        delay(500);
        datapadTFTLCD.printCenteredText(REAR_AXLE_STABILIZER_CALIBRATION_REPAIRING, &Aurebesh6pt7b, textLeft, (_whiteBoxTop + _whiteBoxHeight / 2) - 1, DISPLAY_BACK_COLOR);
    }

    void drawCompleteBanner(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX)
    {
        datapadTFTLCD.printCenteredText(REAR_AXLE_STABILIZER_CALIBRATION_COMPLETE, &Aurebesh10pt7b, centerX, (_whiteBoxTop + _whiteBoxHeight / 2) - 1, CANNON_POWERED_UP_COLOR);
    }

    void playBeeps(IDatapadSoundPlayer &datapadSoundPlayer)
    {
        DatapadTone datapadTone;
        datapadTone.frequency = 1000;
        datapadTone.duration = 75;
        datapadSoundPlayer.playTone(datapadTone);
        delay(500);
        datapadTone.frequency = 3000;
        datapadTone.duration = 10;
        for (size_t counter = 0; counter < 10; counter++)
        {
            datapadSoundPlayer.playTone(datapadTone);
            delay(15);
        }
    }
};

RearAxleStabilizerCalibrationDDS::RearAxleStabilizerCalibrationDDS(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer) : StandByDDS(datapadTFTLCD, datapadSoundPlayer) {}

void RearAxleStabilizerCalibrationDDS::show()
{
    StandByDDS::show();
    RearAxleStabilizerCalibrationDDSHelper rearAxleStabilizerCalibrationDDSHelper = RearAxleStabilizerCalibrationDDSHelper();
    rearAxleStabilizerCalibrationDDSHelper.drawRearAxleStabilizerCalibration(_datapadTFTLCD, _datapadSoundPlayer);
}