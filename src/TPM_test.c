#include <stdio.h>
#include <MKL25Z4.h>
#include <pwm_rgbled.h>
#include <stdint.h>
#include <stdbool.h>
#include <systick.h>
#include <copwdt.h>
void main(){
	
	__disable_irq();
	//initialize_copwdt();
	initialize_systick();
	initialize_rgbled();
	__enable_irq();
	uint8_t count=0;
	_Bool count_direction=0;
	set_blue_level(100);
	
	while(1){
		__asm("wfi");
		//while loop fixed to 1ms
		if(!systick_has_fired()) continue;
		//if systick fires blue led will clear
		turn_off_blue_led();
		if(  count_direction ==1 )
		{
			count++;
			if( count ==101 )
			{
				count_direction = 0;
				count= 100;
			}
		}
		else
		{
			count--;
			if( count ==255 )
			{
				count_direction = 1;
				count= 0;
			}
		}
		set_red_level(count);
		set_green_level(count);
		feed_the_watchdog();

	}


}
