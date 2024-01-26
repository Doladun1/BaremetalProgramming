#include <rgbled.h>
#include <slider.h>
#define THRESHOLD 14000
void main()
{
	uint16_t scan =0;
    initialize_slider();
    initialize_leds();
	clear_leds();
    while(1)
    {
		scan =touch_scan();
        
		if (scan > THRESHOLD +7500)
		set_Color(yellow);
		else if(scan>THRESHOLD +6000)
		set_Color(magenta);
		else if (scan > THRESHOLD +4500)
		set_Color(cyan);
		else if(scan>THRESHOLD +3000)
		set_Color(green);
		else if (scan > THRESHOLD +1500)
			set_Color(blue);
		else if(scan>THRESHOLD)
			set_Color(red);
		

    }
}