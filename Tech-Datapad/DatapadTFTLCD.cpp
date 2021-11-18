//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadTFTLCD.h"

DatapadTFTLCD::DatapadTFTLCD() { _tftlcd.begin(_tftlcd.readID()); }

void DatapadTFTLCD::setRotation(uint8_t rotation) { _tftlcd.setRotation(rotation); }

void DatapadTFTLCD::fillScreen(uint16_t color) { _tftlcd.fillScreen(color); }

void DatapadTFTLCD::drawCircle(int16_t x, int16_t y, int16_t radius, uint16_t color) { _tftlcd.drawCircle(x, y, radius, color); }

void DatapadTFTLCD::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) { _tftlcd.fillTriangle(x0, y0, x1, y1, x2, y2, color); }

void DatapadTFTLCD::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) { _tftlcd.fillCircle(x0, y0, r, color); }

void DatapadTFTLCD::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) { _tftlcd.drawFastHLine(x, y, w, color); }

void DatapadTFTLCD::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) { _tftlcd.drawFastVLine(x, y, h, color); }

void DatapadTFTLCD::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) { _tftlcd.fillRect(x, y, w, h, color); }

void DatapadTFTLCD::setFont(const GFXfont *gfxfont) { _tftlcd.setFont(gfxfont); }

void DatapadTFTLCD::getTextBounds(const char *str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) { _tftlcd.getTextBounds(str, x, y, x1, y1, w, h); }

void DatapadTFTLCD::setCursor(int16_t x, int16_t y) { _tftlcd.setCursor(x, y); }

void DatapadTFTLCD::setTextColor(uint16_t color) { _tftlcd.setTextColor(color); }

void DatapadTFTLCD::print(const char str[]) { _tftlcd.print(str); };

void DatapadTFTLCD::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) { _tftlcd.fillRoundRect(x, y, w, h, r, color); }

void DatapadTFTLCD::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) { _tftlcd.drawRoundRect(x, y, w, h, r, color); }

void DatapadTFTLCD::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) { _tftlcd.drawRect(x, y, w, h, color); }

void DatapadTFTLCD::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) { _tftlcd.drawLine(x0, y0, x1, y1, color); }

void DatapadTFTLCD::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) { _tftlcd.drawTriangle(x0, y0, x1, y1, x2, y2, color); }

int16_t DatapadTFTLCD::width(void) { return _tftlcd.width(); }

int16_t DatapadTFTLCD::height(void) { return _tftlcd.height(); }

void DatapadTFTLCD::drawInnerCircle(int16_t x, int16_t y, int16_t radius, int16_t offset, unsigned int colour)
{
    for (int16_t counter = 0; counter < offset; counter++)
    {
        _tftlcd.drawCircle(x, y, radius - counter, colour);
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
void DatapadTFTLCD::fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)
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
        _tftlcd.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
        _tftlcd.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
        // Copy segment end to sgement start for next segment
        x0 = x2;
        y0 = y2;
        x1 = x3;
        y1 = y3;
    }
}

void DatapadTFTLCD::drawFastHorizontalLine(int16_t x, int16_t y, int16_t width, int16_t height, unsigned int colour)
{
    int16_t top = y - (height / 2);
    for (int16_t counter = top; counter < top + height; counter++)
    {
        _tftlcd.drawFastHLine(x, counter, width, colour);
    }
}

void DatapadTFTLCD::fillIterationShape(int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour)
{
    int16_t newX, newWidth;
    int16_t triangleHeight = width * 0.07;
    newWidth = width - (triangleHeight * 2);
    newX = x + triangleHeight;
    _tftlcd.fillRect(newX, y, newWidth, height, colour);
    int16_t triangleY1 = (y + height) - 1;
    int16_t triangleX2 = newX - triangleHeight;
    int16_t triangleY2 = (y + (height / 2)) - 1;
    _tftlcd.fillTriangle(newX, y, newX, triangleY1, triangleX2, triangleY2, colour);
    newX = newX + newWidth;
    triangleX2 = newX + triangleHeight;
    _tftlcd.fillTriangle(newX, y, newX, triangleY1, triangleX2, triangleY2, colour);
}

void DatapadTFTLCD::printCenteredText(const char *text, const GFXfont *gfxFont, int16_t x, int16_t y, unsigned int colour)
{
    int16_t x1, y1;
    uint16_t textWidth, textHeight;
    _tftlcd.setFont(gfxFont);
    _tftlcd.getTextBounds(text, 0, 0, &x1, &y1, &textWidth, &textHeight);
    _tftlcd.setCursor(x - (textWidth / 2), y + (textHeight / 2));
    _tftlcd.setTextColor(colour);
    _tftlcd.print(text);
}

void DatapadTFTLCD::printCenteredText(const char *text, const GFXfont *gfxFont, int16_t x, int16_t y, uint16_t *width, uint16_t *height, unsigned int colour)
{
    int16_t x1, y1;
    uint16_t textWidth, textHeight;
    _tftlcd.setFont(gfxFont);
    _tftlcd.getTextBounds(text, 0, 0, &x1, &y1, &textWidth, &textHeight);
    _tftlcd.setCursor(x - (textWidth / 2), y + (textHeight / 2));
    _tftlcd.setTextColor(colour);
    _tftlcd.print(text);
    *width = textWidth;
    *height = textHeight;
}

void DatapadTFTLCD::fillTriangle(int16_t x, int16_t y, int16_t baseWidth, int16_t height, int16_t colour, boolean inverted = false)
{
    int16_t halfBaseWidth = baseWidth / 2;
    int16_t triangleX0 = x - halfBaseWidth;
    int16_t triangleY0 = y + (height / 2);
    int16_t triangleX1 = triangleX0 + baseWidth;
    int16_t triangleX2 = triangleX0 + halfBaseWidth;
    int16_t triangleY2 = inverted ? triangleY0 + height : triangleY0 - height;
    _tftlcd.fillTriangle(triangleX0, triangleY0, triangleX1, triangleY0, triangleX2, triangleY2, colour);
}

void DatapadTFTLCD::fillVerticalTriangle(int16_t x, int16_t y, int16_t baseWidth, int16_t height, int16_t colour, boolean inverted = false)
{
    int16_t halfBaseWidth = baseWidth / 2;
    int16_t triangleX0 = x - halfBaseWidth;
    int16_t triangleY0 = y;
    int16_t triangleX1 = x;
    int16_t triangleY1 = inverted ? triangleY0 + height : triangleY0 - height;
    int16_t triangleX2 = triangleX0 + baseWidth;
    int16_t triangleY2 = triangleY0;
    _tftlcd.fillTriangle(triangleX0, triangleY0, triangleX1, triangleY1, triangleX2, triangleY2, colour);
}

void DatapadTFTLCD::drawGrid(int16_t centerX, int16_t centerY, int16_t radius, int16_t gridLines, unsigned int color)
{
    int16_t diameter = radius * 2;
    int16_t gridLineHeight = (diameter / gridLines) + 1;
    int16_t halfGridLines = gridLines / 2;
    int16_t topX = centerX - radius;
    int16_t topY = centerY - radius;
    int16_t nextLinePosition = centerX;
    for (int16_t line = 0; line <= halfGridLines; line++)
    {
        _tftlcd.drawFastVLine(nextLinePosition, topY, diameter, color);
        nextLinePosition += gridLineHeight;
    }
    nextLinePosition = centerX - gridLineHeight;
    for (int16_t line = 0; line < halfGridLines; line++)
    {
        _tftlcd.drawFastVLine(nextLinePosition, topY, diameter, color);
        nextLinePosition -= gridLineHeight;
    }
    nextLinePosition = centerY;
    for (int16_t line = 0; line <= halfGridLines; line++)
    {
        _tftlcd.drawFastHLine(topX, nextLinePosition, diameter, color);
        nextLinePosition += gridLineHeight;
    }
    nextLinePosition = centerY - gridLineHeight;
    for (int16_t line = 0; line < halfGridLines; line++)
    {
        _tftlcd.drawFastHLine(topX, nextLinePosition, diameter, color);
        nextLinePosition -= gridLineHeight;
    }
}

void DatapadTFTLCD::drawRoundFrame(int16_t centerX, int16_t centerY, int16_t radius, int16_t shift, bool hollow, int16_t offset, unsigned int color, unsigned int backColor)
{
    int16_t firstQuadrant = 332 + shift;
    int16_t secondQuadrant = 62 + shift;
    int16_t thirdQuadrant = 152 + shift;
    int16_t fourhtQuadrant = 242 + shift;
    int16_t innerRoundFrameHeight = 6;
    int16_t innerRoundFrameRadius = radius - 5;
    int16_t innerRoundFrameFillHeight = 3;
    int16_t innerRoundFrameFillRadius = radius - 6;
    drawInnerCircle(centerX, centerY, innerRoundFrameRadius, offset, color);
    fillArc(centerX, centerY, firstQuadrant, 19, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, color);
    fillArc(centerX, centerY, secondQuadrant, 19, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, color);
    fillArc(centerX, centerY, thirdQuadrant, 19, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, color);
    fillArc(centerX, centerY, fourhtQuadrant, 19, innerRoundFrameRadius, innerRoundFrameRadius, innerRoundFrameHeight, color);
    if (hollow)
    {
        fillArc(centerX, centerY, firstQuadrant + 1, 18, innerRoundFrameFillRadius, innerRoundFrameFillRadius, innerRoundFrameFillHeight, backColor);
        fillArc(centerX, centerY, secondQuadrant + 1, 8, innerRoundFrameFillRadius, innerRoundFrameFillRadius, innerRoundFrameFillHeight, backColor);
        fillArc(centerX, centerY, secondQuadrant + 31, 8, innerRoundFrameFillRadius, innerRoundFrameFillRadius, innerRoundFrameFillHeight, backColor);
        fillArc(centerX, centerY, thirdQuadrant + 1, 18, innerRoundFrameFillRadius, innerRoundFrameFillRadius, innerRoundFrameFillHeight, backColor);
        fillArc(centerX, centerY, fourhtQuadrant + 1, 8, innerRoundFrameFillRadius, innerRoundFrameFillRadius, innerRoundFrameFillHeight, backColor);
        fillArc(centerX, centerY, fourhtQuadrant + 31, 8, innerRoundFrameFillRadius, innerRoundFrameFillRadius, innerRoundFrameFillHeight, backColor);
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
void DatapadTFTLCD::fillQuarterCircle(int16_t x0, int16_t y0, int16_t r, uint8_t quarter, int16_t delta, uint16_t colour)
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
        _tftlcd.drawFastVLine(x0, y0 - r, r, colour);
        if (x < (y + 1))
        {
            if (quarter & 1)
                _tftlcd.drawFastVLine(x0 + x, y0 - y, (2 * y + delta) / 2, colour);
            if (quarter & 2)
                _tftlcd.drawFastVLine(x0 - x, y0 - y, (2 * y + delta) / 2, colour);
        }
        if (y != py)
        {
            if (quarter & 1)
                _tftlcd.drawFastVLine(x0 + py, y0 - px, (2 * px + delta) / 2, colour);
            if (quarter & 2)
                _tftlcd.drawFastVLine(x0 - py, y0 - px, (2 * px + delta) / 2, colour);
            py = y;
        }
        px = x;
    }
}

void DatapadTFTLCD::drawRoundedRectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t borderColour, uint16_t colour)
{
    _tftlcd.fillRoundRect(x, y, width, height, 5, colour);
    _tftlcd.drawRoundRect(x, y, width, height, 5, borderColour);
}

void DatapadTFTLCD::fillRectangle(int16_t x, int16_t y, int16_t width, int16_t height, int16_t borderColour, uint16_t colour)
{
    _tftlcd.fillRect(x, y, width, height, colour);
    _tftlcd.drawRect(x, y, width, height, borderColour);
}

void DatapadTFTLCD::drawFastVerticalLine(int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour)
{
    int16_t left = x - (width / 2);
    for (int16_t counter = left; counter < left + width; counter++)
    {
        _tftlcd.drawFastVLine(counter, y, height, colour);
    }
}

void DatapadTFTLCD::drawRectangle(int16_t x, int16_t y, int16_t width, int16_t height, int16_t lineWidth, uint16_t colour)
{
    x = x - (lineWidth / 2);
    for (int16_t counter = 0; counter < lineWidth; counter++)
    {
        _tftlcd.drawRect(x + counter, y + counter, width - 2 * counter, height - 2 * counter, colour);
    }
}

void DatapadTFTLCD::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t lineWidth, uint16_t colour)
{
    for (int16_t counter = 0; counter < lineWidth; counter++)
    {
        _tftlcd.drawLine(x0 + counter, y0, x1 + counter, y1, colour);
    }
}

void DatapadTFTLCD::drawVerticalTrapezoid(int16_t x, int16_t y, int16_t baseWidth, int16_t topWidth, int16_t height, int16_t lineWidth, uint16_t colour, bool inverted = false)
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
    drawFastVerticalLine(x, y, baseWidth, lineWidth, colour);
    drawFastVerticalLine(x1, y1, topWidth, lineWidth, colour);
    drawLine(x - (lineWidth / 2), y, x1 - (lineWidth / 2), y1, lineWidth, colour);
    drawLine(x - (lineWidth / 2), y + baseWidth - 1, x1 - (lineWidth / 2), y1 + topWidth, lineWidth, colour);
}

void DatapadTFTLCD::drawBanner(int16_t x, int16_t y, int16_t height, int16_t width, unsigned int color, const char *text, const GFXfont *gfxFont)
{
    int16_t offset = 4;
    int16_t bannerLeft = x - (width / 2);
    fillIterationShape(bannerLeft, y, height, width, TFT_WHITE);
    height -= offset;
    width -= offset;
    bannerLeft = x - (width / 2);
    y += offset / 2;
    fillIterationShape(bannerLeft, y, height, width, color);
    printCenteredText(text, gfxFont, x, y + (height / 2), TFT_WHITE);
}

void DatapadTFTLCD::drawRGBBitmapFar(uint16_t windowX, uint16_t windowY, uint16_t imageWidth, uint16_t imageHeight, uint32_t imagePtr)
{
    uint16_t x, y;
    uint32_t linePtr, pixelPtr;
    // linePtr points to each beginning of line in the source image bitmap.
    linePtr = imagePtr;
    _tftlcd.startWrite();
    for (y = windowY; y < windowY + imageHeight; y++)
    {
        // pixelPtr points to each pixel to be painted.
        pixelPtr = linePtr;
        for (x = windowX; x < windowX + imageWidth; x++)
        {
            _tftlcd.writePixel(x, y, pgm_read_word_far(pixelPtr));
            pixelPtr += sizeof(uint16_t); // Next word (2 bytes)
        }
        // Increment linePtr to point to the next line in the source image bitmap.
        linePtr += imageWidth * sizeof(uint16_t);
    }
    _tftlcd.endWrite();
}

void DatapadTFTLCD::setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1) { _tftlcd.setAddrWindow(x, y, x1, y1); }

void DatapadTFTLCD::pushColors(uint16_t *block, int16_t n, bool first) { _tftlcd.pushColors(block, n, first); }

void DatapadTFTLCD::fillArrow(int16_t x, int16_t y, int16_t baseWidth, int16_t height, int16_t colour, boolean inverted = false)
{
    int16_t halfBaseWidth = baseWidth / 2;
    int16_t triangleX0 = x;
    int16_t triangleY0 = y - halfBaseWidth;
    int16_t triangleX1 = inverted ? triangleX0 - height : triangleX0 + height;
    int16_t triangleY1 = y;
    int16_t triangleX2 = triangleX0;
    int16_t triangleY2 = triangleY1 + halfBaseWidth;
    _tftlcd.fillTriangle(triangleX0, triangleY0, triangleX1, triangleY1, triangleX2, triangleY2, colour);
}

uint16_t DatapadTFTLCD::readPixel(int16_t x, int16_t y) { return _tftlcd.readPixel(x, y); }