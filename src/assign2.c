#include <MKL25Z4.h>
#include <sw1.h>
#include <rgbled.h>

//PORTA->PCR[20] = (PORTA->PCR[20]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)| PORT_PCR_IRQC(0);

 void main( void) {
//create variable random to hold counter variable (keep uninitialized as extra entropy)
uint8_t random;
//configure red LED
initialize_leds();
initialize_sw1();

while(1)
{
    //if sw1 is not pressed 
            //increment random 
	if(sw1_pressed()) {
	random++;
	toggle_red_led();
	toggle_green_led();
	toggle_blue_led();	
	}
   //else
	else {
      	if (random&1) toggle_red_led();      //toggle red led state based on bit 0 of random
	else clear_red_led();
      	if (random&2) toggle_green_led();      //toggle green led state based on bit 1 of random
	else clear_green_led();
       	if (random&4) toggle_blue_led();      //toggle blue led state based on bit 2 of random
	else clear_blue_led();
    //toggle green led state based on bit 1 of random
            //toggle blue led state based on bit 2 of random    
	}     
}   


}
