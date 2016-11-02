/* ***************************************************************** */
/* File name:        ledswi_hal.c                                    */
/* File description: This file has a couple of useful functions to   */
/*                   control LEDs and Switches from peripheral board */
/* Author name:      dloubach                                        */
/* Creation date:    20jan2015                                       */
/* Revision date:    25fev2016                                       */
/* ***************************************************************** */

#include <led_hal.h>

#include "KL25Z/line_follower_mapping.h"

#define USING_OPENSDA_DEBUG

/* ************************************************ */
/* Method name:        ledswi_initLedSwitch         */
/* Method description: As the hardware board was    */
/*                     designed with LEDs/Switches  */
/*                     sharing the same pins, this  */
/*                     method configures how many   */
/*                     LEDS and switches will be    */
/*                     available for the application*/
/* Input params:       cLedNum    = num of LEDs     */
/*                     cSwitchNum = num of Switches */
/*                     cLedNum +                    */
/*                     cSwitchNum <= MAX_LED    */
/* Outpu params:       n/a                          */
/* ************************************************ */
void led_initLed(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pin as gpio */
    PORTE_PCR20 = PORT_PCR_MUX(LS1_ALT);
    PORTE_PCR21 = PORT_PCR_MUX(LS2_ALT);
    PORTE_PCR22 = PORT_PCR_MUX(LS3_ALT);
    PORTE_PCR23 = PORT_PCR_MUX(LS4_ALT);
    PORTE_PCR29 = PORT_PCR_MUX(LS5_ALT);
    PORTE_PCR30 = PORT_PCR_MUX(LS6_ALT);
    
    GPIOE_PDDR |= GPIO_PDDR_PDD(LS1_DIR_OUTPUT | LS2_DIR_OUTPUT | LS3_DIR_OUTPUT | LS4_DIR_OUTPUT | LS5_DIR_OUTPUT | LS6_DIR_OUTPUT);
}



/* ************************************************ */
/* Method name:        ledswi_setLed                */
/* Method description: set the led ON               */
/* Input params:       cLedNum    = which LED {1..4}*/
/* Outpu params:       n/a                          */
/* ************************************************ */
void led_setLed(char cLedNum)
{
    /* sanity check */
    if(cLedNum <= MAX_LED)
    {
        switch(cLedNum)
        {
            case 1:
                GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << LS1_PIN) );
                break;
            case 2:
                GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << LS2_PIN) );
                break;
            case 3:
                GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << LS3_PIN) );
                break;
            case 4:
                GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << LS4_PIN) );
                break;
            case 5:
                GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << LS5_PIN) );
                break;
            case 6:
                GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << LS6_PIN) );
                break;
        } /* switch(cLedNum) */

    } /* if(cLedNum <= MAX_LED) */
}



/* ************************************************ */
/* Method name:        ledswi_clearLed              */
/* Method description: set the led OFF              */
/* Input params:       cLedNum    = which LED {1..4}*/
/* Outpu params:       n/a                          */
/* ************************************************ */
void led_clearLed(char cLedNum)
{
    /* sanity check */
    if(cLedNum <= MAX_LED)
    {
        switch(cLedNum)
        {
            case 1:
                GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << LS1_PIN) );
                break;
            case 2:
                GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << LS2_PIN) );
                break;
            case 3:
                GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << LS3_PIN) );
                break;
            case 4:
                GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << LS4_PIN) );
                break;
            case 5:
                GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << LS5_PIN) );
                break;
            case 6:
                GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << LS6_PIN) );
                break;
        } /* switch(cLedNum) */

    } /* if(cLedNum <= MAX_LED) */
}