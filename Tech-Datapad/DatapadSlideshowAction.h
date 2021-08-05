#ifndef DatapadSlideshowAction_h
#define DatapadSlideshowAction_h

#include "DatapadActionFactory.h"
#include "DatapadActionSetup.h"

class DatapadSlideshowAction
{
public:
    DatapadSlideshowAction(DatapadActionSetup *datapadActionSetup);
    void play();

private:
    DatapadActionSetup *_datapadActionSetup;
    int16_t _currentDatapadDisplaySequence = 1;
};

#endif