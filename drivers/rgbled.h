#ifndef rgbled_H
#define rgbled_H


enum Color {black,blue,green,cyan,red,magenta,yellow,white};


void intialize_red_led();
void intialize_green_led();
void intialize_blue_led();

void initialize_leds();

void set_red_led();
void clear_red_led();
void toggle_red_led();

void set_green_led();
void clear_green_led();
void toggle_green_led();	 

void set_blue_led();
void clear_blue_led();
void toggle_blue_led();	 

void set_Color(enum Color color);

void clear_leds();

#endif
