#ifndef SYSTICK_H
#define SYSTICK_H
#include <stdint.h>
#include <stdbool.h>
#include <MKL25Z4.h>

void initialize_systick();
_Bool systick_has_fired();
#endif
