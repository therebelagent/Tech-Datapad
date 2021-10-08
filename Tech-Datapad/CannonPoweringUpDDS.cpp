//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "CannonPoweringUpDDS.h"
#include "Fonts/Aurebesh6pt7b.h"
#include "Fonts/Aurebesh8pt7b.h"
#include "Fonts/Aurebesh9pt7b.h"

class CannonPoweringUpDDSHelper
{
public:
    void drawCannonPoweringUp(DatapadTFTLCD &datapadTFTLCD)
    {
        int16_t centerX = datapadTFTLCD.width() / 2;
        int16_t centerY = datapadTFTLCD.height() / 2;
        int16_t radius = centerX - 1;
        int16_t cannonX, cannonY;
        drawFixedScreenDetails(datapadTFTLCD, centerX, centerY, radius, cannonX, cannonY);
        drawDepletedCannon(datapadTFTLCD, centerX, centerY, radius, cannonX, cannonY);
        delay(1500);
        drawPoweredDownCannon(datapadTFTLCD, centerX, centerY, radius, cannonX, cannonY);
        delay(100);
        drawPoweredUpCannonAnimation(datapadTFTLCD, centerX, centerY, radius, cannonX, cannonY);
    }

private:
    int16_t getInnerRadius(int16_t radius) { return radius * 0.93; }

    int16_t getSmallCircleCenterY(int16_t y, int16_t radius) { return y + radius * 0.62; }

    int16_t getBannerWidth(int16_t diameter) { return diameter * 0.48; }

    int16_t getBannerHeight(int16_t diameter) { return diameter * 0.09; }

    int16_t getBannerTop(int16_t y) { return y - 80; }

    void drawDepletedCannon(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius, int16_t &cannonX, int16_t &cannonY)
    {
        int16_t diameter = radius * 2;
        drawTopBanner(datapadTFTLCD, DEPLETED_CANNON_BANNER, &Aurebesh8pt7b, centerX, centerY, radius, CANNON_POWERED_DOWN_COLOR);
        drawSmallInnerCircle(datapadTFTLCD, centerX, centerY, radius, CANNON_POWERED_DOWN_COLOR);
        drawCannonPoweringProgressBar(datapadTFTLCD, centerX, centerY, radius, CANNON_POWERED_DOWN_COLOR);
        drawCannon(datapadTFTLCD, cannonX, cannonY, diameter * CANNON_RELATIVE_WIDTH, diameter * CANNON_RELATIVE_HEIGHT, CANNON_POWERED_DOWN_COLOR);
    }

    void drawPoweredDownCannon(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius, int16_t &cannonX, int16_t &cannonY)
    {
        drawTopBanner(datapadTFTLCD, POWERED_CANNON_DOWN_BANNER, &Aurebesh8pt7b, centerX, centerY, radius, CANNON_POWERED_DOWN_COLOR);
    }

    void drawPoweredUpCannonAnimation(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius, int16_t &cannonX, int16_t &cannonY)
    {
        int16_t diameter = radius * 2;
        drawCannonPoweringProgressBar(datapadTFTLCD, centerX, centerY, radius, CANNON_POWERED_UP_COLOR, 40);
        drawSmallInnerCircle(datapadTFTLCD, centerX, centerY, radius, CANNON_POWERED_UP_COLOR);
        drawTopBanner(datapadTFTLCD, POWERED_UP_CANNON_BANNER, &Aurebesh9pt7b, centerX, centerY, radius, CANNON_POWERED_UP_COLOR);
        drawCannon(datapadTFTLCD, cannonX, cannonY, diameter * CANNON_RELATIVE_WIDTH, diameter * CANNON_RELATIVE_HEIGHT, CANNON_POWERED_UP_COLOR);
    }

    void drawCannonPoweringProgressBar(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius, unsigned int colour, int16_t pause = 0)
    {
        int16_t innerRadius = getInnerRadius(radius) - 1;
        int16_t angle = 151;
        do
        {
            datapadTFTLCD.fillArc(centerX, centerY, angle, 1, innerRadius, innerRadius, 10, colour);
            if (pause >= 0)
            {
                delay(pause);
            }
            angle = angle - 4;
        } while (angle >= 19);
    }

    void drawSmallInnerCircle(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius, uint16_t colour)
    {
        int16_t smallCircleCenterY = getSmallCircleCenterY(centerY, radius);
        int16_t smallCircleRadius = radius * 0.04;
        datapadTFTLCD.fillCircle(centerX, smallCircleCenterY, smallCircleRadius, colour);
    }

    void drawTopBanner(DatapadTFTLCD &datapadTFTLCD, const char *text, const GFXfont *gfxFont, int16_t centerX, int16_t centerY, int16_t radius, uint16_t colour)
    {
        int16_t diameter = radius * 2;
        datapadTFTLCD.drawBanner(centerX, getBannerTop(centerY) + 2, getBannerHeight(diameter), getBannerWidth(diameter), colour, text, gfxFont);
    }

    void drawFixedScreenDetails(DatapadTFTLCD &datapadTFTLCD, int16_t centerX, int16_t centerY, int16_t radius, int16_t &cannonX, int16_t &cannonY)
    {
        int16_t innerRadius = getInnerRadius(radius);
        int16_t innerCircleWidth = 9;
        int16_t innerCircleProgressBarWidth = 12;
        int16_t innerCircleDetailWidth = 4;
        int16_t innerCircleDetailRadius = innerRadius - innerCircleWidth;
        int16_t innerCircleProgressBarDetailWidth = 2;
        int16_t innerCircleProgressBarDetailRadius = innerRadius - innerCircleProgressBarWidth - 3;
        int16_t innerCircleProgressBarTipDetailRadius = innerCircleProgressBarDetailRadius - innerCircleProgressBarDetailWidth;

        datapadTFTLCD.fillArc(centerX, centerY, 323, 18, innerRadius, innerRadius, innerCircleWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 323, 4, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);

        datapadTFTLCD.fillArc(centerX, centerY, 217, 35, innerRadius, innerRadius, innerCircleWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 217, 6, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 250, 1, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 256, 1, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 298, 2, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 316, 2, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);

        datapadTFTLCD.fillArc(centerX, centerY, 157, 19, innerRadius, innerRadius, innerCircleWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 174, 13, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);

        datapadTFTLCD.fillArc(centerX, centerY, 20, 45, innerRadius, innerRadius, innerCircleProgressBarWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 20, 45, innerCircleProgressBarDetailRadius, innerCircleProgressBarDetailRadius, innerCircleProgressBarDetailWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 20, 1, innerCircleProgressBarTipDetailRadius, innerCircleProgressBarTipDetailRadius, innerCircleProgressBarDetailWidth, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, centerY, 152, 1, innerCircleProgressBarTipDetailRadius, innerCircleProgressBarTipDetailRadius, innerCircleProgressBarDetailWidth, DISPLAY_RING_COLOR);

        int16_t smallCircleCenterY = getSmallCircleCenterY(centerY, radius);
        int16_t smallCircleRadius = radius * 0.06;
        int16_t smallCircleRingRadius = (radius * 0.1);
        int16_t smallCircleArcRadius = radius * 0.15;
        datapadTFTLCD.fillCircle(centerX, smallCircleCenterY, smallCircleRadius, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, smallCircleCenterY, 0, 120, smallCircleRingRadius, smallCircleRingRadius, 3, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillArc(centerX, smallCircleCenterY, 338, 15, smallCircleArcRadius, smallCircleArcRadius, 2, DISPLAY_RING_COLOR);
        int16_t lineY = smallCircleCenterY - 30;
        int16_t lineLeft = -70;
        int16_t lineHeight = -30;
        int16_t lineWidth = 50;
        datapadTFTLCD.drawFastVerticalLine(centerX, lineY, 10, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastHorizontalLine(centerX, lineY, lineLeft, 2, DISPLAY_RING_COLOR);
        lineLeft = centerX + lineLeft;
        datapadTFTLCD.drawFastVerticalLine(lineLeft, lineY, lineHeight, 2, DISPLAY_RING_COLOR);
        lineLeft = lineLeft - (lineWidth / 2);
        lineY = lineY + lineHeight;
        datapadTFTLCD.drawFastHorizontalLine(lineLeft, lineY, lineWidth, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(lineLeft, lineY, -3, 2, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVerticalLine(lineLeft + lineWidth, lineY, -3, 2, DISPLAY_RING_COLOR);
        int16_t textLeft = centerX + 34;
        datapadTFTLCD.printCenteredText(CANNON_POWERING_UP_FIXED_EMERCENCY, &Aurebesh6pt7b, textLeft, centerY, TFT_YELLOW);
        int16_t textTop = centerY + 15;
        datapadTFTLCD.printCenteredText(CANNON_POWERING_UP_FIXED_POWER, &Aurebesh6pt7b, textLeft, textTop, TFT_YELLOW);
        int16_t diameter = radius * 2;
        cannonX = lineLeft + (lineWidth / 2);
        cannonY = lineY - (diameter * 0.03);
    }

    void drawCannon(DatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t width, int16_t height, uint16_t colour)
    {
        int16_t shapeWidth = width * 0.19;
        int16_t shapeHeight = height * 0.1;
        int16_t shapeY = y - shapeHeight;
        int16_t shapeLeft = x - (shapeWidth / 2);
        datapadTFTLCD.fillRect(shapeLeft, shapeY, shapeWidth, shapeHeight, colour);
        datapadTFTLCD.drawRect(shapeLeft, shapeY, shapeWidth, shapeHeight, DISPLAY_RING_COLOR);

        shapeHeight = width * 0.13;
        datapadTFTLCD.fillQuarterCircle(x, shapeY, shapeHeight, 3, 0, colour);
        datapadTFTLCD.fillArc(x, shapeY, 270, 60, shapeHeight, shapeHeight, 1, DISPLAY_RING_COLOR);
        shapeLeft = x - shapeHeight;
        datapadTFTLCD.drawFastHLine(shapeLeft, shapeY, shapeHeight * 2, DISPLAY_RING_COLOR);

        shapeY = shapeY - shapeHeight + (height * 0.06);
        shapeHeight = height * 0.53;
        shapeWidth = width * 0.2;
        shapeY = shapeY - shapeHeight;
        shapeLeft = x - (shapeWidth / 2);
        datapadTFTLCD.fillRect(shapeLeft, shapeY, shapeWidth, shapeHeight, colour);
        datapadTFTLCD.drawRect(shapeLeft, shapeY, shapeWidth, shapeHeight, DISPLAY_RING_COLOR);

        shapeWidth = width * 0.1;
        shapeHeight = shapeHeight - 1;
        datapadTFTLCD.fillTriangle(shapeLeft - shapeWidth, shapeY + shapeHeight, shapeLeft, shapeY, shapeLeft, shapeY + shapeHeight, colour);
        datapadTFTLCD.drawTriangle(shapeLeft - shapeWidth, shapeY + shapeHeight, shapeLeft, shapeY, shapeLeft, shapeY + shapeHeight, DISPLAY_RING_COLOR);
        datapadTFTLCD.drawFastVLine(shapeLeft, shapeY + 1, shapeHeight - 1, colour);

        shapeLeft = shapeLeft + width * 0.2;
        shapeWidth = width * 0.02;
        shapeHeight = height * 0.17;
        datapadTFTLCD.fillRect(shapeLeft, (shapeY + (height * 0.27) / 2) - (shapeHeight / 2), shapeWidth, shapeHeight, colour);
        datapadTFTLCD.drawRect(shapeLeft, (shapeY + (height * 0.27) / 2) - (shapeHeight / 2), shapeWidth, shapeHeight, DISPLAY_RING_COLOR);

        shapeLeft = shapeLeft + shapeWidth;
        shapeWidth = width * 0.65;
        int16_t shapeOffset = (height * 0.27 - (height * 0.1)) / 2;
        datapadTFTLCD.fillTriangle(shapeLeft, shapeY, shapeLeft + shapeWidth, shapeY + shapeOffset, shapeLeft, shapeY + shapeOffset, colour);
        datapadTFTLCD.drawLine(shapeLeft, shapeY, shapeLeft + shapeWidth, shapeY + shapeOffset, DISPLAY_RING_COLOR);

        shapeHeight = height * 0.1;
        shapeY = shapeY + shapeOffset;
        datapadTFTLCD.fillRect(shapeLeft, shapeY, shapeWidth, shapeHeight, colour);
        datapadTFTLCD.drawFastVLine(shapeLeft + shapeWidth, shapeY, shapeHeight, DISPLAY_RING_COLOR);

        shapeY = shapeY + shapeHeight;
        datapadTFTLCD.fillTriangle(shapeLeft, shapeY, shapeLeft + shapeWidth, shapeY, shapeLeft, shapeY + shapeOffset, colour);
        datapadTFTLCD.drawLine(shapeLeft, shapeY + shapeOffset, shapeLeft + shapeWidth, shapeY, DISPLAY_RING_COLOR);
    }
};

CannonPoweringUpDDS::CannonPoweringUpDDS(DatapadTFTLCD &datapadTFTLCD) : BasicGridDDS(datapadTFTLCD), _datapadTFTLCD(datapadTFTLCD) {}

void CannonPoweringUpDDS::show()
{
    BasicGridDDS::show();
    CannonPoweringUpDDSHelper cannonPoweringUpDDSHelper;
    cannonPoweringUpDDSHelper.drawCannonPoweringUp(_datapadTFTLCD);
}