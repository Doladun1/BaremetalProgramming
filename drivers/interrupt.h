// Active low switch on portd 20
// interupt sincronization
//ISR increment a counter
// main program read and clear counter in each loop
#ifndef INTERUPT_H
#define INTERUPT_H
#include <stdint.h>

void initialize_sw();
uint32_t get_and_clear_sw_count();

#endif