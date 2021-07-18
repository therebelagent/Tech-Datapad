#include "SlideshowDDS.h"
#include "StandByDDS.h"
//#include "ExplosiveChargesDDS.h"
#include "EnemyTargetsDDS.h"
//#include "CannonPoweringUpDDS.h"

SlideshowDDS::SlideshowDDS(MCUFRIEND_kbv *tftlcd) : DatapadDisplaySequence(tftlcd)
{
    _tftlcd = tftlcd;
}

void SlideshowDDS::show()
{
    DatapadDisplaySequence *datapadDisplaySequence;
    switch (currentDatapadDisplaySequence)
    {
    case 1:
        datapadDisplaySequence = new StandByDDS(_tftlcd);
        currentDatapadDisplaySequence = 2;
        break;
    case 2:
        datapadDisplaySequence = new EnemyTargetsDDS(_tftlcd);
        currentDatapadDisplaySequence = 1;
        break;
        /*case 3:
        datapadDisplaySequence = new CannonPoweringUpDDS(_tftlcd);
        currentDatapadDisplaySequence = 1;
        break;*/
        /*case 4:
        datapadDisplaySequence = new ExplosiveChargesDDS(_tftlcd);
        datapadDisplaySequence->reset();
        currentDatapadDisplaySequence = 1;
        break;*/
    }
    datapadDisplaySequence->show();
}

void SlideshowDDS::reset()
{
    currentDatapadDisplaySequence = 1;
    DatapadDisplaySequence::reset();
}