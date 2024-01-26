#include <i2c0.h>
#include <pwm_rgbled.h>
#include <copwdt.h>
#include <systick.h>
#include <sw1.h>
#include <MKL25Z4.h>
#include <stdbool.h>

uint8_t readAccelerometer(uint8_t color_select);
/* This program is a modification of Project 4 PWM combination display. The final display is filtered using 3axis accelerometer
   User can create any combination of colors by rotating the device in the 9 orientations. The serial reading of the accelerometer 
   byte runs relatively slow to the whole program. Speed is maintained by cycling through the axes and measuring one per while loop.
   Program creates combination effect by setting and clearing the 3 axes.
   
   Loop is clocked by systick timer and watchdog reset is set should any errors occur  */ 

void main()//8bit x
{
	uint8_t i2cdata;
   	uint8_t color_select= 0;
    enum Color color =black;
    enum stateType state;
    uint8_t blue_count=0,green_count=0,red_count=0;
	uint8_t red_set=0,blue_set=0,green_set=0;
    uint32_t count=0;
	uint8_t level;
	
	__disable_irq();
    initialize_rgbled();
    initialize_i2c0();
	initialize_copwdt();
	initialize_systick();
	initialize_sw1();
	__enable_irq();
	clear_leds();
    i2cdata=i2c0_read_byte((0x1D<<1),0x0D);//for i2c0 device read the device id. check if the device on
    if(i2cdata==0x1a)//if device id is accel
    {
        set_red_led();
    }
    //enable active mode
    i2c0_write_byte(0x3a,0x2a,0x01);//by writing one to control reg 2A, we enable accel  
  
	clear_red_led();
	
    while(1)
    {
		__asm("wfi");
		//while loop fixed to 1ms
		if(!systick_has_fired()) continue;
		state = timed_press(sw1_pressed());
		
		//if axis is high led will toggle if set by FSM		
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
		// Any combination of colors can be displayed using the 3-axis accelerometer
		else if (state == wait_for_press) 
		{
			// color select cycles each axes 	
			level = readAccelerometer(color_select);
			
			//if level is clear or axis reads positive led is cleared
			if		(color_select ==0 )	red_set = level;
			else if (color_select == 2) green_set = level;
			else if (color_select == 4) blue_set = level;
			
			// if axis reads negative led is set to duty cycle
			set_rgbled_color_to(	(red_set*red_count)/16,(green_set*green_count)/16,(blue_set*blue_count)/16);count=0;
			// color select cycles to each axis
			color_select = (color_select +2) % 0x06;
		}
		//while button is pressed leds cycle through which color is selected
		else if (state ==wait_for_release) {
			count++;
			if (count>2000) set_rgbled_color_to(0,0,0);
			else if (count>1500) set_rgbled_color_to(0,0,50);
			else if (count>1000) set_rgbled_color_to(0,50,0);
			else if (count>500) set_rgbled_color_to(50,0,0);
			else set_rgbled_color_to(20,20,20);
			
		}
      
		
		feed_the_watchdog();
    }
}

uint8_t readAccelerometer(uint8_t color_select){
	uint8_t i2cdata;
	int8_t accelerometerRead;		
	
	
	i2cdata = i2c0_read_byte((0x1D<<1),0x00);//read the status reg
	if(i2cdata & (1<<color_select))// check the status bit is set for the corresponding axis
	{
	color_select++;
	accelerometerRead=i2c0_read_byte((0x1D<<1),color_select); // Read value on the corresponding axis
			  // if value is less than zero return one else return zero
			  if(accelerometerRead<0)
			  {
				 return 1;
			  }
			  else
			  {
				 return 0;
			  }
	  }
	  // if accelerometer doesn't detect a set bit function defaults and returns zero
	  return 0;
	  	
}

