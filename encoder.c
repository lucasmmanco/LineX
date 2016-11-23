/* ***************************************************************** */
/* File name:        encoder.c  	                                 */
/* File description: Header File constaing the methods to initialize */
/*					 and read the encoder of the peripheral board    */
/*                                                                   */
/* Author name:      Lucas Manco                                     */
/* Creation date:    02nov2016                                       */
/* Revision date:    03nov2016                                       */
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
	
	SIM_SCGC6 |= SIM_SCGC6_TPM1(CGC_CLOCK_ENABLED);
	SIM_SCGC6 |= SIM_SCGC6_TPM2(CGC_CLOCK_ENABLED);
	SIM_SCGC5 |= SIM_SCGC5_PORTC(CGC_CLOCK_ENABLED);
	
	/*Alt*/
	PORTC_PCR12 |= PORT_PCR_MUX(ENCODER_R_ALT);
	PORTC_PCR13 |= PORT_PCR_MUX(ENCODER_L_ALT);
	
	/* Sets the TPMSRC to OSCERCLK */
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0x02);
	
	SIM_SOPT2 |= (0b1 << 7U);
	SIM_SOPT2 |= (0b1 << 6U);
	SIM_SOPT2 &= ~(0b1 << 5U);
	
	/*Sets the TPM1CLKSEL to TPM_CLKIN0*/
	SIM_SOPT4 |= SIM_SOPT4_TPM1CLKSEL(0);
	/*Sets the TPM2CLKSEL to TPM_CLKIN1*/
	SIM_SOPT4 |= SIM_SOPT4_TPM2CLKSEL(1);
	
	/*Sets the TMP1 preescaler to 000 (1:1)*/
	TPM1_SC |= TPM_SC_CMOD(0x02);
	TPM1_SC	|= TPM_SC_PS(0);
	
	/*Sets the TMP2 preescaler to 000 (1:1)*/
	TPM2_SC |= TPM_SC_CMOD(0x02);
	TPM2_SC	|= TPM_SC_PS(0);	
	

}

/* ************************************************ */
/* Method name:        getTPMCNT        	        */
/* Method description: Returns the TPM0_CNT value   */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
int encoder_getTPMCNT(int enc_index){
	int value = 0;
	
	if(enc_index == 1){
		value = TPM2_CNT;
		TPM2_CNT = 0;
	}
	else{
		value =  TPM1_CNT;
		TPM1_CNT = 0;
	}
	
	return value;

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
	TPM2_CNT = 0;
	TPM1_CNT = 0;
}
