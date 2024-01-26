#include <sw1.h>


void initialize_sw1(){
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
        PORTA->PCR[20] = (PORTA->PCR[20]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)|PORT_PCR_IRQC(0);

	PTA->PDDR &= ~(1<<20);
}

_Bool sw1_not_pressed(){return PTA->PDIR & (1<<20);}


_Bool sw1_pressed(){return !sw1_not_pressed();}




void _delay( uint8_t delaytime){
	volatile  uint8_t delay_count;
	volatile  uint8_t count;
	
	for (count =0; count<delaytime;count++);{
//	for(delay_count=0;delay_count<time;delay_count++);
}

}


_Bool wait_until_pressed_and_released(){

	while(sw1_pressed()){;}
	_delay(10);
	return sw1_pressed();
}

enum stateType timed_press(_Bool press){
	static enum stateType state= wait_for_press;
	static uint32_t count;
	switch(state){

		case wait_for_press:
			count=0;
			//waits for the intial press
			if(press)	state= wait_for_release;
			//if not pressed wait
			else state= wait_for_press;		
//			set_green_led();
			break;

		case wait_for_release:
			//button pressed begin counting
			count++;
			//when button is released assign time range
			if(!press)	state= assign_time_range; 
		
			else state= wait_for_release;

			break;

		case assign_time_range:

			//count greater than 2 seconds wait for reset 
			if(count > 2000) while(1);
			//count 1.5 seconds to 2 toggle blue
			else if(count > 1500) state = one_half_to_two_sec; // blue;
			//count 1 to 1.5  toggle green
			else if(count > 1000) state = one_to_one_half_sec;
			//count .5 to 1 toggle red
			else if(count > 500)  state = half_to_one_sec;//  red;
			//count 0 t0 0.5 
			else if (count >0) state = zero_to_half_sec ;
			else state=wait_for_press;

			break;
		// once state is assigned fsm returns to wait 
		case one_half_to_two_sec:
			state=wait_for_press;break;
		case one_to_one_half_sec:
			state=wait_for_press;break;
		case half_to_one_sec:
			state=wait_for_press;break;
		case zero_to_half_sec:
			state=wait_for_press;break;
		default :
		return 0;
		
		}
	return state;
}
