/* ***************************************************************** */
/* File name:        ledswi_hal.h                                    */
/* File description: Header file containing the function/methods     */
/*                   prototypes of ledswi.c                          */
/* Author name:      dloubach                                        */
/* Creation date:    09jan2015                                       */
/* Revision date:    25fev2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_LED_HAL_H_
#define SOURCES_LED_HAL_H_

#define MAX_LED        06

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
void led_initLed(void);


/* ************************************************ */
/* Method name:        ledswi_setLed                */
/* Method description: set the led ON               */
/* Input params:       cLedNum    = which LED {1..4}*/
/* Outpu params:       n/a                          */
/* ************************************************ */
void led_setLed(char cLedNum);


/* ************************************************ */
/* Method name:        ledswi_clearLed              */
/* Method description: set the led OFF              */
/* Input params:       cLedNum    = which LED {1..4}*/
/* Outpu params:       n/a                          */
/* ************************************************ */
void led_clearLed(char cLedNum);



#endif /* SOURCES_LEDSWI_LEDSWI_HAL_H_ */
