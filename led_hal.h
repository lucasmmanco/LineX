/* ***************************************************************** */
/* File name:        led_hal.h                                       */
/* File description: Header file containing the function/methods     */
/*                   prototypes of led_hal.c                          */
/* Author name:      lmanco                                          */
/* Creation date:    02out2016                                       */
/* Revision date:    12nov2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_LED_HAL_H_
#define SOURCES_LED_HAL_H_

/* ************************************************ */
/* Method name:        led_initLedSwitch            */
/* Method description: This method configures each  */
/*                     LED's pin in KL25Z           */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void led_initLed(void);


/* ************************************************ */
/* Method name:        led_setLed                   */
/* Method description: set the led ON               */
/* Input params:       cLedNum    = which LED {0..5}*/
/* Output params:      n/a                          */
/* ************************************************ */
void led_setLed(char cLedNum);


/* ************************************************ */
/* Method name:        led_clearLed                 */
/* Method description: set the led OFF              */
/* Input params:       cLedNum    = which LED {0..5}*/
/* Output params:      n/a                          */
/* ************************************************ */
void led_clearLed(char cLedNum);

/* ************************************************ */
/* Method name:        led_selAllLeds               */
/* Method description: set the all leds ON          */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void led_setAllLeds(void);

/* ************************************************ */
/* Method name:        led_clearAllLeds             */
/* Method description: set the all leds OFF         */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void led_clearAllLeds(void);

/* ************************************************ */
/*/Method name:        led_blink                    */
/* Method description: Blink a LED for iTime seconds*/
/*                     for iRep times               */
/* Input params:       cLedNum = LED index          */
/*                     iTime = number of seconds    */
/*                     iRep = number of repetitions */
/* Output params:      n/a                          */
/* ************************************************ */
void led_blink(char cLedNum, int iTime, int iRep);

/* ************************************************ */
/*/Method name:        led_blinkAllLeds             */
/* Method description: Blink all LEDs for iTime     */
/*                     seconds for iRep times       */
/* Input params:       iTime = number of miliseconds*/
/*                     iRep = number of repetitions */
/* Output params:      n/a                          */
/* ************************************************ */
void led_blinkAllLeds(int iTime, int iRep);

#endif /* SOURCES_LEDSWI_LEDSWI_HAL_H_ */
