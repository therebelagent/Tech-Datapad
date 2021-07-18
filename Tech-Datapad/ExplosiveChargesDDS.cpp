#include "ExplosiveChargesDDS.h"
#include "DDSGraphicalUtility.h"
#include "DatapadDisplaySequenceConstants.h"

class ExplosiveChargesDDSHelper
{
public:
    void drawExplosiveChargesDisplaySecuence(MCUFRIEND_kbv *tftlcd)
    {
        int16_t centerX = tftlcd->width() / 2;
        int16_t centerY = tftlcd->height() / 2;
        int16_t radius = centerX - 5;
        drawFirstPhaseTargetDisplay(tftlcd, radius, centerX, centerY);
        delay(1000);
        drawSecondPhaseTargetDisplay(tftlcd, radius, centerX, centerY);
        delay(1000);
        drawThirdPhaseTargetDisplay(tftlcd, radius, centerX, centerY);
    }

private:
    DDSGraphicalUtility *_ddsGraphicalUtility = new DDSGraphicalUtility();

    void drawFirstPhaseTargetDisplay(MCUFRIEND_kbv *tftlcd, int16_t radius, int16_t centerX, int16_t centerY)
    {
        tftlcd->fillCircle(centerX, centerY, radius, LIGHT_BLUE_CIRCLE_COLOR);
        drawBullseye(tftlcd, radius, centerX, centerY);
        tftlcd->fillCircle(centerX, centerY, radius * BULLSEYE_SECOND_CIRCLE_RELATIVE_DIAMETER, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
        int16_t crosshairLenght = radius * BULLSEYE_THIRD_CIRCLE_RELATIVE_DIAMETER;
        drawCrosshair(tftlcd, crosshairLenght, centerX, centerY, DISPLAY_RING_COLOR, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
        _ddsGraphicalUtility->drawInnerCircle(tftlcd, centerX, centerY, crosshairLenght, BULLSEYE_OFFSET, DISPLAY_RING_COLOR);
        drawWhiteVerticalArrows(tftlcd, radius, centerX, centerY);
    }

    void drawSecondPhaseTargetDisplay(MCUFRIEND_kbv *tftlcd, int16_t radius, int16_t centerX, int16_t centerY)
    {
        tftlcd->fillCircle(centerX, centerY, radius * BULLSEYE_SECOND_CIRCLE_RELATIVE_DIAMETER, BLUE_INNER_CIRCLE_COLOR);
        tftlcd->fillCircle(centerX, centerY, radius * BULLSEYE_THIRD_CIRCLE_RELATIVE_DIAMETER, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
    }

    void drawThirdPhaseTargetDisplay(MCUFRIEND_kbv *tftlcd, int16_t radius, int16_t centerX, int16_t centerY)
    {
        tftlcd->fillCircle(centerX, centerY, radius * BULLSEYE_SECOND_CIRCLE_RELATIVE_DIAMETER, DISPLAY_RING_COLOR);
        tftlcd->fillCircle(centerX, centerY, radius * BULLSEYE_THIRD_CIRCLE_RELATIVE_DIAMETER, DISPLAY_RING_COLOR);
        drawBullseye(tftlcd, radius, centerX, centerY);
        drawWhiteVerticalArrows(tftlcd, radius, centerX, centerY);
        drawCrosshair(tftlcd, radius * BULLSEYE_THIRD_CIRCLE_RELATIVE_DIAMETER, centerX, centerY, DARK_GREEN_BULLSEYE_CIRCLE_COLOR, DISPLAY_RING_COLOR);
    }

    void drawCrosshair(MCUFRIEND_kbv *tftlcd, int16_t crosshairLenght, int16_t centerX, int16_t centerY, int16_t crosshairColor, int16_t centerColor)
    {
        tftlcd->drawLine(centerX - crosshairLenght, centerY - crosshairLenght, centerX + crosshairLenght, centerY + crosshairLenght, crosshairColor);
        tftlcd->drawLine(centerX - crosshairLenght, centerY + crosshairLenght, centerX + crosshairLenght, centerY - crosshairLenght, crosshairColor);
        tftlcd->fillCircle(centerX, centerY, crosshairLenght - BULLSEYE_OFFSET, centerColor);
    }

    void drawBullseye(MCUFRIEND_kbv *tftlcd, int16_t radius, int16_t centerX, int16_t centerY)
    {
        int16_t innerCircleRadius = radius * BULLSEYE_BORDER_CIRCLE_RELATIVE_DIAMETER;
        _ddsGraphicalUtility->drawInnerCircle(tftlcd, centerX, centerY, innerCircleRadius, BULLSEYE_OFFSET, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
        innerCircleRadius = radius * BULLSEYE_FIRST_CIRCLE_RELATIVE_DIAMETER;
        _ddsGraphicalUtility->drawInnerCircle(tftlcd, centerX, centerY, innerCircleRadius, BULLSEYE_OFFSET, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
        innerCircleRadius = radius * BULLSEYE_SECOND_CIRCLE_RELATIVE_DIAMETER;
        _ddsGraphicalUtility->drawInnerCircle(tftlcd, centerX, centerY, innerCircleRadius, BULLSEYE_OFFSET, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
        innerCircleRadius = radius * BULLSEYE_THIRD_CIRCLE_RELATIVE_DIAMETER;
        _ddsGraphicalUtility->drawInnerCircle(tftlcd, centerX, centerY, innerCircleRadius, BULLSEYE_OFFSET, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
    }

    void drawWhiteVerticalArrows(MCUFRIEND_kbv *tftlcd, int16_t radius, int16_t centerX, int16_t centerY)
    {
        int16_t diameter = radius * 2;
        int16_t triangleBaseWidth = diameter * 0.06;
        int16_t triangleHeight = diameter * 0.09;
        int16_t triangleBaseOffset = 3;
        _ddsGraphicalUtility->fillTriangle(tftlcd, centerX, centerY - radius - (triangleHeight / 2) - triangleBaseOffset, triangleBaseWidth, triangleHeight, TFT_WHITE, true);
        _ddsGraphicalUtility->fillTriangle(tftlcd, centerX, centerY + radius - (triangleHeight / 2) + triangleBaseOffset, triangleBaseWidth, triangleHeight, TFT_WHITE);
    }
};

ExplosiveChargesDDS::ExplosiveChargesDDS(MCUFRIEND_kbv *tftlcd) : DatapadDisplaySequence(tftlcd) { _tftlcd = tftlcd; };

void ExplosiveChargesDDS::show()
{
    ExplosiveChargesDDSHelper *explosiveChargesDDSHelper = new ExplosiveChargesDDSHelper();
    explosiveChargesDDSHelper->drawExplosiveChargesDisplaySecuence(_tftlcd);
}