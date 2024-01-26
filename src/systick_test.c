// WATCHDOG and SYS_TICK TIMER
#include <MKL25Z4.h>
#include <systick.h>
#include <rgbled.h>
#include <sw1.h>

void main(){
	uint32_t count=0;
	__disable_irq();
	initialize_leds();
	initialize_systick();
	initialize_sw1();
	__enable_irq();
	clear_leds();
	//turn on green
	set_green_led();
	while(1){
		asm("wfi");
		if(!systick_has_fired()) continue;
		//turn off green
		clear_green_led();
		//toggle red every 500 counts
		if(count ==1000){
		toggle_red_led();
		count=0;}
		count++;
	}


}
