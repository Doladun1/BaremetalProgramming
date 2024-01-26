#ifndef sw1_H
#define sw1_H
#include <stdbool.h>
#include <stdint.h>
#include <MKL25Z4.h>

enum stateType {wait_for_press, wait_for_release,assign_time_range,
		 zero_to_half_sec,half_to_one_sec,one_to_one_half_sec,one_half_to_two_sec};

void _delay(uint8_t delaytime);

void initialize_sw1();

_Bool sw1_pressed();


_Bool sw1_not_pressed();

enum stateType timed_press(_Bool press);
_Bool wait_until_pressed_and_released();

#endif
