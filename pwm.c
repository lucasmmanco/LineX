/* ***************************************************************** */
/* File name:        pwm.c                                           */
/* File description: Configuring PWM interface                       */
/* Author name:      lmanco                                          */
/* Creation date:    01nov2016                                       */
/* Revision date:    02nov2016                                       */
/* ***************************************************************** */

#include "KL25Z/line_follower_mapping.h"

#include "pwm_hal.h"

/* ************************************************** */
/* Method name: 	   timer_initTPM1AsPWM            */
/* Method description: configure Timer1 to act as PWM */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void pwm_initTPM1AsPWM(void)
{
	/* un-gate port clock*/
	SIM_SCGC6 |= SIM_SCGC6_TPM1(CGC_CLOCK_ENABLED); //Enable clock for TPM1

	TPM1_SC &= ~(1 << 5u);   //up counting mode

	TPM1_SC &= ~(1 << 4u);   //LPTPM Counter increments on every LPTPM counter clock
	TPM1_SC |=  (1 << 3u);

	TPM1_SC &= ~(1 << 2u);   //Prescale 1:1
	TPM1_SC &= ~(1 << 1u);
	TPM1_SC &= ~(1 << 0u);

	TPM1_C1SC |= (0b1010 << 2u);

	TPM1_CNT = 0x0000;
	TPM1_MOD = 0x0400;

}


/* ************************************************ */
/* Method name:        timer_setPWMDutyCycle        */
/* Method description: Sets the PWM duty cycle      */
/* Input params:       int iDuty: Duty Cycle from   */
/*                     0 to 100                     */
/* Output params:      n/a                          */
/* ************************************************ */
void pwm_setPWMDutyCycle(int iDuty){

	int iPassedDuty;

	//Sanity check

	TPM1_C1V = iDuty*(0x0400)/100;
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
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pins as PWM */
    PORTA_PCR4 |= PORT_PCR_MUX(1U);	// ALT1
	PORTA_PCR5 |= PORT_PCR_MUX(1U); // ALT1

}
