// WATCHDOG and SYS_TICK TIMER 
#include <MKL25Z4.h>
#include <systick.h>
#include <rgbled.h>
#include <copwdt.h>
#include <sw1.h>

void color(enum Color color); 
void main(){

	enum Color color =black;
	enum stateType state;
	__disable_irq();
	initialize_leds();
	initialize_systick();
	initialize_sw1();
	initialize_copwdt();
	__enable_irq();
	clear_leds();
	//turn on green
	set_green_led();
//	clear_green_led();
	while(1){
		__asm("wfi");
		//while loop fixed to 1ms
		if(!systick_has_fired()) continue;
		//if systick fires green led will clear
		clear_green_led();
		//FSM handles switch press and time
		state=	timed_press(	sw1_pressed()	);
		//switch case assigns color based on count

		if (state ==_1_5_to_two_sec) color =blue;
		else if (state == one_to_1_5_sec) color =green;
		else if (state == zero_to_one_sec) color =red;

		if(color ==blue) toggle_blue_led();
		if(color == green) toggle_green_led();
		if(color ==  red) toggle_red_led();
		feed_the_watchdog();
	}


}

