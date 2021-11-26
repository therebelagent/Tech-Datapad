//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

#include "BasicGridDDS.h"

BasicGridDDS::BasicGridDDS(IDatapadTFTLCD &datapadTFTLCD) : StandByDDS(datapadTFTLCD) {}

void BasicGridDDS::show()
{
    StandByDDS::show();
    int16_t centerX = _datapadTFTLCD.width() / 2;
    int16_t centerY = _datapadTFTLCD.height() / 2;
    int16_t radius = centerX - 1;
    _datapadTFTLCD.drawGrid(centerX, centerY, radius, DEFAULT_GRID_LINES, DISPLAY_GRID_LINE_COLOR);
}