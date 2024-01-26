#ifndef SLIDER_H
#define SLIDER_H

#include <stdint.h>
#include <stdbool.h>

void initialize_slider();
_Bool tsi0_scan_has_completed();
_Bool tsi0_scan_is_in_progress();
uint16_t touch_scan();

#endif