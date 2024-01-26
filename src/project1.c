// WATCHDOG and SYS_TICK TIMER 
#include <MKL25Z4.h>
#include <systick.h>
#include <pwm_rgbled.h>
#include <copwdt.h>
#include <sw1.h>

void color(enum Color color); 
void main(){

	enum Color color =black;
	enum stateType state;
	uint8_t blue_count=0,green_count=0,red_count=0;
	uint32_t count=0;
	__disable_irq();
	initialize_rgbled();
	initialize_systick();
	initialize_sw1();
	initialize_copwdt();
	__enable_irq();
	clear_leds();
	//turn on green
	//set_rgbled_color_to(100,100,100);
//	clear_green_led();
	while(1){
		__asm("wfi");
		//while loop fixed to 1ms
		if(!systick_has_fired()) continue;
		
		//FSM handles switch press and time
		state=	timed_press(	sw1_pressed()	);
		//switch case assigns color based on count

		if (state ==one_half_to_two_sec) {color = blue; blue_count=0;}
		else if (state == one_to_one_half_sec) {color = green;green_count=0;}
		else if (state == half_to_one_sec) {color = red;red_count=0;}
		
		//brightness is set based on how long switch is pressed from 0-0.5 seconds
		//color is set using time ranges
		else if (state == zero_to_half_sec) {
			if(color ==blue) blue_count+=16;
			if(color == green) green_count+=16;
			if(color ==  red) red_count+=16;
			
		}
		// when there is no activity the led will display the last value configuration
		else if (state == wait_for_press) {set_rgbled_color_to(red_count/16,green_count/16,blue_count/16);count=0;}
		
		//while button is pressed leds cycle through which color is selected
		else if (state ==wait_for_release) {
			count++;
			if (count>2000) set_rgbled_color_to(0,0,0);
			else if (count>1500) set_rgbled_color_to(0,0,50);
			else if (count>1000) set_rgbled_color_to(0,50,0);
			else if (count>500) set_rgbled_color_to(50,0,0);
			else set_rgbled_color_to(20,20,20);
		
		}

		//Brightness is set depending on count length and color chosen
		//watchdog is fed after each cycle to prevent reset
		//if button is pressed for longer than 2 seconds reset will occur
		feed_the_watchdog();
	}


}

