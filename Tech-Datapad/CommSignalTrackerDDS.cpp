//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "CommSignalTrackerDDS.h"
#include "DDSGraphicalUtility.h"
#include "DatapadDisplaySequenceConstants.h"

class BlinkingDot
{
public:
    BlinkingDot(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t radius, uint16_t colour, uint16_t backColour) : _tftlcd(tftlcd), _x(x), _y(y), _radius(radius), _colour(colour), _backColor(backColour) {}
    void update()
    {
        if (_previousMillis > 0)
        {
            _elapsed += millis() - _previousMillis;
            if (_elapsed < 100)
            {
                _state = 0;
            }
            else if (_elapsed < 650)
            {
                _state = 1;
            }
            else if (_elapsed < 1500)
            {
                _state = 2;
            }
            else if (_elapsed < 2000)
            {
                _elapsed = 0;
            }
        }
        _previousMillis = millis();
        int16_t colour;
        switch (_state)
        {
        case 0:
            colour = LIGHT_ENEMY_TARGET_COLOR;
            break;
        case 1:
            colour = _colour;
            break;
        case 2:
            colour = _backColor;
            break;
        }
        drawDot(colour);
    }

private:
    MCUFRIEND_kbv &_tftlcd;
    const int16_t _x, _y, _radius;
    const uint16_t _colour, _backColor;
    int16_t _state = 0, _elapsed = 0;
    unsigned long _previousMillis = 0;

    void drawDot(uint16_t colour)
    {
        _tftlcd.fillCircle(_x, _y, _radius, colour);
    }
};

class PulsingDot
{
public:
    PulsingDot(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t radius, uint16_t colour) : _tftlcd(tftlcd), _x(x), _y(y), _radius(radius), _colour(colour)
    {
    }

    void update()
    {
        if (_previousMillis > 0)
        {
            _elapsed += millis() - _previousMillis;
            if (_elapsed < 50)
            {
                _state = 0;
            }
            else if (_elapsed < 100)
            {
                _state = 1;
            }
            else if (_elapsed < 150)
            {
                _state = 2;
            }
            else if (_elapsed < 4000)
            {
                _state = 3;
            }
            else if (_elapsed < 5000)
            {
                _elapsed = 0;
            }
        }
        _previousMillis = millis();
        int16_t colour;
        switch (_state)
        {
        case 0:
            colour = TFT_DARKGREY;
            break;
        case 1:
            colour = TFT_LIGHTGREY;
            break;
        case 2:
            colour = LIGHT_ENEMY_TARGET_COLOR;
            break;
        case 3:
            colour = _colour;
            break;
        }
        drawDot(colour);
    }

private:
    MCUFRIEND_kbv &_tftlcd;
    const int16_t _x, _y, _radius;
    const uint16_t _colour;
    int16_t _state = 0, _elapsed = 0;
    unsigned long _previousMillis = 0;

    void drawDot(uint16_t colour)
    {
        _tftlcd.fillCircle(_x, _y, _radius, colour);
    }
};

class CommSignalTrackerDDSHelper
{
public:
    void drawCommSignalTracker(MCUFRIEND_kbv &tftlcd)
    {
        int16_t width = tftlcd.width();
        int16_t centerX = width / 2;
        int16_t centerY = tftlcd.height() / 2;
        int16_t radius = centerX - 1;
        //Draw Center Circle.
        int16_t centerCircleRadius = (width * 0.25) / 2;
        int16_t centerCirleWidth = width * 0.015;
        _ddsGraphicalUtility.drawInnerCircle(tftlcd, centerX, centerY, centerCircleRadius, centerCirleWidth, TFT_DARKCYAN);
        //Draw Walls.
        drawWalls(tftlcd, centerX, centerY, width);
        //Draw Rounded Frame.
        drawRoundFrame(tftlcd, centerX, centerY, radius);
        //Draw Red Pulsing & Blinking Dots Animation.
        drawPulsingBlinkingDots(tftlcd, centerX, centerY, width);
    }

private:
    DDSGraphicalUtility _ddsGraphicalUtility;

    void drawWalls(MCUFRIEND_kbv &tftlcd, int16_t centerX, int16_t centerY, int16_t width)
    {
        //Draw Wall A.
        int16_t wallHeight = (width * 0.36);
        int16_t wallTop = centerY - (width * 0.15) - wallHeight;
        int16_t wallWidth = width * 0.49;
        tftlcd.fillRoundRect(0, wallTop, wallWidth, wallHeight, 5, TFT_DARKCYAN);
        tftlcd.drawRoundRect(0, wallTop, wallWidth, wallHeight, 5, DISPLAY_RING_COLOR);
        //Draw Wall B.
        wallHeight = width * 0.377;
        wallWidth = width * 0.34;
        int16_t wallLeft = centerX + (width * 0.15);
        wallTop = centerY - (width * 0.146) - wallHeight;
        _ddsGraphicalUtility.drawRoundedRectangle(tftlcd, wallLeft, wallTop, wallWidth, wallHeight, DISPLAY_RING_COLOR, TFT_DARKCYAN);
        //Draw Wall C.
        wallTop = wallTop + wallHeight;
        wallHeight = width * 0.677;
        wallWidth = width * 0.31;
        wallLeft = centerX + (width * 0.18);
        _ddsGraphicalUtility.fillRectangle(tftlcd, wallLeft, wallTop, wallWidth, wallHeight, DISPLAY_RING_COLOR, TFT_DARKCYAN);
        _ddsGraphicalUtility.drawFastHorizontalLine(tftlcd, wallLeft + 1, wallTop, wallWidth, 2, TFT_DARKCYAN);
        //Draw Wall D.
        wallHeight = width * 0.33;
        wallWidth = width * 0.15;
        wallLeft = centerX - (width * 0.063) - wallWidth;
        wallTop = centerY + (width * 0.19);
        _ddsGraphicalUtility.drawRoundedRectangle(tftlcd, wallLeft, wallTop, wallWidth, wallHeight, DISPLAY_RING_COLOR, TFT_DARKCYAN);
        //Draw Wall E.
        wallHeight = width * 0.44;
        wallWidth = width * 0.24;
        wallLeft = centerX - (width * 0.25) - wallWidth;
        wallTop = centerY + (width * 0.03);
        _ddsGraphicalUtility.drawRoundedRectangle(tftlcd, wallLeft, wallTop, wallWidth, wallHeight, DISPLAY_RING_COLOR, TFT_DARKCYAN);
    }

    void drawRoundFrame(MCUFRIEND_kbv &tftlcd, int16_t centerX, int16_t centerY, int16_t radius)
    {
        int16_t firstArc = 12;
        int16_t secondArc = 90;
        int16_t thirdArc = 150;
        int16_t fourhtArc = 228;
        int16_t fifthtArc = 298;
        int16_t innerRoundFrameHeight = ((radius * 2) * 0.04) - GRID_OUTER_FRAME_OFFSET;
        int16_t innerRoundFrameRadius = radius - 3;
        tftlcd.drawCircle(centerX, centerY, radius, TFT_WHITE);
        _ddsGraphicalUtility.drawInnerCircle(tftlcd, centerX, centerY, radius - 1, GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility.fillArc(tftlcd, centerX, centerY, firstArc, 17, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility.fillArc(tftlcd, centerX, centerY, secondArc - 13, 3, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility.fillArc(tftlcd, centerX, centerY, secondArc - 23, 2, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight / 2, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility.fillArc(tftlcd, centerX, centerY, secondArc, 14, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility.fillArc(tftlcd, centerX, centerY, thirdArc, 20, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility.fillArc(tftlcd, centerX, centerY, fourhtArc, 14, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility.fillArc(tftlcd, centerX, centerY, fifthtArc - 10, 2, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight / 2, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility.fillArc(tftlcd, centerX, centerY, fifthtArc - 23, 3, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility.fillArc(tftlcd, centerX, centerY, fifthtArc, 17, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility.fillArc(tftlcd, centerX, centerY, 353, 1, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility.fillArc(tftlcd, centerX, centerY, 359, 1, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility.fillArc(tftlcd, centerX, centerY, 5, 1, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
    }

    void drawPulsingBlinkingDots(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t width)
    {
        int16_t redDotX = x + (width * 0.074);
        int16_t redDotY = y - (width * 0.23);
        int16_t redDotRadius = width * 0.03;
        PulsingDot pulsingDot1 = PulsingDot(tftlcd, redDotX, redDotY, redDotRadius, ENEMY_TARGET_COLOR);
        redDotX = x - (width * 0.36);
        redDotY = y - (width * 0.08);
        PulsingDot pulsingDot2 = PulsingDot(tftlcd, redDotX, redDotY, redDotRadius, ENEMY_TARGET_COLOR);
        redDotX = x + (width * 0.074);
        PulsingDot pulsingDot3 = PulsingDot(tftlcd, redDotX, redDotY, redDotRadius, ENEMY_TARGET_COLOR);
        redDotX = x - (width * 0.21);
        redDotY = y + (width * 0.11);
        PulsingDot pulsingDot4 = PulsingDot(tftlcd, redDotX, redDotY, redDotRadius, ENEMY_TARGET_COLOR);
        redDotY = y + (width * 0.12);
        PulsingDot pulsingDot5 = PulsingDot(tftlcd, x, redDotY, redDotRadius, ENEMY_TARGET_COLOR);
        redDotX = x + (width * 0.036);
        redDotY = y + (width * 0.21);
        PulsingDot pulsingDot6 = PulsingDot(tftlcd, redDotX, redDotY, redDotRadius, ENEMY_TARGET_COLOR);
        int16_t centerCommSinalBeepCircleRadius = (width * 0.088) / 2;
        BlinkingDot blinkingDot = BlinkingDot(tftlcd, x, y, centerCommSinalBeepCircleRadius, DISPLAY_RING_COLOR, DISPLAY_BACK_COLOR);
        int16_t elapsed = 0;
        int16_t interval = 10000;
        unsigned long previousMillis = millis();
        do
        {
            pulsingDot1.update();
            pulsingDot2.update();
            pulsingDot3.update();
            pulsingDot4.update();
            pulsingDot5.update();
            pulsingDot6.update();
            blinkingDot.update();
            elapsed += millis() - previousMillis;
            previousMillis = millis();
        } while (elapsed < interval);
    }
};

CommSignalTrackerDDS::CommSignalTrackerDDS(MCUFRIEND_kbv &tftlcd) : DatapadDisplaySequence(tftlcd), _tftlcd(tftlcd)
{
}

void CommSignalTrackerDDS::show()
{
    CommSignalTrackerDDSHelper commSignalTrackerDDSHelper = CommSignalTrackerDDSHelper();
    commSignalTrackerDDSHelper.drawCommSignalTracker(_tftlcd);
}