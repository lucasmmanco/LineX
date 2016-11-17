/* ***************************************************************** */
/* File name:        led_hal.c                                       */
/* File description: This file has a couple of useful functions to   */
/*                   control LEDs board                              */
/* Author name:      lmanco                                          */
/* Creation date:    02out2016                                       */
/* Revision date:    12nov2016                                       */
/* ***************************************************************** */

#include <led_hal.h>
#include <util.h>

#include "KL25Z/line_follower_mapping.h"

#define MAX_LED    6

/* ************************************************ */
/* Method name:        led_initLedSwitch            */
/* Method description: This method configures each  */
/*                     LED's pin in KL25Z           */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void led_initLed(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);

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
/* Method name:        led_setLed                   */
/* Method description: set the led ON               */
/* Input params:       cLedNum    = which LED {0..5}*/
/* Output params:      n/a                          */
/* ************************************************ */
void led_setLed(char cLedNum)
{
    /* sanity check */
    if(cLedNum <= MAX_LED)
    {
        switch(cLedNum)
        {
            case 0:
                GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << LS6_PIN) );
                break;
            case 1:
                GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << LS5_PIN) );
                break;
            case 2:
                GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << LS4_PIN) );
                break;
            case 3:
                GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << LS3_PIN) );
                break;
            case 4:
                GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << LS2_PIN) );
                break;
            case 5:
                GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << LS1_PIN) );
                break;
            default:
                break;
        } /* switch(cLedNum) */

    } /* if(cLedNum <= MAX_LED) */
}



/* ************************************************ */
/* Method name:        led_clearLed                 */
/* Method description: set the led OFF              */
/* Input params:       cLedNum    = which LED {0..5}*/
/* Output params:      n/a                          */
/* ************************************************ */
void led_clearLed(char cLedNum)
{
    /* sanity check */
    if(cLedNum <= MAX_LED)
    {
        switch(cLedNum)
        {
            case 0:
                GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << LS6_PIN) );
                break;
            case 1:
                GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << LS5_PIN) );
                break;
            case 2:
                GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << LS4_PIN) );
                break;
            case 3:
                GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << LS3_PIN) );
                break;
            case 4:
                GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << LS2_PIN) );
                break;
            case 5:
                GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << LS1_PIN) );
                break;
        } /* switch(cLedNum) */

    } /* if(cLedNum <= MAX_LED) */
}

/* ************************************************ */
/* Method name:        led_selAllLeds               */
/* Method description: set the all leds ON          */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void led_setAllLeds(void){
    led_setLed(0);
    led_setLed(1);
    led_setLed(2);
    led_setLed(3);
    led_setLed(4);
    led_setLed(5);
}

/* ************************************************ */
/* Method name:        led_clearAllLeds             */
/* Method description: set the all leds OFF         */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void led_clearAllLeds(void){
    led_clearLed(0);
    led_clearLed(1);
    led_clearLed(2);
    led_clearLed(3);
    led_clearLed(4);
    led_clearLed(5);
}

/* ************************************************ */
/*/Method name:        led_blink                    */
/* Method description: Blink a LED for iTime seconds*/
/*                     for iRep times               */
/* Input params:       cLedNum = LED index          */
/*                     iTime = number of seconds    */
/*                     iRep = number of repetitions */
/* Output params:      n/a                          */
/* ************************************************ */
void led_blink(char cLedNum, int iTime, int iRep){
    int i, j;
    
    for(i=0; i<iRep; i++){
        led_setLed(cLedNum);
        
        for(j=0; j<iTime; j++)
            util_genDelay1ms();
            
        led_clearLed(cLedNum);
        
        for(j=0; j<iTime; j++)
            util_genDelay1ms();
    }
    
}

/* ************************************************ */
/*/Method name:        led_blinkAllLeds             */
/* Method description: Blink all LEDs for iTime     */
/*                     seconds for iRep times       */
/* Input params:       iTime = number of miliseconds*/
/*                     iRep = number of repetitions */
/* Output params:      n/a                          */
/* ************************************************ */
void led_blinkAllLeds(int iTime, int iRep){
    int i, j;
    
    for(i=0; i<iRep; i++){
        led_setAllLeds();
        
        for(j=0; j<iTime; j++)
            util_genDelay1ms();
            
        led_clearAllLeds();
        
        for(j=0; j<iTime; j++)
            util_genDelay1ms();
    }
}
