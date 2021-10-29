//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include <JPEGDecoder.h>
#include "DDSImagePainter.h"

// Return the minimum of two values a and b
#define minimum(a, b) (((a) < (b)) ? (a) : (b))

DDSImagePainter::DDSImagePainter(DatapadTFTLCD datapadTFTLCD) : _datapadTFTLCD(datapadTFTLCD) {}

void DDSImagePainter::drawArrayJpeg(const uint8_t arrayname[], uint32_t array_size, int x, int y)
{
    boolean decoded = JpegDec.decodeArray(arrayname, array_size);
    if (decoded)
    {
        // retrieve infomration about the image
        uint16_t *pImg;
        uint16_t mcu_w = JpegDec.MCUWidth;
        uint16_t mcu_h = JpegDec.MCUHeight;
        uint32_t max_x = JpegDec.width;
        uint32_t max_y = JpegDec.height;
        // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
        // Typically these MCUs are 16x16 pixel blocks
        // Determine the width and height of the right and bottom edge image blocks
        uint32_t min_w = minimum(mcu_w, max_x % mcu_w);
        uint32_t min_h = minimum(mcu_h, max_y % mcu_h);
        // save the current image block size
        uint32_t win_w = mcu_w;
        uint32_t win_h = mcu_h;
        // save the coordinate of the right and bottom edges to assist image cropping
        // to the screen size
        max_x += x;
        max_y += y;
        // read each MCU block until there are no more
        while (JpegDec.read())
        {
            // save a pointer to the image block
            pImg = JpegDec.pImage;
            // calculate where the image block should be drawn on the screen
            int mcu_x = JpegDec.MCUx * mcu_w + x;
            int mcu_y = JpegDec.MCUy * mcu_h + y;
            // check if the image block size needs to be changed for the right and bottom edges
            if (mcu_x + mcu_w <= max_x)
                win_w = mcu_w;
            else
                win_w = min_w;
            if (mcu_y + mcu_h <= max_y)
                win_h = mcu_h;
            else
                win_h = min_h;
            // calculate how many pixels must be drawn
            uint16_t mcu_pixels = win_w * win_h;
            // draw image MCU block only if it will fit on the screen
            if ((mcu_x + win_w) <= _datapadTFTLCD.width() && (mcu_y + win_h) <= _datapadTFTLCD.height())
            {
                // Now set a MCU bounding window on the TFT to push pixels into (x, y, x + width - 1, y + height - 1)
                _datapadTFTLCD.setAddrWindow(mcu_x, mcu_y, mcu_x + win_w - 1, mcu_y + win_h - 1);
                // Write all MCU pixels to the TFT window
                _datapadTFTLCD.pushColors(pImg, mcu_pixels, 1);
            }
            // Stop drawing blocks if the bottom of the screen has been reached,
            // the abort function will close the file
            else if ((mcu_y + win_h) >= _datapadTFTLCD.height())
                JpegDec.abort();
        }
    }
}