#include "DDSGraphicalUtility.h"
#include "DatapadDisplaySequenceConstants.h"

void DDSGraphicalUtility::drawInnerCircle(MCUFRIEND_kbv *tftlcd, int16_t x, int16_t y, int16_t radius, int16_t offset, unsigned int colour)
{
    for (int16_t counter = 0; counter < offset; counter++)
    {
        tftlcd->drawCircle(x, y, radius - counter, colour);
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
void DDSGraphicalUtility::fillArc(MCUFRIEND_kbv *tftlcd, int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)
{
    byte seg = 3; // Segments are 3 degrees wide = 120 segments for 360 degrees
    byte inc = 3; // Draw segments every 3 degrees, increase to 6 for segmented ring
    // Calculate first pair of coordinates for segment start
    float sx = cos((start_angle - 90) * DEG2RAD);
    float sy = sin((start_angle - 90) * DEG2RAD);
    uint16_t x0 = sx * (rx - w) + x;
    uint16_t y0 = sy * (ry - w) + y;
    uint16_t x1 = sx * rx + x;
    uint16_t y1 = sy * ry + y;
    // Draw colour blocks every inc degrees
    for (int i = start_angle; i < start_angle + seg * seg_count; i += inc)
    {
        // Calculate pair of coordinates for segment end
        float sx2 = cos((i + seg - 90) * DEG2RAD);
        float sy2 = sin((i + seg - 90) * DEG2RAD);
        int x2 = sx2 * (rx - w) + x;
        int y2 = sy2 * (ry - w) + y;
        int x3 = sx2 * rx + x;
        int y3 = sy2 * ry + y;
        tftlcd->fillTriangle(x0, y0, x1, y1, x2, y2, colour);
        tftlcd->fillTriangle(x1, y1, x2, y2, x3, y3, colour);
        // Copy segment end to sgement start for next segment
        x0 = x2;
        y0 = y2;
        x1 = x3;
        y1 = y3;
    }
}

void DDSGraphicalUtility::drawFastVerticalLine(MCUFRIEND_kbv *tftlcd, int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour)
{
    int16_t left = x - (width / 2);
    for (int16_t counter = left; counter < left + width; counter++)
    {
        tftlcd->drawFastVLine(counter, y, height, colour);
    }
}

void DDSGraphicalUtility::drawFastHorizontalLine(MCUFRIEND_kbv *tftlcd, int16_t x, int16_t y, int16_t width, int16_t height, unsigned int colour)
{
    int16_t top = y - (height / 2);
    for (int16_t counter = top; counter < top + height; counter++)
    {
        tftlcd->drawFastHLine(x, counter, width, colour);
    }
}

void DDSGraphicalUtility::fillIteration(MCUFRIEND_kbv *tftlcd, int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour)
{
    int16_t newX, newWidth;
    int16_t triangleHeight = width * 0.07;
    newWidth = width - (triangleHeight * 2);
    newX = x + triangleHeight;
    tftlcd->fillRect(newX, y, newWidth, height, colour);
    int16_t triangleY1 = (y + height) - 1;
    int16_t triangleX2 = newX - triangleHeight;
    int16_t triangleY2 = (y + (height / 2)) - 1;
    tftlcd->fillTriangle(newX, y, newX, triangleY1, triangleX2, triangleY2, colour);
    newX = newX + newWidth;
    triangleX2 = newX + triangleHeight;
    tftlcd->fillTriangle(newX, y, newX, triangleY1, triangleX2, triangleY2, colour);
}

void DDSGraphicalUtility::printCenteredText(MCUFRIEND_kbv *tftlcd, String text, const GFXfont *gfxFont, int16_t x, int16_t y, uint16_t *width, uint16_t *height, unsigned int colour)
{
    int16_t x1, y1;
    uint16_t textWidth, textHeight;
    tftlcd->setFont(gfxFont);
    tftlcd->getTextBounds(text, 0, 0, &x1, &y1, &textWidth, &textHeight);
    tftlcd->setCursor(x - (textWidth / 2), y + (textHeight / 2));
    tftlcd->setTextColor(colour);
    tftlcd->println(text);
    *width = textWidth;
    *height = textHeight;
}

void DDSGraphicalUtility::fillTriangle(MCUFRIEND_kbv *tftlcd, int16_t x, int16_t y, int16_t baseWidth, int16_t height, int16_t colour, boolean inverted = false)
{
    int16_t triangleX0 = x - (baseWidth / 2);
    int16_t triangleY0 = y + (height / 2);
    int16_t triangleX1 = triangleX0 + baseWidth;
    int16_t triangleX2 = triangleX0 + (baseWidth / 2);
    int16_t triangleY2 = inverted ? triangleY0 + height : triangleY0 - height;
    tftlcd->fillTriangle(triangleX0, triangleY0, triangleX1, triangleY0, triangleX2, triangleY2, colour);
}

void DDSGraphicalUtility::drawGrid(MCUFRIEND_kbv *tftlcd, int16_t centerX, int16_t centerY, int16_t radius)
{
    int16_t diameter = radius * 2;
    int16_t gridLineHeight = diameter / GRID_LINES;
    int16_t topX = centerX - radius;
    int16_t topY = centerY - radius + gridLineHeight;
    do
    {
        tftlcd->drawFastHLine(topX, topY, diameter, DISPLAY_GRID_LINE_COLOR);
        topY = topY + gridLineHeight;
    } while (topY <= (centerY + radius));
    topY = centerY - radius;
    topX = topX + gridLineHeight;
    do
    {
        tftlcd->drawFastVLine(topX, topY, diameter, DISPLAY_GRID_LINE_COLOR);
        topX = topX + gridLineHeight;
    } while (topX <= (centerX + radius));
}