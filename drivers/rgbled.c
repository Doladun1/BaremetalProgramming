#include <rgbled.h>
#include <MKL25Z4.h>


void initialize_red_led(){
SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
PORTB->PCR[18] = (PORTB->PCR[18]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)| PORT_PCR_IRQC(0);
	PTB->PDDR  |= (1<<18) ;

}
void initialize_green_led(){
SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
PORTB->PCR[19] = (PORTB->PCR[19]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)|PORT_PCR_IRQC(0);
	PTB->PDDR  |= (1<<19) ;
}
void initialize_blue_led(){
SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
PORTD->PCR[1] = (PORTD->PCR[1]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)|PORT_PCR_IRQC(0);
		PTD->PDDR  |= (1<<1);
}

void initialize_leds(){
SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
PORTD->PCR[1] = (PORTD->PCR[1]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)|PORT_PCR_IRQC(0);


SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
PORTB->PCR[19] = (PORTB->PCR[19]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)|PORT_PCR_IRQC(0);


SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
PORTB->PCR[18] = (PORTB->PCR[18]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(1)| PORT_PCR_IRQC(0);
	PTB->PDDR  |= (1<<18) | (1<<19) ;
	PTD->PDDR |= (1<<1);
}

void set_red_led(){	 PTB->PCOR |= (1<<18);}
void clear_red_led(){	PTB->PSOR |= (1<<18);}
void toggle_red_led(){ PTB->PTOR  |= (1<<18);} 	 

void set_green_led(){	 PTB->PCOR |= (1<<19);}
void clear_green_led(){	PTB->PSOR |= (1<<19);}
void toggle_green_led(){ PTB->PTOR  |= (1<<19);} 	 
	 

void set_blue_led(){         PTD->PCOR |= (1<<1);}
void clear_blue_led(){        PTD->PSOR |= (1<<1);}
void toggle_blue_led(){ 	PTD->PTOR |= (1<<1);} 

void set_Color(enum Color color){
	switch(color){
		case black:
		clear_leds();
		break;
		
		case blue:
		set_blue_led();clear_green_led();clear_red_led();
		break;
		case green:
		clear_blue_led();set_green_led();clear_red_led();
		break;
		case cyan:
		set_blue_led();set_green_led();clear_red_led();
		break;

		case red:
		clear_blue_led();clear_green_led();set_red_led();
		break;

		case magenta:
		set_blue_led();clear_green_led();set_red_led();
		break;

		case yellow:
		clear_blue_led();set_green_led();set_red_led();
		break;

		case white:
		set_blue_led();set_green_led();set_red_led();
		break;
	}
}

void clear_leds(){ PTB->PSOR |= (1<<18)| (1<<19); PTD-> PSOR |= (1<<1);}
