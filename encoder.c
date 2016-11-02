/* ***************************************************************** */
/* File name:        encoder.c  	                                 */
/* File description: Header File constaing the methods to initialize */
/*					 and read the encoder of the peripheral board    */
/*                                                                   */
/* Author name:      Henrique Amitay & Lucas Manco                   */
/* Creation date:    20may2016                                       */
/* Revision date:    03jun2016                                       */
/* ***************************************************************** */

#include "KL25Z/line_follower_mapping.h"
/* system includes */
#include "fsl_clock_manager.h"
#include "fsl_port_hal.h"
#include "fsl_tpm_hal.h"
#include "encoder.h"

/* ************************************************ */
/* Method name:        initEncoderConfig  	        */
/* Method description: Set the configuration of the */
/*					   encoder ports and TPM0       */
/*					   registers                    */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void encoder_initEncoderConfig(){

	/*Alt*/
	SIM_SCGC5 |= SIM_SCGC5_PORTE(ENCODER_PIN);
	PORTE_PCR29 |= PORT_PCR_MUX(ENCODER_ALT);

	/* Sets the TPMSRC to OSCERCLK */
	SIM_SOPT2 |=  (0b1 << 25U);
	SIM_SOPT2 &=  ~(0b1 << 24U);

	SIM_SOPT2 |= (0b1 << 7U);
	SIM_SOPT2 |= (0b1 << 6U);
	SIM_SOPT2 &= ~(0b1 << 5U);

	/*Sets the TPM0CLKSEL to TPM_CLKIN0*/
	SIM_SOPT4 &= ~(1 << 24U);

	/*Enables the TPM0 Clock Gate Control*/
	SIM_SCGC6 |= (1 << 24U);

	/*Sets the TMP0 preescaler to 000 (1:1)*/
	TPM0_SC &= ~(1 << 0U);
	TPM0_SC &= ~(1 << 1U);
	TPM0_SC &= ~(1 << 2U);
	TPM0_SC &= ~(1 << 3U);
	TPM0_SC |= (1 << 4U);


}

/* ************************************************ */
/* Method name:        getTPMCNT        	        */
/* Method description: Returns the TPM0_CNT value   */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
int encoder_getTPMCNT(){

	int iCount = TPM0_CNT;

	return iCount;
}

/* ************************************************ */
/* Method name:        resetTPMCNT      	        */
/* Method description: Resets manually the TPM0_CNT */
/*                     register                     */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void encoder_resetTPMCNT()
{
	TPM0_CNT = 0;
}
