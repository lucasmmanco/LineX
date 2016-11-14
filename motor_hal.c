/* ***************************************************************** */
/* File name:        motor_hal.c                                     */
/* File description: Methods of motor                                */
/* Author name:      lmanco                                          */
/* Creation date:    01nov2016                                       */
/* Revision date:    02nov2016                                       */
/* ***************************************************************** */

#include "KL25Z/line_follower_mapping.h"

#include "fsl_clock_manager.h"
#include "fsl_port_hal.h"
#include "fsl_gpio_hal.h"

#include "motor_hal.h"
#include "pwm.h"

/* **************************************************** */
/* Method name: 	   motor_init                       */
/* Method description: Initialize the PWM for motors    */
/* Input params:	   n/a 							    */
/* Outpu params:	   n/a 							    */
/* **************************************************** */
void motor_init(void){
    
    pwm_initTPM0AsPWM();
    pwm_module_init();
}

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
void motor_set(char cMotor, int iDir, int iDuty){
    
    if(cMotor == 'R'){
        if(iDir == 1){
            pwm_setPWMDutyCycle(iDuty, 2);
            pwm_setPWMDutyCycle(0, 0);
        }
        else{        
            pwm_setPWMDutyCycle(0, 2);
            pwm_setPWMDutyCycle(iDuty, 0);
        }
    }
    else if(cMotor == 'L'){
        if(iDir == 0){
            pwm_setPWMDutyCycle(iDuty, 1);
            pwm_setPWMDutyCycle(0, 3);
        }
        else{        
            pwm_setPWMDutyCycle(0, 1);
            pwm_setPWMDutyCycle(iDuty, 3);
        }
    }
    
}

/* **************************************************** */
/* Method name: 	   motor_stop                       */
/* Method description: Stop all motors                  */
/* Input params:	   n/a 							    */
/* Outpu params:	   n/a 							    */
/* **************************************************** */
void motor_stop(){
    pwm_setPWMDutyCycle(0, 0);
    pwm_setPWMDutyCycle(0, 1);
    pwm_setPWMDutyCycle(0, 2);
    pwm_setPWMDutyCycle(0, 3);
}
