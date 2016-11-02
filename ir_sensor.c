/* ***************************************************************** */
/* File name:        ir_sensor.c                                    */
/* File description: This file has a couple of useful functions to   */
/*                   control and read IR sensors of the Line Follower*/
/* Author name:      lmanco                                          */
/* Creation date:    07oct2016                                       */
/* Revision date:    07oct2016                                       */
/* ***************************************************************** */

#include "ir_sensor.h"

#include "KL25Z/line_follower_mapping.h"

void ir_initIRTX(void){
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pin as gpio */
    PORTE_PCR5 = PORT_PCR_MUX(IR_TX_PIN);
    
    GPIOE_PDDR |= GPIO_PDDR_PDD(IR_TX_DIR_OUTPUT);
}

void ir_setIRTX(void){
    GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << IR_TX_PIN));
}

void ir_clearIRTX(void){
    GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << IR_TX_PIN));
}