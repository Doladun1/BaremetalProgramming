#include <systick.h>



#ifndef SYSTICK_PERIOD
#define SYSTICK_PERIOD 1000
#endif


#define SYSTICK_TOP_ (( uint32_t)(SYS_CLOCK / SYSTICK_PERIOD))

#if 	((SYS_CLOCK / SYSTICK_PERIOD) > (1<<24) -1 )	
#error SYSTICK_PERIOD is too large
#endif
//#define SYSTICK_TOP_ ((uint32_t)SYSTICK_TOP_VAL)

static volatile _Bool systick_irq;
void initialize_systick()
{
	//Configure CTRL
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
			SysTick_CTRL_ENABLE_Msk |
			SysTick_CTRL_TICKINT_Msk;

	//Set Period in LOAD
	SysTick->LOAD = SYSTICK_TOP_;
}

_Bool systick_has_fired()
{
	if(systick_irq)
	{
		systick_irq =0;
		return 1;
	}
	return false;
}

void SysTick_Handler()
{
	systick_irq=1;
}
