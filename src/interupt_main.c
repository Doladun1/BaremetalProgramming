#define PORTD_IRQ_PRIORITY 2 // to set the interupt priority to 2
#include <interrupt.h>
#include <stdint.h>
#include <rgbled.h>
#include <MKL25Z4.h>
#include <copwdt.h>
#include <systick.h>

void main () {

      __disable_irq();
      initialize_sw();
      initialize_leds();
	  initialize_copwdt();
	  initialize_systick();
      __enable_irq();
	  clear_leds();
	  //set_red_led();
	 
      while (1) {
		  //__asm("wfi");
		  //while loop fixed to 1ms
		  //if(!systick_has_fired()) continue;
		  //clear_red_led();
		  
          if (get_and_clear_sw_count() != 0) set_red_led();
              
			//  set_red_led();
          
		feed_the_watchdog();

      }
}
