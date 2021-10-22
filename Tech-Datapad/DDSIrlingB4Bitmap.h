//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//
// Image Size     : 114x114 pixels
// Memory usage   : 25992 bytes

#include <avr/pgmspace.h>

#define PROGMEM_LATE __attribute__((__section__(".fini1")))
extern const uint16_t irlingB4Bitmap[12996] PROGMEM_LATE;