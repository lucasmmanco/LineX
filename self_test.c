/* ***************************************************************** */
/* File name:        self_test.c                                     */
/* File description: Methods to test all peripherics of LineX        */
/* Author name:      lmanco                                          */
/* Creation date:    02oct2016                                       */
/* Revision date:                                                    */
/* ***************************************************************** */

#include "KL25Z/line_follower_mapping.h"
#include <self_test.h>
#include <adc.h>
#include <led_hal.h>
#include <encoder.h>
#include <ir_sensor.h>
#include <motor_hal.h>
#include <util.h>

#define IR_BASE_VARIATION   1500
#define ENC_BASE_VARIATION  1

//void main_cyclicExecuteIsr(void){
//
//    /* set the cyclic executive flag */
//    uiFlagNextPeriod = 1;
//}

int selfTest_IR(){
    
    int i = 0;
    int iTime = 0;
    int ir_rx_var[6] = {0, 0, 0, 0, 0, 0};
    int error = 0;
    
    led_clearAllLeds();
    
    for(i=0; i<6; i++){
        ir_clearIRTX();
        ir_rx_var[i] = ir_sensor_readIR(i);
        ir_setIRTX();

        //This loop is necessary because of the sensor hysteresis
        for(iTime=0; iTime<20; iTime++)
            util_genDelay10ms();

        ir_rx_var[i] = ir_rx_var[i] - ir_sensor_readIR(i);
        if(ir_rx_var[i] > IR_BASE_VARIATION)
            led_setLed(i);
        else
            error++;
            
    }
    
    ir_clearIRTX();
    
    return error;
}

int selfTest_motor_and_encoder(){
    
    int error = 0;
    int iTime = 0;
    int iEnc0 = 0;
    int iEnc1 = 0;
    
    //tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, main_cyclicExecuteIsr);
    
    //Blinks all Leds to indicates that this self test will start
    //encoder_resetTPMCNT();
    led_blinkAllLeds(100, 10);
    led_clearAllLeds();
    
    motor_set('R', 1, 100);
    motor_set('L', 1, 100);
    
    //while(!uiFlagNextPeriod);
    //    uiFlagNextPeriod = 0;
    
    //This loop is necessary because of the motor hysteresis
    for(iTime=0; iTime<100; iTime++){
        util_genDelay10ms();
    }

    iEnc0 = encoder_getTPMCNT(0);
    iEnc1 = encoder_getTPMCNT(1);
    //iEnc0 = encoder_getTPMCNT(0) - iEnc0;
    //iEnc1 = encoder_getTPMCNT(1) - iEnc1;
    
    motor_stop();
    
    if(iEnc0 > ENC_BASE_VARIATION)
        led_setLed(0);
    else
        error++;
        
    if(iEnc1 > ENC_BASE_VARIATION)
        led_setLed(5);
    else
        error++;
        
    encoder_resetTPMCNT();
    
    return error;
}
