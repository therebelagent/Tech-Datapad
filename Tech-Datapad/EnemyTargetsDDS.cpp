//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "EnemyTargetsDDS.h"
#include "Fonts/Aurebesh3pt7b.h"
#include "Fonts/Aurebesh7pt7b.h"

class SonarGauge
{
public:
    SonarGauge(IDatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t radius, int16_t topY, int16_t innerCircleRadius, int16_t friendlyTargetTriangleBaseWidth, int16_t friendlyTargetTriangleHeight) : _datapadTFTLCD(datapadTFTLCD), _x(x), _y(y), _topY(topY), _radius(radius), _innerCircleRadius(innerCircleRadius), _friendlyTargetTriangleBaseWidth(friendlyTargetTriangleBaseWidth), _friendlyTargetTriangleHeight(friendlyTargetTriangleHeight){};

    void setup()
    {
        _gaugeY = _topY - (_radius * B_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE) - _innerCircleRadius;
        _gaugeLenght = (2 * _radius) * 0.6;
        _friendlyTargetTriangleY = _gaugeY - 5;
        _datapadTFTLCD.fillTriangle(_x, _friendlyTargetTriangleY, _friendlyTargetTriangleBaseWidth, _friendlyTargetTriangleHeight, DISPLAY_RING_COLOR);
        _lines = _degress / _angleJump;
        _linesCounter = 1;
    }

    void update()
    {
        if (_elapsed >= _interval)
        {
            if (_linesCounter <= _lines + 1)
            {
                float x1 = _gaugeLenght * sin(_angle * M_PI / 180);
                float y1 = _gaugeLenght * cos(_angle * M_PI / 180);
                _datapadTFTLCD.drawLine(_x, _gaugeY, _x + x1, _gaugeY - y1, 2, DISPLAY_RING_COLOR);
                _datapadTFTLCD.drawLine(_x, _gaugeY, _x + x1, _gaugeY - y1, 2, DISPLAY_BACK_COLOR);
                _datapadTFTLCD.fillTriangle(_x, _friendlyTargetTriangleY, _friendlyTargetTriangleBaseWidth, _friendlyTargetTriangleHeight, DISPLAY_RING_COLOR);
                _angle = _angle - _angleJump;
                if (_angle < 0)
                {
                    _angle = _angle + 360;
                }
                _linesCounter++;
            }
            else
            {
                _linesCounter = 1;
                _angle = 95;
                _elapsed = 0;
                _previousMillis = millis();
            }
        }
        else
        {
            _elapsed += millis() - _previousMillis;
            _previousMillis = millis();
        }
    }

private:
    IDatapadTFTLCD &_datapadTFTLCD;
    int16_t _x, _y, _radius, _topY, _innerCircleRadius, _friendlyTargetTriangleY, _friendlyTargetTriangleBaseWidth, _friendlyTargetTriangleHeight;
    int16_t _gaugeY, _gaugeLenght;
    int16_t _lines, _linesCounter, _angle = 95, _degress = 190;
    const int16_t _angleJump = 5;
    const int16_t _interval = 1500;
    int16_t _state = 0, _elapsed = _interval;
    unsigned long _previousMillis = 0;
};

class PulsingTriangle
{
public:
    void initialize(IDatapadTFTLCD *datapadTFTLCD, int16_t x, int16_t y, int16_t baseWidth, int16_t height, uint16_t color)
    {
        _datapadTFTLCD = datapadTFTLCD;
        _x = x;
        _y = y;
        _baseWidth = baseWidth;
        _height = height;
        _color = color;
    }

    void update()
    {
        if (_previousMillis > 0)
        {
            _elapsed += millis() - _previousMillis;
            if (_elapsed < 100)
            {
                _state = 0;
            }
            else if (_elapsed < 200)
            {
                _state = 1;
            }
            else if (_elapsed < 300)
            {
                _state = 2;
            }
            else if (_elapsed < 3200)
            {
                _state = 3;
            }
            else if (_elapsed < 3300)
            {
                _elapsed = 0;
            }
        }
        _previousMillis = millis();
        int16_t color;
        switch (_state)
        {
        case 0:
            color = TFT_DARKGREY;
            break;
        case 1:
            color = TFT_LIGHTGREY;
            break;
        case 2:
            color = LIGHT_ENEMY_TARGET_COLOR;
            break;
        case 3:
            color = _color;
            break;
        }
        drawTriangle(color);
    }

private:
    IDatapadTFTLCD *_datapadTFTLCD;
    int16_t _x, _y, _baseWidth, _height;
    uint16_t _color;
    int16_t _state = 0, _elapsed = 0;
    unsigned long _previousMillis = 0;

    void drawTriangle(uint16_t colour)
    {
        _datapadTFTLCD->fillTriangle(_x, _y, _baseWidth, _height, colour, true);
    }
};

class EnemyTargetsDDSHelper
{
public:
    void drawEnemyTargets(IDatapadTFTLCD &datapadTFTLCD)
    {
        int16_t centerX = (datapadTFTLCD.width() / 2);
        int16_t centerY = (datapadTFTLCD.height() / 2);
        int16_t radius = centerX - 1;
        int16_t topY = centerY + radius;
        int16_t innerCircleRadius = radius * B_INNER_CIRCLE_RELATIVE_DIAMETER;
        int16_t friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight;
        friendlyTargetTriangleBaseWidth = (innerCircleRadius * 2) * 0.25;
        friendlyTargetTriangleHeight = (innerCircleRadius * 2) * 0.33;
        datapadTFTLCD.drawGrid(centerX, centerY, radius, ENEMY_TARGET_GRID_LINES, DISPLAY_GRID_LINE_COLOR);
        drawHeaderText(datapadTFTLCD, centerX, centerY, radius);
        drawInnerArcs(datapadTFTLCD, centerX, centerY, radius);
        drawInnerCircles(datapadTFTLCD, centerX, radius, topY);
        _sonarGauge = new SonarGauge(datapadTFTLCD, centerX, centerY, radius, topY, innerCircleRadius, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight);
        _sonarGauge->setup();
        initializeTargets(datapadTFTLCD, centerX, radius, topY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight);
        drawTargetsAnimation(datapadTFTLCD, centerX, radius, topY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight);
    }

private:
    SonarGauge *_sonarGauge;
    PulsingTriangle _pulsingTriangles[21];

    void drawHeaderText(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius)
    {
        uint16_t textWidth, textHeight;
        int16_t textTop = (centerY - radius) + 8;
        datapadTFTLCD.printCenteredText(ENEMY_TARGET_HEADER_A_TEXT, &Aurebesh3pt7b, centerX, textTop, &textWidth, &textHeight, DISPLAY_RING_COLOR);
        textTop = (centerY - radius) + 19;
        datapadTFTLCD.printCenteredText(ENEMY_TARGET_HEADER_B_TEXT, &Aurebesh7pt7b, centerX, textTop, &textWidth, &textHeight, DISPLAY_RING_COLOR);
        int16_t textLeft = centerX - (textWidth / 2);
        int16_t littleRectangleWidth = 10;
        int16_t littleRectangleHeight = 3;
        datapadTFTLCD.fillRect(textLeft - 3 - littleRectangleWidth, textTop, littleRectangleWidth, littleRectangleHeight, TFT_WHITE);
        datapadTFTLCD.fillRect(textLeft + textWidth + 3, textTop, littleRectangleWidth, littleRectangleHeight, TFT_WHITE);
    }

    void drawInnerArcs(IDatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t radius)
    {
        int rx = radius - 3;
        int ry = radius - 3;
        datapadTFTLCD.fillArc(x, y, 285, 15, rx, ry, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(x, y, 30, 15, rx, ry, 3, DISPLAY_RING_COLOR);
        rx = rx - 6;
        ry = ry - 6;
        datapadTFTLCD.fillArc(x, y, 315, 4, rx, ry, 4, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(x, y, 290, 5, rx, ry, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(x, y, 306, 1, rx, ry, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(x, y, 311, 1, rx, ry, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(x, y, 33, 4, rx, ry, 4, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(x, y, 46, 1, rx, ry, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(x, y, 51, 1, rx, ry, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(x, y, 55, 5, rx, ry, 3, DISPLAY_RING_COLOR);
        rx = radius - 3;
        ry = radius - 3;
        datapadTFTLCD.fillArc(x, y, 165, 10, rx, ry, 2, DISPLAY_RING_COLOR);
        int16_t topY = y + radius;
        datapadTFTLCD.fillCircle(x, topY - 19, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(x + 14, topY - 16, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(x + 28, topY - 16, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(x + 42, topY - 16, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(x - 14, topY - 16, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(x - 28, topY - 16, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(x - 42, topY - 16, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastHorizontalLine(x - 39, topY - 11, 78, 2, DISPLAY_RING_COLOR);
        int height = 10;
        datapadTFTLCD.drawFastVerticalLine(x, topY - 19, height, 3, DISPLAY_RING_COLOR);
    }

    void drawInnerCircles(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t radius, int16_t topY)
    {
        int16_t innerCircleRadius = radius * A_INNER_CIRCLE_RELATIVE_DIAMETER;
        int16_t innerCircleCenterY = topY - (radius * A_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE) - innerCircleRadius;
        datapadTFTLCD.drawInnerCircle(centerX, innerCircleCenterY, innerCircleRadius, GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
        innerCircleRadius = radius * B_INNER_CIRCLE_RELATIVE_DIAMETER;
        innerCircleCenterY = topY - (radius * B_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE) - innerCircleRadius;
        datapadTFTLCD.drawInnerCircle(centerX, innerCircleCenterY, innerCircleRadius, GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
    }

    void initializeTargets(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t radius, int16_t topY, int16_t friendlyTargetTriangleBaseWidth, int16_t friendlyTargetTriangleHeight)
    {
        int16_t innerCircleRadius = radius * B_INNER_CIRCLE_RELATIVE_DIAMETER;
        int16_t innerCircleCenterY = topY - (radius * B_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE) - innerCircleRadius;
        int16_t enemyTargetTriangleBaseWidth = friendlyTargetTriangleBaseWidth * 0.75;
        int16_t enemyTargetTriangleHeight = friendlyTargetTriangleHeight * 0.6;
        int16_t enemyX = centerX;
        _pulsingTriangles[0].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 75, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        _pulsingTriangles[1].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 103, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        _pulsingTriangles[2].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 135, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        _pulsingTriangles[3].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 170, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        enemyX = centerX - 25;
        _pulsingTriangles[4].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 95, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        _pulsingTriangles[5].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 135, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        _pulsingTriangles[6].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 170, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        enemyX = enemyX - 25;
        _pulsingTriangles[7].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 75, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        _pulsingTriangles[8].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 125, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        _pulsingTriangles[9].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 155, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        enemyX = enemyX - 25;
        _pulsingTriangles[10].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 115, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        _pulsingTriangles[11].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 170, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        enemyX = enemyX - 25;
        _pulsingTriangles[12].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 135, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        enemyX = centerX + 25;
        _pulsingTriangles[13].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 100, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        _pulsingTriangles[14].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 140, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        _pulsingTriangles[15].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 170, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        enemyX = enemyX + 25;
        _pulsingTriangles[16].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 105, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        _pulsingTriangles[17].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 145, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        enemyX = enemyX + 25;
        _pulsingTriangles[18].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 135, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        _pulsingTriangles[19].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 165, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
        enemyX = enemyX + 25;
        _pulsingTriangles[20].initialize(&datapadTFTLCD, enemyX, innerCircleCenterY - 145, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, ENEMY_TARGET_COLOR);
    }

    void drawTargetsAnimation(IDatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t radius, int16_t topY, int16_t friendlyTargetTriangleBaseWidth, int16_t friendlyTargetTriangleHeight)
    {
        int16_t elapsed = 0;
        int16_t interval = 10000;
        unsigned long previousMillis = millis();
        do
        {
            for (int16_t counter = 0; counter < 21; counter++)
            {
                _pulsingTriangles[counter].update();
            }
            _sonarGauge->update();
            elapsed += millis() - previousMillis;
            previousMillis = millis();
        } while (elapsed < interval);
        delete _sonarGauge;
    }
};

EnemyTargetsDDS::EnemyTargetsDDS(IDatapadTFTLCD &datapadTFTLCD) : DatapadDisplaySequence(datapadTFTLCD) {}

void EnemyTargetsDDS::show()
{
    EnemyTargetsDDSHelper enemyTargetsDDSHelper;
    enemyTargetsDDSHelper.drawEnemyTargets(_datapadTFTLCD);
}