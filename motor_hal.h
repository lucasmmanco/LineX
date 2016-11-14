/* ***************************************************************** */
/* File name:        motor_hal.h                                     */
/* File description: Header File of motor                            */
/* Author name:      lmanco                                          */
/* Creation date:    01nov2016                                       */
/* Revision date:    02nov2016                                       */
/* ***************************************************************** */

/* **************************************************** */
/* Method name: 	   motor_init                       */
/* Method description: Initialize the PWM for motors    */
/* Input params:	   n/a 							    */
/* Outpu params:	   n/a 							    */
/* **************************************************** */
void motor_init(void);

/* **************************************************** */
/* Method name: 	   motor_set                        */
/* Method description: Set the PWM Duty Cycle and       */
/*                     Direction for each motor         */
/* Input params:       char cMotor: 'R' for right motor */
/*                                  'L' for left motor  */
/*                     int iDir: 1 for ahead 0 to back  */
/*                     int iDuty: Duty Cycle (%)        */
/* Outpu params:	   n/a 							    */
/* **************************************************** */
void motor_set(char cMotor, int iDir, int iDuty);

/* **************************************************** */
/* Method name: 	   motor_stop                       */
/* Method description: Stop all motors                  */
/* Input params:	   n/a 							    */
/* Outpu params:	   n/a 							    */
/* **************************************************** */
void motor_stop(void);