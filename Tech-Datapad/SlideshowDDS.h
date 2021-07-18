#ifndef SlideshowDDS_h
#define SlideshowDDS_h

#include "DatapadDisplaySequence.h"

class SlideshowDDS : public DatapadDisplaySequence
{
public:
    SlideshowDDS(MCUFRIEND_kbv *tftlcd);
    void show();
    void reset();

private:
    MCUFRIEND_kbv *_tftlcd;
    int16_t currentDatapadDisplaySequence = 1;
};

#endif