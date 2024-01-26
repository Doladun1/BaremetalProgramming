#include <pwm_sw1.h>


void initialize_pwm_blue_led(){
	//set up PD1
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE->PCR[1] = (PORTE->PCR[1]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(4)|PORT_PCR_IRQC(0);
	PTE->PDDR  |= (1<<1);
	//Setup Timer 1
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	TPM1->SC = TPM_SC_CPWMS(0) | TPM_SC_PS(0);
	TPM0->MOD=100-1;
	turn_off_blue_led();
	//Setup TPM0 Ch0 
	TPM1->CONTROLS[20].CnSC = TPM_CnSC_ELSA(0)    |    TPM_CnSC_ELSB(1) |
			TPM_CnSC_MSA(0)    |    TPM_CnSC_MSB(1);
//		TPM1->CONTROLS[20].CnV = 50-1;

}
void  turn_on_blue_led( uint8_t duty_cycle){
	TPM0->CONTROLS[1].CnV = duty_cycle;
}
void  turn_off_blue_led(){
	turn_on_blue_led(0);  
}
