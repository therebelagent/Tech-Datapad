#include "EnemyTargetsDDS.h"
#include "DatapadDisplaySequenceConstants.h"
#include "DDSGraphicalUtility.h"
#include "Fonts/Aurebesh3pt7b.h"
#include "Fonts/Aurebesh5pt7b.h"

class EnemyTargetsDDSHelper
{
public:
    void drawEnemyTargets(MCUFRIEND_kbv *tftlcd)
    {
        int16_t centerX = (tftlcd->width() / 2);
        int16_t centerY = (tftlcd->height() / 2);
        int16_t radius = centerX - 1;
        int16_t topY = centerY + radius;
        int16_t friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight;
        drawHeaderText(tftlcd, centerX, centerY, radius);
        drawInnerArcs(tftlcd, centerX, centerY, radius);
        drawInnerCircles(tftlcd, centerX, radius, topY);
        drawSonarAnimation(tftlcd, centerX, centerY, radius, topY, &friendlyTargetTriangleBaseWidth, &friendlyTargetTriangleHeight);
        drawInnerCircles(tftlcd, centerX, radius, topY);
        drawTargetsAnimation(tftlcd, centerX, radius, topY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight);
    }

private:
    DDSGraphicalUtility *_ddsGraphicalUtility = new DDSGraphicalUtility();

    void drawSonarAnimation(MCUFRIEND_kbv *tftlcd, int16_t centerX, int16_t centerY, int16_t radius, int16_t topY, int16_t *friendlyTargetTriangleBaseWidth, int16_t *friendlyTargetTriangleHeight)
    {
        int16_t innerCircleRadius = radius * B_INNER_CIRCLE_RELATIVE_DIAMETER;
        int16_t innerCircleCenterY = topY - (radius * B_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE) - innerCircleRadius;
        int16_t gaugeLenght = (2 * radius) * 0.65;
        *friendlyTargetTriangleBaseWidth = (innerCircleRadius * 2) * 0.25;
        *friendlyTargetTriangleHeight = (innerCircleRadius * 2) * 0.33;
        int16_t friendlyTargetTriangleY = innerCircleCenterY - 5;
        _ddsGraphicalUtility->fillTriangle(tftlcd, centerX, friendlyTargetTriangleY, *friendlyTargetTriangleBaseWidth, *friendlyTargetTriangleHeight, DISPLAY_RING_COLOR);
        delay(1000);

        int16_t angle = 95;
        int16_t degress = 190;
        int16_t angleJump = 2;
        int16_t lines = degress / angleJump;
        int16_t linesCounter = 1;
        while (linesCounter <= lines + 1)
        {
            float x1 = gaugeLenght * sin(angle * M_PI / 180);
            float y1 = gaugeLenght * cos(angle * M_PI / 180);
            tftlcd->drawLine(centerX, innerCircleCenterY, centerX + x1, innerCircleCenterY - y1, DISPLAY_RING_COLOR);
            tftlcd->drawLine(centerX, innerCircleCenterY, centerX + x1, innerCircleCenterY - y1, DISPLAY_BACK_COLOR);
            _ddsGraphicalUtility->fillTriangle(tftlcd, centerX, friendlyTargetTriangleY, *friendlyTargetTriangleBaseWidth, *friendlyTargetTriangleHeight, DISPLAY_RING_COLOR);
            angle = angle - angleJump;
            if (angle < 0)
            {
                angle = angle + 360;
            }
            linesCounter++;
        }

        _ddsGraphicalUtility->drawGrid(tftlcd, centerX - 1, centerY, radius);
    }

    void drawHeaderText(MCUFRIEND_kbv *tftlcd, int16_t centerX, int16_t centerY, int16_t radius)
    {
        uint16_t textWidth, textHeight;
        int16_t textTop = (centerY - radius) + 11;
        _ddsGraphicalUtility->printCenteredText(tftlcd, ENEMY_TARGET_HEADER_A_TEXT, &Aurebesh3pt7b, centerX, textTop, &textWidth, &textHeight, DISPLAY_RING_COLOR);
        textTop = (centerY - radius) + 23;
        _ddsGraphicalUtility->printCenteredText(tftlcd, ENEMY_TARGET_HEADER_B_TEXT, &Aurebesh5pt7b, centerX, textTop, &textWidth, &textHeight, DISPLAY_RING_COLOR);
        int16_t textLeft = centerX - (textWidth / 2);
        tftlcd->fillCircle(textLeft - 5, textTop, 2, DISPLAY_RING_COLOR);
        tftlcd->fillCircle(textLeft + textWidth + 5, textTop, 2, DISPLAY_RING_COLOR);
    }

    void drawInnerCircles(MCUFRIEND_kbv *tftlcd, int16_t centerX, int16_t radius, int16_t topY)
    {
        int16_t innerCircleRadius = radius * A_INNER_CIRCLE_RELATIVE_DIAMETER;
        int16_t innerCircleCenterY = topY - (radius * A_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE) - innerCircleRadius;
        _ddsGraphicalUtility->drawInnerCircle(tftlcd, centerX, innerCircleCenterY, innerCircleRadius, GRID_OUTTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
        innerCircleRadius = radius * B_INNER_CIRCLE_RELATIVE_DIAMETER;
        innerCircleCenterY = topY - (radius * B_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE) - innerCircleRadius;
        _ddsGraphicalUtility->drawInnerCircle(tftlcd, centerX, innerCircleCenterY, innerCircleRadius, GRID_OUTTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
    }

    void drawInnerArcs(MCUFRIEND_kbv *tftlcd, int16_t x, int16_t y, int16_t radius)
    {
        int width = 3;
        int rx = radius - 8;
        int ry = radius - 8;
        _ddsGraphicalUtility->fillArc(tftlcd, x, y, 285, 15, rx, ry, width, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, x, y, 30, 15, rx, ry, width, DISPLAY_RING_COLOR);
        rx = rx - 6;
        ry = ry - 6;
        _ddsGraphicalUtility->fillArc(tftlcd, x, y, 315, 4, rx, ry, width, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, x, y, 33, 4, rx, ry, width, DISPLAY_RING_COLOR);
        rx = radius - 6;
        ry = radius - 6;
        width = 1;
        _ddsGraphicalUtility->fillArc(tftlcd, x, y, 165, 10, rx, ry, width, DISPLAY_RING_COLOR);
        int16_t topY = y + radius;
        tftlcd->fillCircle(x, topY - 19, 3, DISPLAY_RING_COLOR);
        tftlcd->fillCircle(x + 14, topY - 16, 2, DISPLAY_RING_COLOR);
        tftlcd->fillCircle(x + 28, topY - 16, 2, DISPLAY_RING_COLOR);
        tftlcd->fillCircle(x + 42, topY - 16, 2, DISPLAY_RING_COLOR);
        tftlcd->fillCircle(x - 14, topY - 16, 2, DISPLAY_RING_COLOR);
        tftlcd->fillCircle(x - 28, topY - 16, 2, DISPLAY_RING_COLOR);
        tftlcd->fillCircle(x - 42, topY - 16, 2, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->drawFastHorizontalLine(tftlcd, x - 39, topY - 11, 78, width, DISPLAY_RING_COLOR);
        int height = 12;
        _ddsGraphicalUtility->drawFastVerticalLine(tftlcd, x, topY - 19, height, 3, DISPLAY_RING_COLOR);
    }

    void drawTargetsAnimation(MCUFRIEND_kbv *tftlcd, int16_t centerX, int16_t radius, int16_t topY, int16_t friendlyTargetTriangleBaseWidth, int16_t friendlyTargetTriangleHeight)
    {
        drawTargets(tftlcd, centerX, radius, topY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight, TFT_DARKGREY);
        delay(50);
        drawTargets(tftlcd, centerX, radius, topY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight, TFT_LIGHTGREY);
        delay(50);
        drawTargets(tftlcd, centerX, radius, topY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight, LIGHT_ENEMY_TARGET_COLOR);
        delay(50);
        drawTargets(tftlcd, centerX, radius, topY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight, ENEMY_TARGET_COLOR);
    }
    void drawTargets(MCUFRIEND_kbv *tftlcd, int16_t centerX, int16_t radius, int16_t topY, int16_t friendlyTargetTriangleBaseWidth, int16_t friendlyTargetTriangleHeight, int16_t colour)
    {
        int16_t innerCircleRadius = radius * B_INNER_CIRCLE_RELATIVE_DIAMETER;
        int16_t innerCircleCenterY = topY - (radius * B_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE) - innerCircleRadius;
        int16_t enemyTargetTriangleBaseWidth = friendlyTargetTriangleBaseWidth * 0.75;
        int16_t enemyTargetTriangleHeight = friendlyTargetTriangleHeight * 0.6;
        int16_t enemyX = centerX;
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 75, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 103, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 135, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 170, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = centerX - 25;
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 95, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 135, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 170, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = enemyX - 25;
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 75, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 125, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 155, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = enemyX - 25;
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 115, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 170, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = enemyX - 25;
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 135, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = centerX + 25;
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 100, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 140, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 170, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = enemyX + 25;
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 105, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 145, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = enemyX + 25;
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 135, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 165, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = enemyX + 25;
        _ddsGraphicalUtility->fillTriangle(tftlcd, enemyX, innerCircleCenterY - 145, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
    }
};

EnemyTargetsDDS::EnemyTargetsDDS(MCUFRIEND_kbv *tftlcd) : BasicGridDDS(tftlcd) { _tftlcd = tftlcd; };

void EnemyTargetsDDS::show()
{
    BasicGridDDS::show();
    EnemyTargetsDDSHelper *enemyTargetsDDSHelper = new EnemyTargetsDDSHelper();
    enemyTargetsDDSHelper->drawEnemyTargets(_tftlcd);
}