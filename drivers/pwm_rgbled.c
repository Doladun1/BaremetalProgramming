#include <pwm_rgbled.h>

void initialize_pwm_red_led(){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[18] = (PORTB->PCR[18]&~(PORT_PCR_MUX_MASK)) | PORT_PCR_MUX(4);
	PTB->PDDR  |= (1<<18) ;
	//Setup Timer 0
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	TPM0->SC = TPM_SC_CPWMS(0) | TPM_SC_PS(7);
	TPM0->MOD=100-1;

	//Setup TPM0 Ch1
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_ELSA(1)    |//    TPM_CnSC_ELSB(1) |
			TPM_CnSC_MSA(0)    |    TPM_CnSC_MSB(1);
	
	turn_off_red_led();		
	//Start the timer
	TPM2->SC  |= TPM_SC_CMOD(01);


}
void initialize_pwm_green_led(){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[19] = (PORTB->PCR[19]&~(PORT_PCR_MUX_MASK)) | PORT_PCR_MUX(3);
	PTB->PDDR  |= (1<<19) ;
	//Setup Timer
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	TPM2->SC = TPM_SC_CPWMS(0) | TPM_SC_PS(7);
	TPM2->MOD=256-1;

	//Setup TPM0 Ch1
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_ELSA(1 )    | //   TPM_CNSC_ELSB(1) |
			TPM_CnSC_MSA(0)    |    TPM_CnSC_MSB(1);
	turn_off_green_led();
	//Start the Timer
	TPM2->SC  |= TPM_SC_CMOD(01);

}

void  set_green_level( uint8_t duty_cycle){
	TPM2->CONTROLS[1].CnV = duty_cycle;
}
void  turn_off_green_led(){
	set_green_level(0);  
}

void  set_red_level( uint8_t duty_cycle){
	TPM2->CONTROLS[0].CnV = duty_cycle;
}
void  turn_off_red_led(){
	set_red_level(0);
}

void initialize_pwm_blue_led(){
	//set up PD1
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[1] = (PORTD->PCR[1] &~ (PORT_PCR_MUX_MASK)) | PORT_PCR_MUX(4);
	PTD->PDDR |= (1<<1);

	//Setup Timer 0
	 SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	 TPM0->SC = TPM_SC_CPWMS(0) | TPM_SC_PS(7);
	 TPM0->MOD = 256-1;
	
	//Setup TPM0 Ch1
	TPM0-> CONTROLS[1].CnSC = TPM_CnSC_ELSA(1)|TPM_CnSC_MSA(0)|TPM_CnSC_MSB(1);

	
	turn_off_blue_led();
	//Start the timer
	TPM0->SC = TPM_SC_CMOD(01);
}
void  set_blue_level( uint8_t duty_cycle){
	TPM0->CONTROLS[1].CnV = duty_cycle;
}
void  turn_off_blue_led(){
	set_blue_level(0);  
}


void initialize_rgbled(){
	//set up PD1
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[1] = (PORTD->PCR[1] &~ (PORT_PCR_MUX_MASK)) | PORT_PCR_MUX(4);
	PTD->PDDR |= (1<<1);
	
	//set up PB19
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[19] = (PORTB->PCR[19]&~(PORT_PCR_MUX_MASK)) | PORT_PCR_MUX(3);
	PTB->PDDR  |= (1<<19) ;
	
	//set up PB18
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[18] = (PORTB->PCR[18]&~(PORT_PCR_MUX_MASK)) | PORT_PCR_MUX(3);
	PTB->PDDR  |= (1<<18) ;
	
	
	//Setup Timer 0 
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	TPM0->SC = TPM_SC_CPWMS(0) | TPM_SC_PS(7);
	TPM0->MOD = 256-1;
	
	//Setup Timer 2 
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	TPM2->SC = TPM_SC_CPWMS(0) | TPM_SC_PS(7);
	TPM2->MOD=256-1;
	
	//Setup TPM0 Ch1
	TPM0-> CONTROLS[1].CnSC = TPM_CnSC_ELSA(1)|TPM_CnSC_MSA(0)|TPM_CnSC_MSB(1);

	//Setup TPM2 Ch1 Ch0
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_ELSA(1 )   |  TPM_CnSC_MSA(0)    |    TPM_CnSC_MSB(1);
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_ELSA(1)    |	TPM_CnSC_MSA(0)    |    TPM_CnSC_MSB(1);
	
	turn_off_red_led();
	turn_off_green_led();
	turn_off_blue_led();
	//Start the timer
	TPM0->SC  |= TPM_SC_CMOD(01);
	TPM2->SC  |= TPM_SC_CMOD(01);
}

void set_rgbled_color_to(uint8_t red, uint8_t green, uint8_t blue){
	
	
	
		set_blue_level(blue);set_green_level(green);set_red_level(red);
		
}

void clear_leds(){ PTB->PSOR |= (1<<18)| (1<<19); PTD-> PSOR |= (1<<1);}
