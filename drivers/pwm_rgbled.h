#ifndef pwm_rgbled_H
#define pwm_rgbled_H

#include <stdint.h>
#include <MKL25Z4.h>
enum Color {black,blue,green,cyan,red,magenta,yellow,white};


void initialize_pwm_red_led();
void initialize_pwm_green_led();
void initialize_pwm_blue_led();

void initialize_rgbled();

void set_green_level(uint8_t duty_cycle);
void turn_off_green_led();

void set_blue_level(uint8_t duty_cycle);
void turn_off_blue_led();

void set_red_level(uint8_t duty_cycle);
void turn_off_red_led();

void set_rgbled_color_to(uint8_t red,uint8_t green,uint8_t blue);

void clear_leds();

#endif
