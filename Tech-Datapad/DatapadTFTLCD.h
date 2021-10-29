//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include <MCUFRIEND_kbv.h>

#ifndef DatapadTFTLCD_h
#define DatapadTFTLCD_h

class DatapadTFTLCD
{
public:
    DatapadTFTLCD();
    virtual void drawCircle(int16_t x, int16_t y, int16_t radius, uint16_t color);
    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    virtual void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
    virtual void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    virtual void fillScreen(uint16_t color);
    virtual void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    virtual void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    virtual void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
    virtual void getTextBounds(const char *str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
    virtual void setRotation(uint8_t rotation);
    virtual void setFont(const GFXfont *gfxfont);
    virtual void setCursor(int16_t x, int16_t y);
    virtual void setTextColor(uint16_t color);
    virtual void print(const char str[]);
    virtual int16_t width(void);
    virtual int16_t height(void);
    virtual void drawRGBBitmapFar(uint16_t windowX, uint16_t windowY, uint16_t imageWidth, uint16_t imageHeight, uint32_t imagePtr);
    //Methods extracted from DDSGraphicalUtility
    virtual void drawInnerCircle(int16_t x, int16_t y, int16_t radius, int16_t offset, unsigned int colour);
    virtual void fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour);
    virtual void drawFastVerticalLine(int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour);
    virtual void drawFastHorizontalLine(int16_t x, int16_t y, int16_t width, int16_t height, unsigned int colour);
    virtual void fillIterationShape(int16_t x, int16_t y, int16_t height, int16_t width, unsigned int colour);
    virtual void printCenteredText(const char *text, const GFXfont *gfxFont, int16_t x, int16_t y, unsigned int colour);
    virtual void printCenteredText(const char *text, const GFXfont *gfxFont, int16_t x, int16_t y, uint16_t *width, uint16_t *height, unsigned int colour);
    virtual void fillTriangle(int16_t x, int16_t y, int16_t baseWidth, int16_t height, int16_t colour, boolean inverted = false);
    virtual void drawGrid(int16_t centerX, int16_t centerY, int16_t radius, int16_t gridLines, unsigned int color);
    virtual void drawRoundFrame(int16_t centerX, int16_t centerY, int16_t radius, int16_t shift, bool hollow, int16_t offset, unsigned int color, unsigned int backColor);
    virtual void fillQuarterCircle(int16_t x0, int16_t y0, int16_t r, uint8_t quarter, int16_t delta, uint16_t colour);
    virtual void drawRectangle(int16_t x, int16_t y, int16_t width, int16_t height, int16_t lineWidth, uint16_t colour);
    virtual void fillRectangle(int16_t x, int16_t y, int16_t width, int16_t height, int16_t borderColour, uint16_t colour);
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t lineWidth, uint16_t colour);
    virtual void drawRoundedRectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t borderColour, uint16_t colour);
    virtual void drawVerticalTrapezoid(int16_t x, int16_t y, int16_t baseWidth, int16_t topWidth, int16_t height, int16_t lineWidth, uint16_t colour, bool inverted = false);
    virtual void drawBanner(int16_t x, int16_t y, int16_t height, int16_t width, unsigned int color, const char *text, const GFXfont *gfxFont);
    virtual void setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1);
    virtual void pushColors(uint16_t *block, int16_t n, bool first);

private:
    MCUFRIEND_kbv _tftlcd;
};

#endif