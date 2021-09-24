//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DDSGraphicalUtility.h"
#include "DatapadDisplaySequenceConstants.h"

void DDSGraphicalUtility::drawInnerCircle(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t radius, int16_t offset, unsigned int colour)
{
    for (int16_t counter = 0; counter < offset; counter++)
    {
        tftlcd.drawCircle(x, y, radius - counter, colour);
    }
}

// #########################################################################
// Draw a circular or elliptical arc with a defined thickness
// #########################################################################
// x,y == coords of centre of arc
// start_angle = 0 - 359
// seg_count = number of 3 degree segments to draw (120 => 360 degree arc)
// rx = x axis radius
// yx = y axis radius
// w  = width (thickness) of arc in pixels
// colour = 16 bit colour value
// Note if rx and ry are the same then an arc of a circle is drawn
void DDSGraphicalUtility::fillArc(MCUFRIEND_kbv &tftlcd, int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)
{
    byte seg = 3; // Segments are 3 degrees wide = 120 segments for 360 degrees
    byte inc = 3; // Draw segments every 3 degrees, increase to 6 for segmented ring
    // Calculate first pair of coordinates for segment start
    float sx = cos((start_angle - 90) * DEG_TO_RAD);
    float sy = sin((start_angle - 90) * DEG_TO_RAD);
    uint16_t x0 = sx * (rx - w) + x;
    uint16_t y0 = sy * (ry - w) + y;
    uint16_t x1 = sx * rx + x;
    uint16_t y1 = sy * ry + y;
    // Draw colour blocks every inc degrees
    for (int i = start_angle; i < start_angle + seg * seg_count; i += inc)
    {
        // Calculate pair of coordinates for segment end
        float sx2 = cos((i + seg - 90) * DEG_TO_RAD);
        float sy2 = sin((i + seg - 90) * DEG_TO_RAD);
        int x2 = sx2 * (rx - w) + x;
        int y2 = sy2 * (ry - w) + y;
        int x3 = sx2 * rx + x;
        int y3 = sy2 * ry + y;
        tftlcd.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
        tftlcd.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
        // Copy segment end to sgement start for next segment
        x0 = x2;
        y0 = y2;
        x1 = x3;
        y1 = y3;
    }
}

void DDSGraphicalUtility::drawFastHorizontalLine(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t width, int16_t height, unsigned int colour)
{
    int16_t top = y - (height / 2);
    for (int16_t counter = top; counter < top + height; counter++)
    {
        tftlcd.drawFastHLine(x, counter, width, colour);
    }
}

void DDSGraphicalUtility::fillIteration(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour)
{
    int16_t newX, newWidth;
    int16_t triangleHeight = width * 0.07;
    newWidth = width - (triangleHeight * 2);
    newX = x + triangleHeight;
    tftlcd.fillRect(newX, y, newWidth, height, colour);
    int16_t triangleY1 = (y + height) - 1;
    int16_t triangleX2 = newX - triangleHeight;
    int16_t triangleY2 = (y + (height / 2)) - 1;
    tftlcd.fillTriangle(newX, y, newX, triangleY1, triangleX2, triangleY2, colour);
    newX = newX + newWidth;
    triangleX2 = newX + triangleHeight;
    tftlcd.fillTriangle(newX, y, newX, triangleY1, triangleX2, triangleY2, colour);
}

void DDSGraphicalUtility::printCenteredText(MCUFRIEND_kbv &tftlcd, String text, const GFXfont *gfxFont, int16_t x, int16_t y, uint16_t *width, uint16_t *height, unsigned int colour)
{
    int16_t x1, y1;
    uint16_t textWidth, textHeight;
    tftlcd.setFont(gfxFont);
    tftlcd.getTextBounds(text, 0, 0, &x1, &y1, &textWidth, &textHeight);
    tftlcd.setCursor(x - (textWidth / 2), y + (textHeight / 2));
    tftlcd.setTextColor(colour);
    tftlcd.println(text);
    *width = textWidth;
    *height = textHeight;
}

void DDSGraphicalUtility::fillTriangle(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t baseWidth, int16_t height, int16_t colour, boolean inverted = false)
{
    int16_t triangleX0 = x - (baseWidth / 2);
    int16_t triangleY0 = y + (height / 2);
    int16_t triangleX1 = triangleX0 + baseWidth;
    int16_t triangleX2 = triangleX0 + (baseWidth / 2);
    int16_t triangleY2 = inverted ? triangleY0 + height : triangleY0 - height;
    tftlcd.fillTriangle(triangleX0, triangleY0, triangleX1, triangleY0, triangleX2, triangleY2, colour);
}

void DDSGraphicalUtility::drawGrid(MCUFRIEND_kbv &tftlcd, int16_t centerX, int16_t centerY, int16_t radius)
{
    int16_t diameter = radius * 2;
    int16_t gridLineHeight = diameter / GRID_LINES;
    int16_t topX = centerX - radius;
    int16_t topY = centerY - radius + gridLineHeight;
    do
    {
        tftlcd.drawFastHLine(topX, topY, diameter, DISPLAY_GRID_LINE_COLOR);
        topY = topY + gridLineHeight;
    } while (topY <= (centerY + radius));
    topY = centerY - radius;
    topX = topX + gridLineHeight;
    do
    {
        tftlcd.drawFastVLine(topX, topY, diameter, DISPLAY_GRID_LINE_COLOR);
        topX = topX + gridLineHeight;
    } while (topX <= (centerX + radius));
}

void DDSGraphicalUtility::drawRoundFrame(MCUFRIEND_kbv &tftlcd, int16_t centerX, int16_t centerY, int16_t radius, int16_t shift, bool hollow)
{
    int16_t firstQuadrant = 332 + shift;
    int16_t secondQuadrant = 62 + shift;
    int16_t thirdQuadrant = 152 + shift;
    int16_t fourhtQuadrant = 242 + shift;
    int16_t innerRoundFrameHeight = 6;
    int16_t innerRoundFrameRadius = radius - 5;
    int16_t innerRoundFrameFillHeight = 3;
    int16_t innerRoundFrameFillRadius = radius - 6;
    drawInnerCircle(tftlcd, centerX, centerY, innerRoundFrameRadius, GRID_OUTER_FRAME_OFFSET, DISPLAY_RING_COLOR);
    fillArc(tftlcd, centerX, centerY, firstQuadrant, 19, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
    fillArc(tftlcd, centerX, centerY, secondQuadrant, 19, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
    fillArc(tftlcd, centerX, centerY, thirdQuadrant, 19, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
    fillArc(tftlcd, centerX, centerY, fourhtQuadrant, 19, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, DISPLAY_RING_COLOR);
    if (hollow)
    {
        fillArc(tftlcd, centerX, centerY, firstQuadrant + 1, 18, innerRoundFrameFillRadius, innerRoundFrameFillRadius, innerRoundFrameFillHeight, DISPLAY_BACK_COLOR);
        fillArc(tftlcd, centerX, centerY, secondQuadrant + 1, 8, innerRoundFrameFillRadius, innerRoundFrameFillRadius, innerRoundFrameFillHeight, DISPLAY_BACK_COLOR);
        fillArc(tftlcd, centerX, centerY, secondQuadrant + 31, 8, innerRoundFrameFillRadius, innerRoundFrameFillRadius, innerRoundFrameFillHeight, DISPLAY_BACK_COLOR);
        fillArc(tftlcd, centerX, centerY, thirdQuadrant + 1, 18, innerRoundFrameFillRadius, innerRoundFrameFillRadius, innerRoundFrameFillHeight, DISPLAY_BACK_COLOR);
        fillArc(tftlcd, centerX, centerY, fourhtQuadrant + 1, 8, innerRoundFrameFillRadius, innerRoundFrameFillRadius, innerRoundFrameFillHeight, DISPLAY_BACK_COLOR);
        fillArc(tftlcd, centerX, centerY, fourhtQuadrant + 31, 8, innerRoundFrameFillRadius, innerRoundFrameFillRadius, innerRoundFrameFillHeight, DISPLAY_BACK_COLOR);
    }
}

/**************************************************************************/
/*!
    @brief  Quarter-circle drawer with fill, used for circles and roundrects
    @param  x0       Center-point x coordinate
    @param  y0       Center-point y coordinate
    @param  r        Radius of circle
    @param  corners  Mask bits indicating which quarters we're doing
    @param  delta    Offset from center-point, used for round-rects
    @param  color    16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void DDSGraphicalUtility::fillQuarterCircle(MCUFRIEND_kbv &tftlcd, int16_t x0, int16_t y0, int16_t r, uint8_t quarter, int16_t delta, uint16_t colour)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;
    int16_t px = x;
    int16_t py = y;

    delta++;
    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        tftlcd.drawFastVLine(x0, y0 - r, r, colour);
        if (x < (y + 1))
        {
            if (quarter & 1)
                tftlcd.drawFastVLine(x0 + x, y0 - y, (2 * y + delta) / 2, colour);
            if (quarter & 2)
                tftlcd.drawFastVLine(x0 - x, y0 - y, (2 * y + delta) / 2, colour);
        }
        if (y != py)
        {
            if (quarter & 1)
                tftlcd.drawFastVLine(x0 + py, y0 - px, (2 * px + delta) / 2, colour);
            if (quarter & 2)
                tftlcd.drawFastVLine(x0 - py, y0 - px, (2 * px + delta) / 2, colour);
            py = y;
        }
        px = x;
    }
}

void DDSGraphicalUtility::drawRoundedRectangle(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t width, int16_t height, uint16_t borderColour, uint16_t colour)
{
    tftlcd.fillRoundRect(x, y, width, height, 5, colour);
    tftlcd.drawRoundRect(x, y, width, height, 5, borderColour);
}

void DDSGraphicalUtility::fillRectangle(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t width, int16_t height, int16_t borderColour, uint16_t colour)
{
    tftlcd.fillRect(x, y, width, height, colour);
    tftlcd.drawRect(x, y, width, height, borderColour);
}

void DDSGraphicalUtility::drawFastVerticalLine(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour)
{
    int16_t left = x - (width / 2);
    for (int16_t counter = left; counter < left + width; counter++)
    {
        tftlcd.drawFastVLine(counter, y, height, colour);
    }
}

void DDSGraphicalUtility::drawRectangle(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t width, int16_t height, int16_t lineWidth, uint16_t colour)
{
    x = x - (lineWidth / 2);
    for (int16_t counter = 0; counter < lineWidth; counter++)
    {
        tftlcd.drawRect(x + counter, y + counter, width - 2 * counter, height - 2 * counter, colour);
    }
}

void DDSGraphicalUtility::drawLine(MCUFRIEND_kbv &tftlcd, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t lineWidth, uint16_t colour)
{
    for (int16_t counter = 0; counter < lineWidth; counter++)
    {
        tftlcd.drawLine(x0 + counter, y0, x1 + counter, y1, colour);
    }
}

void DDSGraphicalUtility::drawVerticalTrapezoid(MCUFRIEND_kbv &tftlcd, int16_t x, int16_t y, int16_t baseWidth, int16_t topWidth, int16_t height, int16_t lineWidth, uint16_t colour, bool inverted = false)
{
    int16_t x1, y1;
    y1 = y + ((baseWidth - topWidth) / 2);
    if (!inverted)
    {
        x1 = x + height - lineWidth;
    }
    else
    {
        x = x + height - lineWidth;
        x1 = x - height + lineWidth;
    }
    drawFastVerticalLine(tftlcd, x, y, baseWidth, lineWidth, colour);
    drawFastVerticalLine(tftlcd, x1, y1, topWidth, lineWidth, colour);
    drawLine(tftlcd, x - (lineWidth / 2), y, x1 - (lineWidth / 2), y1, lineWidth, colour);
    drawLine(tftlcd, x - (lineWidth / 2), y + baseWidth - 1, x1 - (lineWidth / 2), y1 + topWidth, lineWidth, colour);
}