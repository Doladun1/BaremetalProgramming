#include <MKL25Z4.h>


void main(void) 
{
	//Configure LED and Push button
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[18] = (PORTB->PCR[18]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1) | PORT_PCR_IRQC(0);
	
	PTB->PDDR  |= (1<<18);
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
        PORTA->PCR[20] = (PORTA->PCR[20]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)| PORT_PCR_IRQC(0);

        PTA->PDDR  &= ~(1<<20);
	while(1){	
//check if  button on
	if( PTA->PDIR & (1<<20))
		PTB->PCOR |= (1<<18);
	else
		PTB->PSOR |= (1<<18);
	//toogle LED
	}
}
