#ifndef BasicGridDDS_h
#define BasicGridDDS_h

#include "DatapadDisplaySequence.h""

class BasicGridDDS : public DatapadDisplaySequence
{
public:
    BasicGridDDS(MCUFRIEND_kbv *tftlcd);
    void show();

private:
    MCUFRIEND_kbv *_tftlcd;
};

#endif