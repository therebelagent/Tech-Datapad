//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DatapadTFTLCD.h"

#ifndef DDSTextPrinter_h
#define DDSTextPrinter_h

const int16_t PARAGRAPH_MAX_ITEMS = 36;
const int16_t SENTENCE_BUFFER_SIZE = 32;

class DDSTextPrinter
{
public:
    DDSTextPrinter(DatapadTFTLCD &datapadTFTLCD, int16_t x, int16_t y, int16_t width, int16_t height, int16_t lineHeight, int16_t lineVerticalGap, int16_t backColour);
    void print(const char *const paragraph[], byte paragraphSize);
    void scrollDown(const char *const paragraph[], byte paragraphSize, int16_t steps = 1);
    void scrollUp(const char *const paragraph[], byte paragraphSize, int16_t steps = 1);

private:
    DatapadTFTLCD &_datapadTFTLCD;
    const int16_t _x, _y, _width, _height, _lineHeight, _lineVerticalGap, _backColor;
    char _buffer[SENTENCE_BUFFER_SIZE];
    void internalPrint(int16_t x, int16_t y, const char *text);
    byte getParagraphSize(byte currentParagraphSize);
    void reset();
};

#endif