#include <MKL25Z4.h>

//PORTA->PCR[20] = (PORTA->PCR[20]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)| PORT_PCR_IRQC(0);

 void main( void) {
//create variable random to hold counter variable (keep uninitialized as extra entropy)
uint8_t random;
//configure red LED
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
        PORTB->PCR[18] = (PORTB->PCR[18]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)| PORT_PCR_IRQC(0);

//configure green LED
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
        PORTB->PCR[19] = (PORTB->PCR[19]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)|PORT_PCR_IRQC(0);

//configure blue LED
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
        PORTD->PCR[1] = (PORTB->PCR[1]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)|PORT_PCR_IRQC(0);


	PTB->PDDR  |= (1<<18) | (1<<19) ;
	PTD->PDDR  |= (1<<1);

        SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
        PORTA->PCR[20] = (PORTA->PCR[20]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)|PORT_PCR_IRQC(0);

	PTA->PDDR &= ~(1<<20);

while(1)
{
    //if sw1 is not pressed 
            //increment random 
	if( PTA->PDIR & (1<<20)) {
	random++;
	}
    //else
	else {
      	if (random&1) PTB->PCOR |= (1<<18);      //set red led state based on bit 0 of random
	else PTB->PSOR |= (1<<18);
      	if (random&2) PTB->PCOR |= (1<<19);      //set green led state based on bit 1 of random
	else PTB->PSOR |= (1<<19);
       	if (random&4) PTD->PCOR |= (1<<1);      //set blue led state based on bit 2 of random
	else PTD->PSOR |= (1<<1);
    //set green led state based on bit 1 of random
            //set blue led state based on bit 2 of random    
	}     
}   


}
