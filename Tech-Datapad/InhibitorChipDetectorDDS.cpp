//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "InhibitorChipDetectorDDS.h"
#include "DDSHeadScanImage.h"
#include "Fonts/Aurebesh3pt7b.h"
#include "Fonts/Aurebesh6pt7b.h"

class ForeignBodyTracker
{
public:
    ForeignBodyTracker(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer, int16_t x, int16_t y) : _datapadTFTLCD(datapadTFTLCD), _datapadSoundPlayer(datapadSoundPlayer), _x(x), _y(y)
    {
        _datapadTone.frequency = 1500;
        _datapadTone.duration = 100;
    }

    void draw()
    {
        int16_t width = _datapadTFTLCD.width();
        //Draw Main Circle.
        _circleRadius = (getWidth(width, 0.2)) / 2;
        int16_t circleLineWidth = getWidth(width, 0.015);
        _datapadTFTLCD.fillArc(_x, _y, 0, 360, _circleRadius, _circleRadius, circleLineWidth, DISPLAY_RING_COLOR);
        //Draw Internal Triangles.
        int16_t triangleBaseWidth = getWidth(width, 0.03);
        int16_t triangleHeight = getWidth(width, 0.06);
        int16_t triangleX = _x;
        int16_t triangleY = _y + _circleRadius;
        _datapadTFTLCD.fillVerticalTriangle(triangleX, triangleY - 1, triangleBaseWidth + 2, triangleHeight + 2, DISPLAY_RING_COLOR);
        triangleY = _y - _circleRadius;
        _datapadTFTLCD.fillVerticalTriangle(triangleX, triangleY, triangleBaseWidth, triangleHeight, DISPLAY_RING_COLOR, true);
        triangleX = _x - _circleRadius;
        triangleY = _y;
        _datapadTFTLCD.fillArrow(triangleX, triangleY, triangleBaseWidth + 2, triangleHeight + 2, DISPLAY_RING_COLOR);
        triangleX = _x + _circleRadius;
        _datapadTFTLCD.fillArrow(triangleX - 1, triangleY, triangleBaseWidth + 2, triangleHeight + 2, DISPLAY_RING_COLOR, true);
        //Draw U Base.
        int16_t uBaseWidth = getWidth(width, 0.17);
        int16_t uBaseLeft = _x - (uBaseWidth / 2);
        int16_t uBaseTop = _y + getWidth(width, 0.14);
        int16_t lineHeight = 2;
        _datapadTFTLCD.fillRect(uBaseLeft, uBaseTop, uBaseWidth, lineHeight, DISPLAY_RING_COLOR);
        int16_t uBaseVerticalLineHeight = getWidth(width, 0.04);
        int16_t uBaseVerticalSmallLineHeight = getWidth(width, 0.015);
        int16_t uBaseVerticalSmallerLineHeight = uBaseVerticalSmallLineHeight / 2;
        int16_t quarter = uBaseWidth * 0.25;
        _datapadTFTLCD.fillRect(uBaseLeft, uBaseTop, lineHeight, -uBaseVerticalLineHeight, DISPLAY_RING_COLOR);
        _datapadTFTLCD.fillRect(uBaseLeft + quarter, uBaseTop, lineHeight, -uBaseVerticalSmallerLineHeight, DISPLAY_RING_COLOR);
        _datapadTFTLCD.fillRect(uBaseLeft + (quarter * 2), uBaseTop, lineHeight, -uBaseVerticalSmallLineHeight, DISPLAY_RING_COLOR);
        _datapadTFTLCD.fillRect(uBaseLeft + (quarter * 3), uBaseTop, lineHeight, -uBaseVerticalSmallerLineHeight, DISPLAY_RING_COLOR);
        _datapadTFTLCD.fillRect(uBaseLeft + uBaseWidth - lineHeight, uBaseTop, lineHeight, -uBaseVerticalLineHeight, DISPLAY_RING_COLOR);
        //Draw Foreign Body Label.
        int16_t textTop = uBaseTop + getWidth(width, 0.019);
        _datapadTFTLCD.printCenteredText(INHIBITOR_CHIP_DETECTOR_FOREIGN_TRACKER_TEXT, &Aurebesh3pt7b, _x, textTop, DISPLAY_RING_COLOR);
        textTop += 5;
        _datapadTFTLCD.printCenteredText(INHIBITOR_CHIP_DETECTOR_BODY_TRACKER_TEXT, &Aurebesh3pt7b, _x, textTop, DISPLAY_RING_COLOR);
        //Draw Foreign Body Dot.
        _color = _datapadTFTLCD.readPixel(_x + 5, _y);
        drawForeignBodyDot();
    }

    void update()
    {
        if (_previousMillis > 0)
        {
            _elapsed += millis() - _previousMillis;
            if (_elapsed >= 40)
            {
                if (_raising)
                {
                    _progressLevel = _progressLevel + _increment;
                }
                else
                {
                    _progressLevel = _progressLevel - _increment;
                }
                if (_progressLevel > 100)
                {
                    _progressLevel = 100;
                    _raising = false;
                }
                else if (_progressLevel < 0)
                {
                    _datapadSoundPlayer.playTone(_datapadTone);
                    _progressLevel = 0;
                    _raising = true;
                }
                //Draw Foreign Body Dot.
                drawForeignBodyDot();
                _elapsed = 0;
            }
        }
        _previousMillis = millis();
    }

private:
    IDatapadTFTLCD &_datapadTFTLCD;
    IDatapadSoundPlayer &_datapadSoundPlayer;
    DatapadTone _datapadTone;
    int16_t _x, _y, _circleRadius, _progressLevel = 100, _increment = 10, _elapsed = 0, _baseCircleRadius = 0;
    unsigned long _previousMillis = 0;
    bool _raising = true;
    uint16_t _color;

    void drawForeignBodyDot()
    {
        float value = getMappedValue(_progressLevel);
        int16_t baseCircleRadius = _circleRadius * value;
        if (_baseCircleRadius != baseCircleRadius)
        {
            if (_progressLevel < 100)
            {
                value = getMappedValue(100);
                int16_t canvasCircleRadius = _circleRadius * value;
                _datapadTFTLCD.fillCircle(_x, _y, canvasCircleRadius, _color);
            }
            _datapadTFTLCD.fillCircle(_x, _y, baseCircleRadius, DISPLAY_RING_COLOR);
            int16_t dotCircleRadius = baseCircleRadius * 0.8;
            _datapadTFTLCD.fillCircle(_x, _y, dotCircleRadius, TFT_RED);
        }
        _baseCircleRadius = baseCircleRadius;
    }

    float getMappedValue(int16_t progressLevel)
    {
        int16_t mappedValue = map(progressLevel, 0, 100, 22, 33);
        float value = (float)mappedValue / (float)100;
        return value;
    }

    int16_t getWidth(int16_t reference, float percentage)
    {
        int16_t result = reference * percentage;
        if (result % 2 != 0)
            result--;
        return result;
    }
};

class InhibitorChipDetectorDDSHelper
{
public:
    void drawInhibitorChipDetector(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer)
    {
        int16_t width = datapadTFTLCD.width();
        int16_t centerX = width / 2;
        int16_t centerY = datapadTFTLCD.height() / 2;
        int16_t radius = centerX - 1;
        drawFixedScreenDetails(datapadTFTLCD, datapadSoundPlayer, centerX, centerY, radius, width);
        playBeeps(datapadSoundPlayer);
        RunForeignBodyTracker();
    }

private:
    ForeignBodyTracker *_foreignBodyTracker = nullptr;

    void drawFixedScreenDetails(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer, int16_t centerX, int16_t centerY, int16_t radius, int16_t width)
    {
        //Draw Head Scan Image.
        DDSHeadScanImage ddsHeadScanImage = DDSHeadScanImage(datapadTFTLCD);
        ddsHeadScanImage.drawImage(centerX - (ddsHeadScanImage.width() / 2), centerY - (width * 0.39));
        //Draw Fixed Screen Details.
        datapadTFTLCD.drawGrid(centerX, centerY, radius, INHIBITOR_CHIP_DETECTOR_GRID_LINES, DISPLAY_GRID_LINE_COLOR);
        datapadTFTLCD.drawInnerCircle(centerX, centerY, radius, INHIBITOR_CHIP_DETECTOR_GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
        //Draw Arcs.
        int16_t arcRadius = radius - INHIBITOR_CHIP_DETECTOR_GRID_OUTER_FRAME_OFFSET - 4;
        int16_t firstInnerArcRadius = arcRadius - 2;
        int16_t SecondInnerArcRadius = firstInnerArcRadius - 1;
        datapadTFTLCD.fillArc(centerX, centerY, 35, 16, arcRadius, arcRadius, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 47, 8, firstInnerArcRadius, firstInnerArcRadius, 1, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 53, 4, SecondInnerArcRadius, SecondInnerArcRadius, 1, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 277, 16, arcRadius, arcRadius, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 289, 8, firstInnerArcRadius, firstInnerArcRadius, 1, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 295, 4, SecondInnerArcRadius, SecondInnerArcRadius, 1, DISPLAY_RING_COLOR);
        //Draw Top Details.
        int16_t separation = width * 0.01;
        int16_t lineWidth = width * 0.025;
        int16_t bannerTop = centerY - (width * 0.445);
        drawRightBannerDashes(datapadTFTLCD, centerX + 1, lineWidth, separation, bannerTop, width);
        drawLeftBannerDashes(datapadTFTLCD, centerX, lineWidth, separation, bannerTop, width);
        //Draw Bottom Banner.
        bannerTop = centerY + (width * 0.33);
        uint16_t textWidth, textHeight;
        datapadTFTLCD.printCenteredText(INHIBITOR_CHIP_DETECTOR_ACTIVE_SCAN_BANNER_TEXT, &Aurebesh6pt7b, centerX, bannerTop, &textWidth, &textHeight, DISPLAY_RING_COLOR);
        int16_t lineLeft = centerX - (textWidth / 2) + textWidth;
        drawRightBannerDashes(datapadTFTLCD, lineLeft, lineWidth, separation, bannerTop, width);
        lineLeft = centerX - (textWidth / 2);
        drawLeftBannerDashes(datapadTFTLCD, lineLeft, lineWidth, separation, bannerTop, width);
        //Draw Bottom Details.
        int16_t bottomArcRadius = arcRadius + 2;
        datapadTFTLCD.fillArc(centerX, centerY, 144, 24, bottomArcRadius, bottomArcRadius, 2, DISPLAY_RING_COLOR);
        int16_t bottomLineTop = centerY + (width * 0.38) + 1;
        int16_t bottomLineLeft = centerX - (width * 0.28);
        int16_t bottomLineWidth = width * 0.03;
        datapadTFTLCD.fillRect(bottomLineLeft, bottomLineTop, bottomLineWidth, 2, DISPLAY_RING_COLOR);
        bottomLineLeft = centerX + (width * 0.28) - bottomLineWidth;
        datapadTFTLCD.fillRect(bottomLineLeft, bottomLineTop, bottomLineWidth, 2, DISPLAY_RING_COLOR);
        bottomLineTop = centerY + (width * 0.43);
        bottomLineWidth = width * 0.08;
        bottomLineLeft = centerX - (bottomLineWidth / 2);
        datapadTFTLCD.fillRect(bottomLineLeft, bottomLineTop, bottomLineWidth, 2, DISPLAY_RING_COLOR);
        int16_t bottomUnderscoreLineTop = centerY + (width * 0.44);
        int16_t bottomUnderscoreLineLeft = bottomLineLeft - bottomLineWidth - 3;
        datapadTFTLCD.fillRect(bottomUnderscoreLineLeft, bottomUnderscoreLineTop, bottomLineWidth, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawLine(bottomUnderscoreLineLeft + bottomLineWidth, bottomUnderscoreLineTop, bottomLineLeft, bottomLineTop, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawLine(bottomUnderscoreLineLeft, bottomUnderscoreLineTop, bottomUnderscoreLineLeft - 3, bottomLineTop, 2, DISPLAY_RING_COLOR);
        int16_t bottomUnderscoreLineWidth = width * 0.05;
        datapadTFTLCD.fillRect(bottomUnderscoreLineLeft - bottomUnderscoreLineWidth - 2, bottomLineTop, bottomUnderscoreLineWidth, 2, DISPLAY_RING_COLOR);
        bottomUnderscoreLineLeft = bottomLineLeft + bottomLineWidth + 3;
        datapadTFTLCD.fillRect(bottomUnderscoreLineLeft, bottomUnderscoreLineTop, bottomLineWidth, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawLine(bottomLineLeft + bottomLineWidth - 2, bottomLineTop, bottomUnderscoreLineLeft - 2, bottomUnderscoreLineTop, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawLine(bottomUnderscoreLineLeft + bottomLineWidth, bottomUnderscoreLineTop, bottomUnderscoreLineLeft + bottomLineWidth + 2, bottomLineTop, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillRect(bottomUnderscoreLineLeft + bottomLineWidth + 2, bottomLineTop, bottomUnderscoreLineWidth, 2, DISPLAY_RING_COLOR);
        bottomLineTop = centerY + (width * 0.47);
        bottomLineWidth = width * 0.17;
        bottomLineLeft = centerX - (bottomLineWidth / 2);
        datapadTFTLCD.fillRect(bottomLineLeft, bottomLineTop, bottomLineWidth, 2, DISPLAY_RING_COLOR);
        bottomLineTop = bottomLineTop - 2;
        bottomLineWidth = width * 0.21;
        bottomLineLeft = centerX - (bottomLineWidth / 2);
        datapadTFTLCD.fillRect(bottomLineLeft, bottomLineTop, bottomLineWidth, 2, DISPLAY_RING_COLOR);
        bottomLineTop = bottomLineTop - 1;
        bottomLineWidth = width * 0.25;
        bottomLineLeft = centerX - (bottomLineWidth / 2);
        datapadTFTLCD.fillRect(bottomLineLeft, bottomLineTop, bottomLineWidth, 2, DISPLAY_RING_COLOR);
        int16_t innerBottomArcRadius = bottomArcRadius - 5;
        datapadTFTLCD.fillArc(centerX, centerY, 146, 4, innerBottomArcRadius, innerBottomArcRadius, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 202, 4, innerBottomArcRadius, innerBottomArcRadius, 2, DISPLAY_RING_COLOR);
        //Draw Foreign Body Tracker.
        int16_t foreignBodyTrackerY = centerY - (width * 0.27);
        _foreignBodyTracker = new ForeignBodyTracker(datapadTFTLCD, datapadSoundPlayer, centerX, foreignBodyTrackerY);
    }

    void drawRightBannerDashes(IDatapadTFTLCD &datapadTFTLCD, int16_t lineLeft, int16_t lineWidth, int16_t separation, int16_t y, int16_t width)
    {
        lineLeft += separation;
        int16_t lineHeight = 3;
        datapadTFTLCD.drawFastHorizontalLine(lineLeft, y - (lineHeight / 2), lineWidth, lineHeight, DISPLAY_RING_COLOR);
        lineLeft += separation + lineWidth;
        datapadTFTLCD.drawFastHorizontalLine(lineLeft, y - (lineHeight / 2), lineWidth, lineHeight, DISPLAY_RING_COLOR);
        lineLeft += separation + lineWidth;
        datapadTFTLCD.drawFastHorizontalLine(lineLeft, y, lineWidth * 2, 2, DISPLAY_RING_COLOR);
        lineLeft += separation + (lineWidth * 2);
        datapadTFTLCD.drawFastHorizontalLine(lineLeft, y, (lineWidth / 2), 2, DISPLAY_RING_COLOR);
    }

    void drawLeftBannerDashes(IDatapadTFTLCD &datapadTFTLCD, int16_t lineLeft, int16_t lineWidth, int16_t separation, int16_t y, int16_t width)
    {
        int16_t lineHeight = 3;
        int16_t left = lineLeft - separation - lineWidth;
        datapadTFTLCD.drawFastHorizontalLine(left, y - (lineHeight / 2), lineWidth, lineHeight, DISPLAY_RING_COLOR);
        left = left - separation - lineWidth;
        datapadTFTLCD.drawFastHorizontalLine(left, y - (lineHeight / 2), lineWidth, lineHeight, DISPLAY_RING_COLOR);
        left = left - separation - (lineWidth * 2);
        datapadTFTLCD.drawFastHorizontalLine(left, y, lineWidth * 2, 2, DISPLAY_RING_COLOR);
        left = left - separation - (lineWidth / 2);
        datapadTFTLCD.drawFastHorizontalLine(left, y, (lineWidth / 2), 2, DISPLAY_RING_COLOR);
    }

    void RunForeignBodyTracker()
    {
        _foreignBodyTracker->draw();
        int16_t elapsed = 0;
        int16_t interval = 5000;
        unsigned long previousMillis = millis();
        do
        {
            _foreignBodyTracker->update();
            elapsed += millis() - previousMillis;
            previousMillis = millis();
        } while (elapsed < interval);
        delete _foreignBodyTracker;
    }

    void playBeeps(IDatapadSoundPlayer &datapadSoundPlayer)
    {
        DatapadTone datapadTone;
        datapadTone.frequency = 3000;
        datapadTone.duration = 40;
        for (size_t counter = 0; counter < 5; counter++)
        {
            datapadSoundPlayer.playTone(datapadTone);
            delay(50);
        }
    }
};

InhibitorChipDetectorDDS::InhibitorChipDetectorDDS(IDatapadTFTLCD &datapadTFTLCD, IDatapadSoundPlayer &datapadSoundPlayer) : DatapadDisplaySequence(datapadTFTLCD, datapadSoundPlayer) {}

void InhibitorChipDetectorDDS::show()
{
    InhibitorChipDetectorDDSHelper inhibitorChipDetectorDDSHelper;
    inhibitorChipDetectorDDSHelper.drawInhibitorChipDetector(_datapadTFTLCD, _datapadSoundPlayer);
}