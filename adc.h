/*
 * File name: adc.h
 *
 *  Created on: 06/06/2016
 *      Author: msoliveira
 */

/* ************************************************** */
/* Method name: 	   adc_initADCModule              */
/* Method description: configure ADC module           */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void adc_initADCModule(void);

/* ************************************************** */
/* Method name: 	   adc_initConvertion             */
/* Method description: init a conversion from D to A  */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void adc_initConvertion(int sensorIndex);

/* ************************************************** */
/* Method name: 	   adc_isAdcDone                  */
/* Method description: check if conversion is done    */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
int adc_isAdcDone(void);

/* ************************************************** */
/* Method name: 	   adc_getConvertionValue         */
/* Method description: retrieve converted value       */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
int adc_getConvertionValue(void);
