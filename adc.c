/* ***************************************************************** */
/* File name:        adc.c                                           */
/* File description: ADC configuration and utilization functions     */
/* Author name:      lmanco                                          */
/* Creation date:    02oct2016                                       */
/* Revision date:                                                    */
/* ***************************************************************** */

#include "KL25Z/line_follower_mapping.h"

#define ADC0_SC1A_COCO (ADC0_SC1A >> 7)

/* ************************************************** */
/* Method name: 	   adc_initADCModule              */
/* Method description: configure ADC module           */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void adc_initADCModule(void){

	/* un-gate port clock*/
	SIM_SCGC6 |= SIM_SCGC6_ADC0(CGC_CLOCK_ENABLED);	//Enable clock for ADC

    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTB(CGC_CLOCK_ENABLED);
    SIM_SCGC5 |= SIM_SCGC5_PORTC(CGC_CLOCK_ENABLED);

    /* set pin as ADC In */
    PORTB_PCR0 |= PORT_PCR_MUX(0u);   //IR1
    PORTB_PCR1 |= PORT_PCR_MUX(0u);   //IR2
    PORTB_PCR2 |= PORT_PCR_MUX(0u);   //IR1
    PORTB_PCR3 |= PORT_PCR_MUX(0u);   //IR2
    PORTC_PCR1 |= PORT_PCR_MUX(0u);   //IR1
    PORTC_PCR2 |= PORT_PCR_MUX(0u);   //IR2

    ADC0_CFG1 |= (ADC_CFG1_ADICLK(0b01) | ADC_CFG1_MODE(0b11) | ADC_CFG1_ADLSMP(0b0) | ADC_CFG1_ADIV(0b00) | ADC_CFG1_ADLPC(0b0));
    
    ADC0_SC2 |= (ADC_SC2_REFSEL(0b00) | ADC_SC2_DMAEN(0b0) | ADC_SC2_ACFE(0b0) | ADC_SC2_ADTRG(0b0));
    
    ADC0_CFG2 |= (ADC_CFG2_ADLSTS(0b00) | ADC_CFG2_ADHSC(0b0) | ADC_CFG2_ADACKEN(0b0) | ADC_CFG2_MUXSEL(0b0));

}

/* ************************************************** */
/* Method name: 	   adc_initConvertion             */
/* Method description: init a conversion from D to A  */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void adc_initConvertion(char sensorIndex){
    
    ADC0_SC1A = ADC_SC1_AIEN(0);
    ADC0_SC1A = ADC_SC1_DIFF(0);
    
	switch(sensorIndex){
		case 0:
			ADC0_SC1A = ADC_SC1_ADCH(0b01000);
			break;
		case 1:
			ADC0_SC1A = ADC_SC1_ADCH(0b01001);
			break;
		case 2:
			ADC0_SC1A = ADC_SC1_ADCH(0b01100);
			break;
		case 3:
			ADC0_SC1A = ADC_SC1_ADCH(0b01101);
			break;
		case 4:
			ADC0_SC1A = ADC_SC1_ADCH(0b01011);
			break;
		case 5:
			ADC0_SC1A = ADC_SC1_ADCH(0b01111);
			break;
		default:
			break;
	}

    /*
    ADC_SC1_COCO(x) // conversion complete flag HW-set
    ADC_SC1_AIEN(x) // conversion complete interrupt disables	
	ADC_SC1_DIFF(x) // selects single-ended convertion
	ADC_SC1_ADCH(x) // selects channel, view 3.7.1.3.1 ADC0 Channel Assignment ADC0_SE4a from datasheet
	*/
}

/* ************************************************** */
/* Method name: 	   adc_isAdcDone                  */
/* Method description: check if conversion is done    */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
int adc_isAdcDone(void)
{
	if(ADC0_SC1A_COCO) // watch complete convertion flag
	{
		return 1; // if the conversion is complete, return 1
	}
	else
		return 0; // if the conversion is still taking place, return 0

}

/* ************************************************** */
/* Method name: 	   adc_getConvertionValue         */
/* Method description: retrieve converted value       */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
int adc_getConvertionValue(void)
{
	return ADC0_RA; // return the register value that keeps the result of convertion
}
