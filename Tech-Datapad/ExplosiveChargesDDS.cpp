//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "ExplosiveChargesDDS.h"

class ExplosiveChargesDDSHelper
{
public:
    void drawExplosiveChargesDisplaySecuence(DatapadTFTLCD &datapadTFTLCD)
    {
        int16_t centerX = datapadTFTLCD.width() / 2;
        int16_t centerY = datapadTFTLCD.height() / 2;
        int16_t radius = centerX - 5;
        drawFirstPhaseTargetDisplay(datapadTFTLCD, radius, centerX, centerY);
        delay(1000);
        drawSecondPhaseTargetDisplay(datapadTFTLCD, radius, centerX, centerY);
        delay(1000);
        drawThirdPhaseTargetDisplay(datapadTFTLCD, radius, centerX, centerY);
    }

private:
    void drawFirstPhaseTargetDisplay(DatapadTFTLCD &datapadTFTLCD, int16_t radius, int16_t centerX, int16_t centerY)
    {
        datapadTFTLCD.fillCircle(centerX, centerY, radius, LIGHT_BLUE_CIRCLE_COLOR);
        drawBullseye(datapadTFTLCD, radius, centerX, centerY);
        datapadTFTLCD.fillCircle(centerX, centerY, radius * BULLSEYE_SECOND_CIRCLE_RELATIVE_DIAMETER, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
        int16_t crosshairLenght = radius * BULLSEYE_THIRD_CIRCLE_RELATIVE_DIAMETER;
        drawCrosshair(datapadTFTLCD, crosshairLenght, centerX, centerY, DISPLAY_RING_COLOR, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
        datapadTFTLCD.drawInnerCircle(centerX, centerY, crosshairLenght, BULLSEYE_OFFSET, DISPLAY_RING_COLOR);
        drawWhiteVerticalArrows(datapadTFTLCD, radius, centerX, centerY);
    }

    void drawSecondPhaseTargetDisplay(DatapadTFTLCD &datapadTFTLCD, int16_t radius, int16_t centerX, int16_t centerY)
    {
        datapadTFTLCD.fillCircle(centerX, centerY, radius * BULLSEYE_SECOND_CIRCLE_RELATIVE_DIAMETER, BLUE_INNER_CIRCLE_COLOR);
        datapadTFTLCD.fillCircle(centerX, centerY, radius * BULLSEYE_THIRD_CIRCLE_RELATIVE_DIAMETER, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
    }

    void drawThirdPhaseTargetDisplay(DatapadTFTLCD &datapadTFTLCD, int16_t radius, int16_t centerX, int16_t centerY)
    {
        datapadTFTLCD.fillCircle(centerX, centerY, radius * BULLSEYE_SECOND_CIRCLE_RELATIVE_DIAMETER, DISPLAY_RING_COLOR);
        datapadTFTLCD.fillCircle(centerX, centerY, radius * BULLSEYE_THIRD_CIRCLE_RELATIVE_DIAMETER, DISPLAY_RING_COLOR);
        drawBullseye(datapadTFTLCD, radius, centerX, centerY);
        drawWhiteVerticalArrows(datapadTFTLCD, radius, centerX, centerY);
        drawCrosshair(datapadTFTLCD, radius * BULLSEYE_THIRD_CIRCLE_RELATIVE_DIAMETER, centerX, centerY, DARK_GREEN_BULLSEYE_CIRCLE_COLOR, DISPLAY_RING_COLOR);
    }

    void drawCrosshair(DatapadTFTLCD &datapadTFTLCD, int16_t crosshairLenght, int16_t centerX, int16_t centerY, int16_t crosshairColor, int16_t centerColor)
    {
        datapadTFTLCD.drawLine(centerX - crosshairLenght, centerY - crosshairLenght, centerX + crosshairLenght, centerY + crosshairLenght, 2, crosshairColor);
        datapadTFTLCD.drawLine(centerX - crosshairLenght, centerY + crosshairLenght, centerX + crosshairLenght, centerY - crosshairLenght, 2, crosshairColor);
        datapadTFTLCD.fillCircle(centerX, centerY, crosshairLenght - BULLSEYE_OFFSET, centerColor);
    }

    void drawBullseye(DatapadTFTLCD &datapadTFTLCD, int16_t radius, int16_t centerX, int16_t centerY)
    {
        int16_t innerCircleRadius = radius * BULLSEYE_BORDER_CIRCLE_RELATIVE_DIAMETER;
        datapadTFTLCD.drawInnerCircle(centerX, centerY, innerCircleRadius, BULLSEYE_OFFSET, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
        innerCircleRadius = radius * BULLSEYE_FIRST_CIRCLE_RELATIVE_DIAMETER;
        datapadTFTLCD.drawInnerCircle(centerX, centerY, innerCircleRadius, BULLSEYE_OFFSET, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
        innerCircleRadius = radius * BULLSEYE_SECOND_CIRCLE_RELATIVE_DIAMETER;
        datapadTFTLCD.drawInnerCircle(centerX, centerY, innerCircleRadius, BULLSEYE_OFFSET, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
        innerCircleRadius = radius * BULLSEYE_THIRD_CIRCLE_RELATIVE_DIAMETER;
        datapadTFTLCD.drawInnerCircle(centerX, centerY, innerCircleRadius, BULLSEYE_OFFSET, DARK_GREEN_BULLSEYE_CIRCLE_COLOR);
    }

    void drawWhiteVerticalArrows(DatapadTFTLCD &datapadTFTLCD, int16_t radius, int16_t centerX, int16_t centerY)
    {
        int16_t diameter = radius * 2;
        int16_t triangleBaseWidth = diameter * 0.06;
        int16_t triangleHeight = diameter * 0.09;
        int16_t triangleBaseOffset = 3;
        datapadTFTLCD.fillTriangle(centerX, centerY - radius - (triangleHeight / 2) - triangleBaseOffset, triangleBaseWidth, triangleHeight, TFT_WHITE, true);
        datapadTFTLCD.fillTriangle(centerX, centerY + radius - (triangleHeight / 2) + triangleBaseOffset, triangleBaseWidth, triangleHeight, TFT_WHITE);
    }
};

ExplosiveChargesDDS::ExplosiveChargesDDS(DatapadTFTLCD &datapadTFTLCD) : DatapadDisplaySequence(datapadTFTLCD), _datapadTFTLCD(datapadTFTLCD) {}

void ExplosiveChargesDDS::show()
{
    ExplosiveChargesDDSHelper explosiveChargesDDSHelper;
    explosiveChargesDDSHelper.drawExplosiveChargesDisplaySecuence(_datapadTFTLCD);
}