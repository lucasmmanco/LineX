/* ***************************************************************** */
/* File name:        encoder.h  	                                 */
/* File description: Header File constaing the methods to initialize */
/*					 and read the encoder of the peripheral board    */
/*                                                                   */
/* Author name:      Lucas Manco                                     */
/* Creation date:    02nov2016                                       */
/* Revision date:    03nov2016                                       */
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
/*					   or TPM1_CNT                  */
/* Input params:       enc_index = 0 for rigth enc  */
/*                                 1 for left enc   */
/* Output params:      iCount = count value         */
/* ************************************************ */
int encoder_getTPMCNT(int enc_index);

/* ************************************************ */
/* Method name:        resetTPMCNT      	        */
/* Method description: Resets manually the TPM0_CNT */
/*                     and TPM1_CNT registers       */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void encoder_resetTPMCNT();




#endif /* SOURCES_ENCODER_H_ */
