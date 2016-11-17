/* ***************************************************************** */
/* File name:        pwm.c                                           */
/* File description: Configuring PWM interface                       */
/* Author name:      lmanco                                          */
/* Creation date:    01nov2016                                       */
/* Revision date:    02nov2016                                       */
/* ***************************************************************** */

#include "KL25Z/line_follower_mapping.h"

#include "fsl_tpm_hal.h"
#include "pwm.h"

/* ************************************************** */
/* Method name: 	   timer_initTPM1AsPWM            */
/* Method description: configure Timer1 to act as PWM */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void pwm_initTPM0AsPWM(void)
{
	/* un-gate port clock*/
	SIM_SCGC6 |= SIM_SCGC6_TPM0(CGC_CLOCK_ENABLED); //Enable clock for TPM0

	TPM0_SC &= ~(1 << 5u);   //up counting mode

	TPM0_SC |= TPM_SC_CMOD(0x01); //LPTPM counter increments on every LPTPM counter clock

	TPM0_SC |= TPM_SC_PS(0x00);   //Prescale 1:1

	TPM0_C0SC |= (0b1010 << 2u);
	TPM0_C1SC |= (0b1010 << 2u);
	TPM0_C2SC |= (0b1010 << 2u);
	TPM0_C3SC |= (0b1010 << 2u);
	TPM0_C4SC |= (0b1010 << 2u);
	TPM0_C5SC |= (0b1010 << 2u);

	TPM0_CNT = 0x0000;
	TPM0_MOD = 0x0400;
	TPM0_CONF |= TPM_CONF_DBGMODE(0x3);
	
	TPM0_C0V = 0;
	TPM0_C1V = 0;
	TPM0_C2V = 0;
	TPM0_C3V = 0;
	TPM0_C4V = 0;
	TPM0_C5V = 0;

}


/* ************************************************ */
/* Method name:        timer_setPWMDutyCycle        */
/* Method description: Sets the PWM duty cycle      */
/* Input params:       int iDuty: Duty Cycle from   */
/*                     0 to 100                     */
/* Output params:      n/a                          */
/* ************************************************ */
void pwm_setPWMDutyCycle(int iDuty, int iCH){

	switch(iCH){
		case 0:
			TPM0_C0V = iDuty*(0x0400)/100;
			break;
		case 1:
			TPM0_C1V = iDuty*(0x0400)/100;
			break;
		case 2:
			TPM0_C2V = iDuty*(0x0400)/100;
			break;
		case 3:
			TPM0_C3V = iDuty*(0x0400)/100;
			break;
		case 4:
			TPM0_C4V = iDuty*(0x0400)/100;
			break;
		case 5:
			TPM0_C5V = iDuty*(0x0400)/100;
			break;
		default:
			break;
	}
}

/* ************************************************ */
/* Method name:        pwm_module/-init		        */
/* Method description: Initialize the pwm motor 	*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void pwm_module_init(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTD(CGC_CLOCK_ENABLED);

    /* set pins as PWM */
	PORTD_PCR0 |= PORT_PCR_MUX(4U); // ALT3
    PORTD_PCR1 |= PORT_PCR_MUX(4U);	// ALT3
	PORTD_PCR2 |= PORT_PCR_MUX(4U); // ALT3
    PORTD_PCR3 |= PORT_PCR_MUX(4U);	// ALT3

}
