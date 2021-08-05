#ifndef DatapadDisplaySequence_h
#define DatapadDisplaySequence_h

#include <MCUFRIEND_kbv.h>

class DatapadDisplaySequence
{

public:
    DatapadDisplaySequence(MCUFRIEND_kbv *tftlcd);
    virtual void show();
    virtual void reset();

private:
    MCUFRIEND_kbv *_tftlcd;
};

#endif