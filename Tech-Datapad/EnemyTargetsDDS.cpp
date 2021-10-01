//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "EnemyTargetsDDS.h"
#include "DatapadDisplaySequenceConstants.h"
#include "Fonts/Aurebesh3pt7b.h"
#include "Fonts/Aurebesh4pt7b.h"

class EnemyTargetsDDSHelper
{
public:
    void drawEnemyTargets(DatapadTFTLCD &datapadTFTLCD)
    {
        int16_t centerX = (datapadTFTLCD.width() / 2);
        int16_t centerY = (datapadTFTLCD.height() / 2);
        int16_t radius = centerX - 1;
        int16_t topY = centerY + radius;
        int16_t friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight;
        drawHeaderText(datapadTFTLCD, centerX, centerY, radius);
        drawInnerArcs(datapadTFTLCD, centerX, centerY, radius);
        drawInnerCircles(datapadTFTLCD, centerX, radius, topY);
        drawSonarAnimation(datapadTFTLCD, centerX, centerY, radius, topY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight);
        drawInnerCircles(datapadTFTLCD, centerX, radius, topY);
        drawTargetsAnimation(datapadTFTLCD, centerX, radius, topY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight);
    }

private:
    void drawSonarAnimation(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius, int16_t topY, int16_t &friendlyTargetTriangleBaseWidth, int16_t &friendlyTargetTriangleHeight)
    {
        int16_t innerCircleRadius = radius * B_INNER_CIRCLE_RELATIVE_DIAMETER;
        int16_t gaugeY = topY - (radius * B_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE) - innerCircleRadius;
        int16_t gaugeLenght = (2 * radius) * 0.65;
        friendlyTargetTriangleBaseWidth = (innerCircleRadius * 2) * 0.25;
        friendlyTargetTriangleHeight = (innerCircleRadius * 2) * 0.33;
        int16_t friendlyTargetTriangleY = gaugeY - 5;
        datapadTFTLCD.fillTriangle(centerX, friendlyTargetTriangleY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight, DISPLAY_RING_COLOR);
        int16_t angle = 95;
        int16_t degress = 190;
        int16_t angleJump = 2;
        int16_t lines = degress / angleJump;
        int16_t linesCounter = 1;
        while (linesCounter <= lines + 1)
        {
            float x1 = gaugeLenght * sin(angle * M_PI / 180);
            float y1 = gaugeLenght * cos(angle * M_PI / 180);
            datapadTFTLCD.drawLine(centerX, gaugeY, centerX + x1, gaugeY - y1, DISPLAY_RING_COLOR);
            datapadTFTLCD.drawLine(centerX, gaugeY, centerX + x1, gaugeY - y1, DISPLAY_BACK_COLOR);
            datapadTFTLCD.fillTriangle(centerX, friendlyTargetTriangleY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight, DISPLAY_RING_COLOR);
            angle = angle - angleJump;
            if (angle < 0)
            {
                angle = angle + 360;
            }
            linesCounter++;
        }
        datapadTFTLCD.drawGrid(centerX - 1, centerY, radius);
    }

    void drawHeaderText(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius)
    {
        uint16_t textWidth, textHeight;
        int16_t textTop = (centerY - radius) + 11;
        datapadTFTLCD.printCenteredText(ENEMY_TARGET_HEADER_A_TEXT, &Aurebesh3pt7b, centerX, textTop, &textWidth, &textHeight, DISPLAY_RING_COLOR);
        textTop = (centerY - radius) + 23;
        datapadTFTLCD.printCenteredText(ENEMY_TARGET_HEADER_B_TEXT, &Aurebesh4pt7b, centerX, textTop, &textWidth, &textHeight, DISPLAY_RING_COLOR);
        int16_t textLeft = centerX - (textWidth / 2);
        datapadTFTLCD.fillCircle(textLeft - 5, textTop, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(textLeft + textWidth + 5, textTop, 2, DISPLAY_RING_COLOR);
    }

    void drawInnerCircles(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t radius, int16_t topY)
    {
        int16_t innerCircleRadius = radius * A_INNER_CIRCLE_RELATIVE_DIAMETER;
        int16_t innerCircleCenterY = topY - (radius * A_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE) - innerCircleRadius;
        datapadTFTLCD.drawInnerCircle(centerX, innerCircleCenterY, innerCircleRadius, GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
        innerCircleRadius = radius * B_INNER_CIRCLE_RELATIVE_DIAMETER;
        innerCircleCenterY = topY - (radius * B_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE) - innerCircleRadius;
        datapadTFTLCD.drawInnerCircle(centerX, innerCircleCenterY, innerCircleRadius, GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
    }

    void drawInnerArcs(DatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t radius)
    {
        int width = 3;
        int rx = radius - 8;
        int ry = radius - 8;
        datapadTFTLCD.fillArc(x, y, 285, 15, rx, ry, width, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(x, y, 30, 15, rx, ry, width, DISPLAY_RING_COLOR);
        rx = rx - 6;
        ry = ry - 6;
        datapadTFTLCD.fillArc(x, y, 315, 4, rx, ry, width, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(x, y, 33, 4, rx, ry, width, DISPLAY_RING_COLOR);
        rx = radius - 6;
        ry = radius - 6;
        datapadTFTLCD.fillArc(x, y, 165, 10, rx, ry, 2, DISPLAY_RING_COLOR);
        int16_t topY = y + radius;
        datapadTFTLCD.fillCircle(x, topY - 19, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(x + 14, topY - 16, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(x + 28, topY - 16, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(x + 42, topY - 16, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(x - 14, topY - 16, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(x - 28, topY - 16, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(x - 42, topY - 16, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastHLine(x - 39, topY - 12, 78, DISPLAY_RING_COLOR);
        int height = 12;
        datapadTFTLCD.drawFastVerticalLine(x, topY - 19, height, 3, DISPLAY_RING_COLOR);
    }

    void drawTargetsAnimation(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t radius, int16_t topY, int16_t friendlyTargetTriangleBaseWidth, int16_t friendlyTargetTriangleHeight)
    {
        drawTargets(datapadTFTLCD, centerX, radius, topY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight, TFT_DARKGREY);
        delay(50);
        drawTargets(datapadTFTLCD, centerX, radius, topY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight, TFT_LIGHTGREY);
        delay(50);
        drawTargets(datapadTFTLCD, centerX, radius, topY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight, LIGHT_ENEMY_TARGET_COLOR);
        delay(50);
        drawTargets(datapadTFTLCD, centerX, radius, topY, friendlyTargetTriangleBaseWidth, friendlyTargetTriangleHeight, ENEMY_TARGET_COLOR);
    }
    void drawTargets(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t radius, int16_t topY, int16_t friendlyTargetTriangleBaseWidth, int16_t friendlyTargetTriangleHeight, int16_t colour)
    {
        int16_t innerCircleRadius = radius * B_INNER_CIRCLE_RELATIVE_DIAMETER;
        int16_t innerCircleCenterY = topY - (radius * B_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE) - innerCircleRadius;
        int16_t enemyTargetTriangleBaseWidth = friendlyTargetTriangleBaseWidth * 0.75;
        int16_t enemyTargetTriangleHeight = friendlyTargetTriangleHeight * 0.6;
        int16_t enemyX = centerX;
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 75, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 103, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 135, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 170, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = centerX - 25;
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 95, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 135, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 170, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = enemyX - 25;
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 75, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 125, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 155, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = enemyX - 25;
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 115, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 170, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = enemyX - 25;
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 135, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = centerX + 25;
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 100, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 140, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 170, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = enemyX + 25;
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 105, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 145, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = enemyX + 25;
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 135, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 165, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
        enemyX = enemyX + 25;
        datapadTFTLCD.fillTriangle(enemyX, innerCircleCenterY - 145, enemyTargetTriangleBaseWidth, enemyTargetTriangleHeight, colour, true);
    }
};

EnemyTargetsDDS::EnemyTargetsDDS(DatapadTFTLCD &datapadTFTLCD) : BasicGridDDS(datapadTFTLCD), _datapadTFTLCD(datapadTFTLCD) {}

void EnemyTargetsDDS::show()
{
    BasicGridDDS::show();
    EnemyTargetsDDSHelper enemyTargetsDDSHelper;
    enemyTargetsDDSHelper.drawEnemyTargets(_datapadTFTLCD);
}