//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "DDSHeadScanImage.h"
#include "DDSImagePainter.h"
#include "DDSHeadScanRepository.h"

DDSHeadScanImage::DDSHeadScanImage(IDatapadTFTLCD &datapadTFTLCD) : IDDSImage(datapadTFTLCD) {}

void DDSHeadScanImage::drawImage(int16_t x, int16_t y)
{
    DDSImagePainter ddsImagePainter = DDSImagePainter(_datapadTFTLCD);
    ddsImagePainter.drawArrayJpeg(headScanImage, sizeof(headScanImage), x, y);
}

int16_t DDSHeadScanImage::width() { return 225; }

int16_t DDSHeadScanImage::height() { return 276; }