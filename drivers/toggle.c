#include <toggle.h>
#include <stdint.h>

//
enum stateType= {wait_for_press, wait_for_release}

_Bool timed_press_FSM(_Bool press){
	static enum stateType state= wait_for_press;
	
	switch(state){

		case wait_for_press:
		if(press)	{state= wait_for_release;return 1;}
		
		else {state= wait_for_press;return 0;}		
		
		break;

		case wait_for_release:
		
		if(!press)	{state= wait_for_press;return 0;}
		else return true;

		break;
		default:
		return 0;
		
		}
}
