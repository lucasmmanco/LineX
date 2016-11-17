/* ***************************************************************** */
/* File name:        pwm.h                                           */
/* File description: Configuring PWM interface                       */
/* Author name:      lmanco                                          */
/* Creation date:    01nov2016                                       */
/* Revision date:    02nov2016                                       */
/* ***************************************************************** */

/* ************************************************** */
/* Method name: 	   pwm_initTPM1AsPWM             */
/* Method description: configure Timer1 to act as PWM */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void pwm_initTPM0AsPWM(void);

/* ************************************************ */
/* Method name:        pwm_coolerfan_init         */
/* Method description: Initialize the cooler device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void pwm_setPWMDutyCycle(int iDuty, int iCH);

/* ************************************************ */
/* Method name:        pwm_coolerfan_init         */
/* Method description: Sets the PWM duty cycle      */
/* Input params:       int iDuty: Duty Cycle from   */
/*                     0 to 100                     */
/* Output params:      n/a                          */
/* ************************************************ */
void pwm_module_init(void);