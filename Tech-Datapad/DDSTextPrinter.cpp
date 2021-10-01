//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DDSTextPrinter.h"

DDSTextPrinter::DDSTextPrinter(DatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t width, int16_t height, int16_t lineHeight, int16_t lineVerticalGap, int16_t backColour) : _datapadTFTLCD(datapadTFTLCD), _x(x), _y(y), _width(width), _height(height), _lineHeight(lineHeight), _lineVerticalGap(lineVerticalGap), _backColor(backColour) {}

void DDSTextPrinter::print(const char *const paragraph[], byte paragraphSize)
{
    int16_t lineHeigh = _lineHeight + _lineVerticalGap;
    int16_t lineTop = _y + _lineHeight;
    int16_t maxTop = _y + _height;
    int16_t x1, y1;
    reset();
    paragraphSize = getParagraphSize(paragraphSize);
    for (int16_t line = 0; line < paragraphSize; line++)
    {
        strcpy_P(_buffer, (char *)pgm_read_word(&(paragraph[line])));
        internalPrint(_x, lineTop, _buffer);
        lineTop += lineHeigh;
        if (lineTop + _lineHeight > maxTop)
        {
            break;
        }
    }
}

void DDSTextPrinter::scrollDown(const char *const paragraph[], byte paragraphSize, int16_t steps = 1)
{
    int16_t lineHeigh = _lineHeight + _lineVerticalGap;
    int16_t currentLineTop = _y + _lineHeight;
    bool paragraphScrolled = false;
    int16_t maxTop = _y + _height;
    int16_t lineTop;
    paragraphSize = getParagraphSize(paragraphSize);
    for (int16_t lineCounter = 1; lineCounter <= _height; lineCounter += steps)
    {
        lineTop = currentLineTop;
        reset();
        for (int16_t line = 0; line < paragraphSize; line++)
        {
            if (lineTop + lineHeigh > maxTop)
            {
                if (line == 0)
                    paragraphScrolled = true;
                break;
            }
            strcpy_P(_buffer, (char *)pgm_read_word(&(paragraph[line])));
            internalPrint(_x, lineTop, _buffer);
            lineTop += lineHeigh;
        }
        delay(50);
        currentLineTop += steps + _lineVerticalGap;
        if (paragraphScrolled)
        {
            break;
        }
    }
}

void DDSTextPrinter::scrollUp(const char *const paragraph[], byte paragraphSize, int16_t steps = 1)
{
    int16_t currentLineTop = _y + _height - _lineVerticalGap;
    int16_t lineHeigh = _lineHeight + _lineVerticalGap;
    bool paragraphScrolled = false;
    int16_t maxTop = _y + _height;
    int16_t lineTop;
    paragraphSize = getParagraphSize(paragraphSize);
    for (int16_t lineCounter = _height; lineCounter >= 0; lineCounter -= steps)
    {
        lineTop = currentLineTop;
        reset();
        for (int16_t line = 0; line < paragraphSize; line++)
        {
            if (lineTop - lineHeigh < _y)
            {
                if (line == paragraphSize - 1)
                {
                    paragraphScrolled = true;
                    break;
                }
            }
            else
            {
                strcpy_P(_buffer, (char *)pgm_read_word(&(paragraph[line])));
                internalPrint(_x, lineTop, _buffer);
            }
            if (lineTop + lineHeigh < maxTop)
            {
                lineTop += lineHeigh;
            }
            else
            {
                break;
            }
        }
        currentLineTop -= steps + _lineVerticalGap;
        if (paragraphScrolled)
        {
            break;
        }
    }
}

void DDSTextPrinter::internalPrint(int16_t x, int16_t y, const char *text)
{
    _datapadTFTLCD.setCursor(x, y);
    _datapadTFTLCD.print(text);
}

byte DDSTextPrinter::getParagraphSize(byte currentParagraphSize)
{
    byte paragraphSize = currentParagraphSize;
    if (currentParagraphSize > FORGING_CHAIN_CODES_PARAGRAPH_MAX_ITEMS)
        paragraphSize = FORGING_CHAIN_CODES_PARAGRAPH_MAX_ITEMS;
    return paragraphSize;
}

void DDSTextPrinter::reset()
{
    _datapadTFTLCD.fillRect(_x, _y, _width, _height, _backColor);
}