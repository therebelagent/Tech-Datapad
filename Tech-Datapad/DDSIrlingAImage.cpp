//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DDSIrlingAImage.h"
#include "DDSImagePainter.h"
#include "DDSIrlingARepository.h"

DDSIrlingAImage::DDSIrlingAImage(DatapadTFTLCD &datapadTFTLCD) : _datapadTFTLCD(datapadTFTLCD) {}

void DDSIrlingAImage::drawImage(int16_t x, int16_t y)
{
    DDSImagePainter ddsImagePainter = DDSImagePainter(_datapadTFTLCD);
    ddsImagePainter.drawArrayJpeg(irlingAImage, sizeof(irlingAImage), x, y);
}

int16_t DDSIrlingAImage::width() { return 258; }

int16_t DDSIrlingAImage::height() { return 158; }