#include "slider.h"
#include <MKL25Z4.h>
#include <stdbool.h>
#include <stdint.h>

void initialize_slider()
{
    SIM->SCGC5 |=SIM_SCGC5_TSI_MASK;
    TSI0->GENCS=
        TSI_GENCS_CURSW(0)
        |TSI_GENCS_STM(0)
        |TSI_GENCS_STPE(0)
        |TSI_GENCS_TSIIEN(0)
        |TSI_GENCS_NSCN(1)
        |TSI_GENCS_PS(4)
        |TSI_GENCS_EXTCHRG(0)
        |TSI_GENCS_DVOLT(0)
        |TSI_GENCS_REFCHRG(4)
        |TSI_GENCS_MODE(0);
    TSI0->GENCS |= TSI_GENCS_TSIEN(1);
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK | TSI_GENCS_OUTRGF_MASK;
}
_Bool tsi0_scan_has_completed()
{
    return TSI0->GENCS & TSI_GENCS_EOSF_MASK;
}
_Bool tsi0_scan_is_in_progress()
{
    return TSI0->GENCS & TSI_GENCS_SCNIP_MASK;
}
uint16_t touch_scan()
{
    TSI0->DATA= TSI_DATA_TSICH(9)|TSI_DATA_SWTS_MASK;
    while(!tsi0_scan_has_completed());
    //RECOMMENDED TO CHECK INTERRUPT INSTEAD
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK;
    return TSI0->DATA & TSI_DATA_TSICNT_MASK;
}