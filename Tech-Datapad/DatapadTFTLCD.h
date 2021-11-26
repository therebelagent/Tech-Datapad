//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "IDatapadTFTLCD.h"
#include <MCUFRIEND_kbv.h>

#ifndef DatapadTFTLCD_h
#define DatapadTFTLCD_h

class DatapadTFTLCD : public IDatapadTFTLCD
{
public:
    DatapadTFTLCD();
    void drawCircle(int16_t x, int16_t y, int16_t radius, uint16_t color);
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    void fillScreen(uint16_t color);
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
    void getTextBounds(const char *str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
    void setRotation(uint8_t rotation);
    void setFont(const GFXfont *gfxfont);
    void setCursor(int16_t x, int16_t y);
    void setTextColor(uint16_t color);
    void print(const char str[]);
    int16_t width(void);
    int16_t height(void);
    void drawRGBBitmapFar(uint16_t windowX, uint16_t windowY, uint16_t imageWidth, uint16_t imageHeight, uint32_t imagePtr);
    uint16_t readPixel(int16_t x, int16_t y);
    void drawInnerCircle(int16_t x, int16_t y, int16_t radius, int16_t offset, unsigned int colour);
    void fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour);
    void drawFastVerticalLine(int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour);
    void drawFastHorizontalLine(int16_t x, int16_t y, int16_t width, int16_t height, unsigned int colour);
    void fillIterationShape(int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour);
    void printCenteredText(const char *text, const GFXfont *gfxFont, int16_t x, int16_t y, unsigned int colour);
    void printCenteredText(const char *text, const GFXfont *gfxFont, int16_t x, int16_t y, uint16_t *width, uint16_t *height, unsigned int colour);
    void fillTriangle(int16_t x, int16_t y, int16_t baseWidth, int16_t height, int16_t colour, boolean inverted = false);
    void fillVerticalTriangle(int16_t x, int16_t y, int16_t baseWidth, int16_t height, int16_t colour, boolean inverted = false);
    void drawGrid(int16_t centerX, int16_t centerY, int16_t radius, int16_t gridLines, unsigned int color);
    void drawRoundFrame(int16_t centerX, int16_t centerY, int16_t radius, int16_t shift, bool hollow, int16_t offset, unsigned int color, unsigned int backColor);
    void fillQuarterCircle(int16_t x0, int16_t y0, int16_t r, uint8_t quarter, int16_t delta, uint16_t colour);
    void drawRectangle(int16_t x, int16_t y, int16_t width, int16_t height, int16_t lineWidth, uint16_t colour);
    void fillRectangle(int16_t x, int16_t y, int16_t width, int16_t height, int16_t borderColour, uint16_t colour);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t lineWidth, uint16_t colour);
    void drawRoundedRectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t borderColour, uint16_t colour);
    void drawVerticalTrapezoid(int16_t x, int16_t y, int16_t baseWidth, int16_t topWidth, int16_t height, int16_t lineWidth, uint16_t colour, bool inverted = false);
    void drawBanner(int16_t x, int16_t y, int16_t height, int16_t width, unsigned int color, const char *text, const GFXfont *gfxFont);
    void setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1);
    void pushColors(uint16_t *block, int16_t n, bool first);
    void fillArrow(int16_t x, int16_t y, int16_t baseWidth, int16_t height, int16_t colour, boolean inverted = false);

private:
    MCUFRIEND_kbv _tftlcd;
};

#endif