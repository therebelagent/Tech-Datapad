//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DDSIrlingBImage.h"
#include "DDSImagePainter.h"
#include "DDSIrlingBRepository.h"

DDSIrlingBImage::DDSIrlingBImage(IDatapadTFTLCD &datapadTFTLCD) : IDDSImage(datapadTFTLCD) {}

void DDSIrlingBImage::drawImage(int16_t x, int16_t y)
{
    DDSImagePainter ddsImagePainter = DDSImagePainter(_datapadTFTLCD);
    ddsImagePainter.drawArrayJpeg(irlingBImage, sizeof(irlingBImage), x, y);
}

int16_t DDSIrlingBImage::width() { return 228; }

int16_t DDSIrlingBImage::height() { return 213; }