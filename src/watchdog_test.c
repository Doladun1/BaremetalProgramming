#include <copwdt.h>
#include <rgbled.h>
#include <MKL25Z4.h>

void wait()
{
	volatile unsigned x = 480000;
	while(x--);
}

void main()
{
	initialize_copwdt();
	initialize_leds();
	set_green_led();
	clear_leds();
	toggle_red_led();
	wait();
	toggle_red_led();
	wait();
	toggle_red_led();
	wait();
	while(1){
		set_green_led();
//		feed_the_watchdog();
	}
}
