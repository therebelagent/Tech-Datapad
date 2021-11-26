//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#ifndef IDatapadTFTLCD_h
#define IDatapadTFTLCD_h

#include <Adafruit_GFX.h>

class IDatapadTFTLCD
{
public:
    virtual void drawCircle(int16_t x, int16_t y, int16_t radius, uint16_t color) = 0;
    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) = 0;
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) = 0;
    virtual void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) = 0;
    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) = 0;
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) = 0;
    virtual void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) = 0;
    virtual void fillScreen(uint16_t color) = 0;
    virtual void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) = 0;
    virtual void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) = 0;
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) = 0;
    virtual void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) = 0;
    virtual void getTextBounds(const char *str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) = 0;
    virtual void setRotation(uint8_t rotation) = 0;
    virtual void setFont(const GFXfont *gfxfont) = 0;
    virtual void setCursor(int16_t x, int16_t y) = 0;
    virtual void setTextColor(uint16_t color) = 0;
    virtual void print(const char str[]) = 0;
    virtual int16_t width(void) = 0;
    virtual int16_t height(void) = 0;
    virtual void drawRGBBitmapFar(uint16_t windowX, uint16_t windowY, uint16_t imageWidth, uint16_t imageHeight, uint32_t imagePtr) = 0;
    virtual uint16_t readPixel(int16_t x, int16_t y) = 0;
    virtual void drawInnerCircle(int16_t x, int16_t y, int16_t radius, int16_t offset, unsigned int colour) = 0;
    virtual void fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour) = 0;
    virtual void drawFastVerticalLine(int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour) = 0;
    virtual void drawFastHorizontalLine(int16_t x, int16_t y, int16_t width, int16_t height, unsigned int colour) = 0;
    virtual void fillIterationShape(int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour) = 0;
    virtual void printCenteredText(const char *text, const GFXfont *gfxFont, int16_t x, int16_t y, unsigned int colour) = 0;
    virtual void printCenteredText(const char *text, const GFXfont *gfxFont, int16_t x, int16_t y, uint16_t *width, uint16_t *height, unsigned int colour) = 0;
    virtual void fillTriangle(int16_t x, int16_t y, int16_t baseWidth, int16_t height, int16_t colour, boolean inverted = false) = 0;
    virtual void fillVerticalTriangle(int16_t x, int16_t y, int16_t baseWidth, int16_t height, int16_t colour, boolean inverted = false) = 0;
    virtual void drawGrid(int16_t centerX, int16_t centerY, int16_t radius, int16_t gridLines, unsigned int color) = 0;
    virtual void drawRoundFrame(int16_t centerX, int16_t centerY, int16_t radius, int16_t shift, bool hollow, int16_t offset, unsigned int color, unsigned int backColor) = 0;
    virtual void fillQuarterCircle(int16_t x0, int16_t y0, int16_t r, uint8_t quarter, int16_t delta, uint16_t colour) = 0;
    virtual void drawRectangle(int16_t x, int16_t y, int16_t width, int16_t height, int16_t lineWidth, uint16_t colour) = 0;
    virtual void fillRectangle(int16_t x, int16_t y, int16_t width, int16_t height, int16_t borderColour, uint16_t colour) = 0;
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t lineWidth, uint16_t colour) = 0;
    virtual void drawRoundedRectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t borderColour, uint16_t colour) = 0;
    virtual void drawVerticalTrapezoid(int16_t x, int16_t y, int16_t baseWidth, int16_t topWidth, int16_t height, int16_t lineWidth, uint16_t colour, bool inverted = false) = 0;
    virtual void drawBanner(int16_t x, int16_t y, int16_t height, int16_t width, unsigned int color, const char *text, const GFXfont *gfxFont) = 0;
    virtual void setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1) = 0;
    virtual void pushColors(uint16_t *block, int16_t n, bool first) = 0;
    virtual void fillArrow(int16_t x, int16_t y, int16_t baseWidth, int16_t height, int16_t colour, boolean inverted = false) = 0;
};

#endif