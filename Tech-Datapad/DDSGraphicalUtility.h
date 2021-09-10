//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef DDSGraphicalUtility_h
#define DDSGraphicalUtility_h

#include "MCUFRIEND_kbv.h"

class DDSGraphicalUtility
{
public:
    void drawInnerCircle(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t radius, int16_t offset, unsigned int colour);
    void fillArc(MCUFRIEND_kbv &tftlcd, int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour);
    void drawFastVerticalLine(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour);
    void drawFastHorizontalLine(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t width, int16_t height, unsigned int colour);
    void fillIteration(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour);
    void printCenteredText(MCUFRIEND_kbv &tftlcd, String text, const GFXfont *gfxFont, int16_t x, int16_t y, uint16_t *width, uint16_t *height, unsigned int colour);
    void fillTriangle(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t baseWidth, int16_t height, int16_t colour, boolean inverted = false);
    void drawGrid(MCUFRIEND_kbv &tftlcd, int16_t centerX, int16_t centerY, int16_t radius);
    void drawRoundFrame(MCUFRIEND_kbv &tftlcd, int16_t centerX, int16_t centerY, int16_t radius, int16_t shift, bool hollow);
    void fillQuarterCircle(MCUFRIEND_kbv &tftlcd, int16_t x0, int16_t y0, int16_t r, uint8_t quarter, int16_t delta, uint16_t colour);
    void drawRectangle(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t width, int16_t height, int16_t lineWidth, uint16_t colour);
    void drawLine(MCUFRIEND_kbv &tftlcd, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t lineWidth, uint16_t colour);
};

#endif