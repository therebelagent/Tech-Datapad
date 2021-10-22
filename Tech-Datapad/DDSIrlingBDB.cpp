//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DDSIrlingBDB.h"
#include "DDSIrlingB1Bitmap.h"
#include "DDSIrlingB2Bitmap.h"
#include "DDSIrlingB3Bitmap.h"
#include "DDSIrlingB4Bitmap.h"

DDSIrlingBDB::DDSIrlingBDB(DatapadTFTLCD &datapadTFTLCD) : _datapadTFTLCD(datapadTFTLCD) {}

void DDSIrlingBDB::drawRGBBitmap(int16_t x, int16_t y)
{
    _datapadTFTLCD.drawRGBBitmapFar(x, y, 114, 114, pgm_get_far_address(irlingB4Bitmap));
    _datapadTFTLCD.drawRGBBitmapFar(x + 114, y, 114, 114, pgm_get_far_address(irlingB3Bitmap));
    _datapadTFTLCD.drawRGBBitmapFar(x, y + 114, 114, 98, pgm_get_far_address(irlingB2Bitmap));
    _datapadTFTLCD.drawRGBBitmapFar(x + 114, y + 114, 114, 98, pgm_get_far_address(irlingB1Bitmap));
}

int16_t DDSIrlingBDB::width() { return 227; }

int16_t DDSIrlingBDB::height() { return 211; }