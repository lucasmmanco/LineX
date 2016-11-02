/* ***************************************************************** */
/* File name:        encoder.h  	                                 */
/* File description: Header File constaing the methods to initialize */
/*					 and read the encoder of the peripheral board    */
/*                                                                   */
/* Author name:      Henrique Amitay & Lucas Manco                   */
/* Creation date:    20may2016                                       */
/* Revision date:    03jun2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_ENCODER_H_
#define SOURCES_ENCODER_H_

/* ************************************************ */
/* Method name:        initEncoderConfig  	        */
/* Method description: Set the configuration of the */
/*					   encoder ports and TPM0       */
/*					   registers                    */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void encoder_initEncoderConfig();

/* ************************************************ */
/* Method name:        getTPMCNT        	        */
/* Method description: Returns the TPM0_CNT value   */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
int encoder_getTPMCNT();

/* ************************************************ */
/* Method name:        resetTPMCNT      	        */
/* Method description: Resets manually the TPM0_CNT */
/*                     register                     */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void encoder_resetTPMCNT();




#endif /* SOURCES_ENCODER_H_ */
