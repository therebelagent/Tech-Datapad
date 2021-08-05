#include "CannonPoweringUpDDS.h"
#include "DDSGraphicalUtility.h"
#include "DatapadDisplaySequenceConstants.h"
#include "Fonts/Aurebesh6pt7b.h"
#include "Fonts/Aurebesh8pt7b.h"

class CannonPoweringUpDDSHelper
{
public:
    void drawCannonPoweringUp(MCUFRIEND_kbv *tftlcd)
    {
        int16_t centerX = tftlcd->width() / 2;
        int16_t centerY = tftlcd->height() / 2;
        int16_t radius = centerX - 1;
        int16_t cannonX, cannonY;
        drawFixedScreenDetails(tftlcd, centerX, centerY, radius, &cannonX, &cannonY);
        drawDepletedCannon(tftlcd, centerX, centerY, radius, &cannonX, &cannonY);
        delay(1500);
        drawPoweredDownCannon(tftlcd, centerX, centerY, radius, &cannonX, &cannonY);
        delay(100);
        drawPoweredUpCannonAnimation(tftlcd, centerX, centerY, radius, &cannonX, &cannonY);
    }

private:
    DDSGraphicalUtility *_ddsGraphicalUtility = new DDSGraphicalUtility();

    int16_t getInnerRadius(int16_t radius) { return radius * 0.93; }

    int16_t getSmallCircleCenterY(int16_t y, int16_t radius) { return y + radius * 0.62; }

    int16_t getBannerWidth(int16_t diameter) { return diameter * 0.48; }

    int16_t getBannerHeight(int16_t diameter) { return diameter * 0.09; }

    int16_t getBannerTop(int16_t y) { return y - 80; }

    void drawDepletedCannon(MCUFRIEND_kbv *tftlcd, int16_t centerX, int16_t centerY, int16_t radius, int16_t *cannonX, int16_t *cannonY)
    {
        int16_t diameter = radius * 2;
        drawTopBanner(tftlcd, DEPLETED_CANNON_BANNER, centerX, centerY, radius, CANNON_POWERED_DOWN_COLOR);
        drawSmallInnerCircle(tftlcd, centerX, centerY, radius, CANNON_POWERED_DOWN_COLOR);
        drawCannonPoweringProgressBar(tftlcd, centerX, centerY, radius, CANNON_POWERED_DOWN_COLOR);
        drawCannon(tftlcd, *cannonX, *cannonY, diameter * CANNON_RELATIVE_WIDTH, diameter * CANNON_RELATIVE_HEIGHT, CANNON_POWERED_DOWN_COLOR);
    }

    void drawPoweredDownCannon(MCUFRIEND_kbv *tftlcd, int16_t centerX, int16_t centerY, int16_t radius, int16_t *cannonX, int16_t *cannonY)
    {
        drawTopBanner(tftlcd, POWERED_CANNON_DOWN_BANNER, centerX, centerY, radius, CANNON_POWERED_DOWN_COLOR);
    }

    void drawPoweredUpCannonAnimation(MCUFRIEND_kbv *tftlcd, int16_t centerX, int16_t centerY, int16_t radius, int16_t *cannonX, int16_t *cannonY)
    {
        int16_t diameter = radius * 2;
        drawCannonPoweringProgressBar(tftlcd, centerX, centerY, radius, CANNON_POWERED_UP_COLOR, 40);
        drawSmallInnerCircle(tftlcd, centerX, centerY, radius, CANNON_POWERED_UP_COLOR);
        drawTopBanner(tftlcd, POWERED_UP_CANNON_BANNER, centerX, centerY, radius, CANNON_POWERED_UP_COLOR);
        drawCannon(tftlcd, *cannonX, *cannonY, diameter * CANNON_RELATIVE_WIDTH, diameter * CANNON_RELATIVE_HEIGHT, CANNON_POWERED_UP_COLOR);
    }

    void drawCannonPoweringProgressBar(MCUFRIEND_kbv *tftlcd, int16_t centerX, int16_t centerY, int16_t radius, unsigned int colour, int16_t pause = 0)
    {
        int16_t innerRadius = getInnerRadius(radius) - 1;
        int16_t angle = 151;
        do
        {
            _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, angle, 1, innerRadius, innerRadius, 10, colour);
            if (pause >= 0)
            {
                delay(pause);
            }
            angle = angle - 4;
        } while (angle >= 19);
    }

    void drawSmallInnerCircle(MCUFRIEND_kbv *tftlcd, int16_t centerX, int16_t centerY, int16_t radius, unsigned int colour)
    {
        int16_t smallCircleCenterY = getSmallCircleCenterY(centerY, radius);
        int16_t smallCircleRadius = radius * 0.04;
        tftlcd->fillCircle(centerX, smallCircleCenterY, smallCircleRadius, colour);
    }

    void drawTopBanner(MCUFRIEND_kbv *tftlcd, String text, int16_t centerX, int16_t centerY, int16_t radius, unsigned int colour)
    {
        int16_t diameter = radius * 2;
        int16_t bannerWidth = getBannerWidth(diameter) - 4;
        int16_t bannerHeight = getBannerHeight(diameter) - 4;
        int16_t x = centerX - (bannerWidth / 2);
        int16_t y = getBannerTop(centerY) + 2;
        _ddsGraphicalUtility->fillIteration(tftlcd, x, y, bannerHeight, bannerWidth, colour);
        _ddsGraphicalUtility->printCenteredText(tftlcd, text, &Aurebesh8pt7b, centerX, y + (bannerHeight / 2), 0, 0, TFT_WHITE);
    }

    void drawFixedScreenDetails(MCUFRIEND_kbv *tftlcd, int16_t centerX, int16_t centerY, int16_t radius, int16_t *cannonX, int16_t *cannonY)
    {
        int16_t innerRadius = getInnerRadius(radius);
        int16_t innerCircleWidth = 9;
        int16_t innerCircleProgressBarWidth = 12;
        int16_t innerCircleDetailWidth = 4;
        int16_t innerCircleDetailRadius = innerRadius - innerCircleWidth;
        int16_t innerCircleProgressBarDetailWidth = 2;
        int16_t innerCircleProgressBarDetailRadius = innerRadius - innerCircleProgressBarWidth - 3;
        int16_t innerCircleProgressBarTipDetailRadius = innerCircleProgressBarDetailRadius - innerCircleProgressBarDetailWidth;

        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 323, 18, innerRadius, innerRadius, innerCircleWidth, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 323, 4, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);

        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 217, 35, innerRadius, innerRadius, innerCircleWidth, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 217, 6, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 250, 1, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 256, 1, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 298, 2, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 316, 2, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);

        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 157, 19, innerRadius, innerRadius, innerCircleWidth, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 174, 13, innerCircleDetailRadius, innerCircleDetailRadius, innerCircleDetailWidth, DISPLAY_RING_COLOR);

        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 20, 45, innerRadius, innerRadius, innerCircleProgressBarWidth, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 20, 45, innerCircleProgressBarDetailRadius, innerCircleProgressBarDetailRadius, innerCircleProgressBarDetailWidth, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 20, 1, innerCircleProgressBarTipDetailRadius, innerCircleProgressBarTipDetailRadius, innerCircleProgressBarDetailWidth, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, centerX, centerY, 152, 1, innerCircleProgressBarTipDetailRadius, innerCircleProgressBarTipDetailRadius, innerCircleProgressBarDetailWidth, DISPLAY_RING_COLOR);

        int16_t smallCircleCenterY = getSmallCircleCenterY(centerY, radius);
        int16_t smallCircleRadius = radius * 0.06;
        int16_t smallCircleRingRadius = (radius * 0.1);
        int16_t smallCircleArcRadius = radius * 0.15;
        tftlcd->fillCircle(centerX, smallCircleCenterY, smallCircleRadius, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, centerX, smallCircleCenterY, 0, 120, smallCircleRingRadius, smallCircleRingRadius, 3, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->fillArc(tftlcd, centerX, smallCircleCenterY, 338, 15, smallCircleArcRadius, smallCircleArcRadius, 2, DISPLAY_RING_COLOR);
        int16_t lineY = smallCircleCenterY - 30;
        int16_t lineLeft = -70;
        int16_t lineHeight = -30;
        int16_t lineWidth = 50;
        _ddsGraphicalUtility->drawFastVerticalLine(tftlcd, centerX, lineY, 10, 2, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->drawFastHorizontalLine(tftlcd, centerX, lineY, lineLeft, 2, DISPLAY_RING_COLOR);
        lineLeft = centerX + lineLeft;
        _ddsGraphicalUtility->drawFastVerticalLine(tftlcd, lineLeft, lineY, lineHeight, 2, DISPLAY_RING_COLOR);
        lineLeft = lineLeft - (lineWidth / 2);
        lineY = lineY + lineHeight;
        _ddsGraphicalUtility->drawFastHorizontalLine(tftlcd, lineLeft, lineY, lineWidth, 2, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->drawFastVerticalLine(tftlcd, lineLeft, lineY, -3, 2, DISPLAY_RING_COLOR);
        _ddsGraphicalUtility->drawFastVerticalLine(tftlcd, lineLeft + lineWidth, lineY, -3, 2, DISPLAY_RING_COLOR);

        uint16_t textWidth, textHeight;
        int16_t textLeft = centerX + 34;
        _ddsGraphicalUtility->printCenteredText(tftlcd, CANNON_POWERING_UP_FIXED_EMERCENCY, &Aurebesh6pt7b, textLeft, centerY, &textWidth, &textHeight, TFT_YELLOW);
        int16_t textTop = centerY + 15;
        _ddsGraphicalUtility->printCenteredText(tftlcd, CANNON_POWERING_UP_FIXED_POWER, &Aurebesh6pt7b, textLeft, textTop, &textWidth, &textHeight, TFT_YELLOW);

        int16_t diameter = radius * 2;
        int16_t bannerWidth = getBannerWidth(diameter);
        _ddsGraphicalUtility->fillIteration(tftlcd, centerX - (bannerWidth / 2), getBannerTop(centerY), getBannerHeight(diameter), bannerWidth, TFT_WHITE);

        *cannonX = lineLeft + (lineWidth / 2);
        *cannonY = lineY - (diameter * 0.03);
    }

    void drawCannon(MCUFRIEND_kbv *tftlcd, int16_t x, int16_t y, int16_t width, int16_t height, unsigned int colour)
    {
        int16_t shapeWidth = width * 0.19;
        int16_t shapeHeight = height * 0.1;
        int16_t shapeY = y - shapeHeight;
        int16_t shapeLeft = x - (shapeWidth / 2);
        tftlcd->fillRect(shapeLeft, shapeY, shapeWidth, shapeHeight, colour);
        tftlcd->drawRect(shapeLeft, shapeY, shapeWidth, shapeHeight, DISPLAY_RING_COLOR);

        shapeHeight = width * 0.13;
        _ddsGraphicalUtility->fillQuarterCircle(tftlcd, x, shapeY, shapeHeight, 3, 0, colour);
        _ddsGraphicalUtility->fillArc(tftlcd, x, shapeY, 270, 60, shapeHeight, shapeHeight, 1, DISPLAY_RING_COLOR);
        shapeLeft = x - shapeHeight;
        tftlcd->drawFastHLine(shapeLeft, shapeY, shapeHeight * 2, DISPLAY_RING_COLOR);

        shapeY = shapeY - shapeHeight + (height * 0.06);
        shapeHeight = height * 0.53;
        shapeWidth = width * 0.2;
        shapeY = shapeY - shapeHeight;
        shapeLeft = x - (shapeWidth / 2);
        tftlcd->fillRect(shapeLeft, shapeY, shapeWidth, shapeHeight, colour);
        tftlcd->drawRect(shapeLeft, shapeY, shapeWidth, shapeHeight, DISPLAY_RING_COLOR);

        shapeWidth = width * 0.1;
        shapeHeight = shapeHeight - 1;
        tftlcd->fillTriangle(shapeLeft - shapeWidth, shapeY + shapeHeight, shapeLeft, shapeY, shapeLeft, shapeY + shapeHeight, colour);
        tftlcd->drawTriangle(shapeLeft - shapeWidth, shapeY + shapeHeight, shapeLeft, shapeY, shapeLeft, shapeY + shapeHeight, DISPLAY_RING_COLOR);
        tftlcd->drawFastVLine(shapeLeft, shapeY + 1, shapeHeight - 1, colour);

        shapeLeft = shapeLeft + width * 0.2;
        shapeWidth = width * 0.02;
        shapeHeight = height * 0.17;
        tftlcd->fillRect(shapeLeft, (shapeY + (height * 0.27) / 2) - (shapeHeight / 2), shapeWidth, shapeHeight, colour);
        tftlcd->drawRect(shapeLeft, (shapeY + (height * 0.27) / 2) - (shapeHeight / 2), shapeWidth, shapeHeight, DISPLAY_RING_COLOR);

        shapeLeft = shapeLeft + shapeWidth;
        shapeWidth = width * 0.65;
        int16_t shapeOffset = (height * 0.27 - (height * 0.1)) / 2;
        tftlcd->fillTriangle(shapeLeft, shapeY, shapeLeft + shapeWidth, shapeY + shapeOffset, shapeLeft, shapeY + shapeOffset, colour);
        tftlcd->drawLine(shapeLeft, shapeY, shapeLeft + shapeWidth, shapeY + shapeOffset, DISPLAY_RING_COLOR);

        shapeHeight = height * 0.1;
        shapeY = shapeY + shapeOffset;
        tftlcd->fillRect(shapeLeft, shapeY, shapeWidth, shapeHeight, colour);
        tftlcd->drawFastVLine(shapeLeft + shapeWidth, shapeY, shapeHeight, DISPLAY_RING_COLOR);

        shapeY = shapeY + shapeHeight;
        tftlcd->fillTriangle(shapeLeft, shapeY, shapeLeft + shapeWidth, shapeY, shapeLeft, shapeY + shapeOffset, colour);
        tftlcd->drawLine(shapeLeft, shapeY + shapeOffset, shapeLeft + shapeWidth, shapeY, DISPLAY_RING_COLOR);
    }
};

CannonPoweringUpDDS::CannonPoweringUpDDS(MCUFRIEND_kbv *tftlcd) : BasicGridDDS(tftlcd) { _tftlcd = tftlcd; }

void CannonPoweringUpDDS::show()
{
    BasicGridDDS::show();
    CannonPoweringUpDDSHelper *cannonPoweringUpDDSHelper = new CannonPoweringUpDDSHelper();
    cannonPoweringUpDDSHelper->drawCannonPoweringUp(_tftlcd);
}