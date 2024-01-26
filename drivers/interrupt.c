// Active low switch on portd 20
// interupt sincronization
//ISR increment a counter
// main program read and clear counter in each loop

#include <stdint.h>
#include "interrupt.h"
#include <MKL25z4.h>

#ifndef PORTD_IRQ_PRIORITY
#define PORTD_IRQ_PRIORITY 3
#endif

#define SWPOS 20 // switch position

static uint32_t g_sw_count = 0; // makes it private

void initialize_sw() {

      SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
      PORTD->PCR[SWPOS] = PORT_PCR_MUX(1) |
      PORT_PCR_IRQC(10) | // falling edge
      PORT_PCR_PE_MASK | // we are writting in all the bits
      PORT_PCR_PS_MASK;
      PTD->PDDR &= ~(1<<SWPOS);
      NVIC_SetPriority(PORTD_IRQn, PORTD_IRQ_PRIORITY /*used to make
      //that priority doesnt follow the calling order but the priority order*/);
      NVIC_ClearPendingIRQ(PORTD_IRQn);
      NVIC_EnableIRQ(PORTD_IRQn);
}

uint32_t get_and_clear_sw_count() {

      uint32_t retval;
      uint32_t masking_state = __get_PRIMASK();
      __disable_irq();
      retval = g_sw_count;
      g_sw_count = 0;
      __set_PRIMASK(masking_state);
      return retval;
}

void PORTD_IRQ_Handler() {

      // increment the count then clear the status flag to acknoledge interupt
      g_sw_count++;
      PORTD->ISFR |= (1<<SWPOS); // PORTD_ISFR = 0xFFFFFFFF
}
