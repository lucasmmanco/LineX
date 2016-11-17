

#include "KL25Z/line_follower_mapping.h"
#include "mcg_hal.h"
#include "util.h"
#include "adc.h"
#include "led_hal.h"
#include "ir_sensor.h"
#include "tc_hal.h"
#include "motor_hal.h"
#include "encoder.h"
#include "self_test.h"

/* system includes */
#include "fsl_debug_console.h"

/* defines */
#define CYCLIC_EXECUTIVE_PERIOD         50*10000 /* 10000 100 micro seconds */

volatile unsigned int uiFlagNextPeriod = 0;         /* cyclic executive flag */

float fRpsR = 0.0;
float fRpsL = 0.0;
float iCycleTime = 0.5; //(CYCLIC_EXECUTIVE_PERIOD/1000000);

void main_boardInit(void){
    ////Clock
    mcg_clockInit();
    //ADC
    adc_initADCModule();
    //LEDs
    led_initLed();
    //IR TX
    ir_initIRTX();
    ////MOTORS
    motor_init();
    //Encoders
    encoder_initEncoderConfig();

}

/* ************************************************ */
/* Method name:        main_cyclicExecuteIsr        */
/* Method description: cyclic executive interrupt   */
/*                     service routine              */
/*                     Reads encoder and excute the */
/*                     PID controler                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void main_cyclicExecuteIsr(void){

    /* set the cyclic executive flag */
    uiFlagNextPeriod = 1;
    fRpsR = encoder_getTPMCNT(0);
    fRpsL = encoder_getTPMCNT(1);

    encoder_resetTPMCNT();
}

int main(void){

    main_boardInit();

    tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, main_cyclicExecuteIsr);

    int position = 0;
    
    float rpsR, rpsL;
    int rpmR, rpmL;

    int stt = 0;
    int iTimer = 0;
    int ir_rx_index = 0;
    int ir_rx_val[6] = {0, 0, 0, 0, 0, 0};
    int ir_Base[12], ir_normalized[6];
    
    //int error = selfTest_IR();
    //error = selfTest_motor_and_encoder();
    //
    //for(iTimer=0; iTimer < 100; iTimer++)
    //    util_genDelay10ms();
    //
    led_setAllLeds();
    ir_setIRTX();
    ir_sensor_runCalibration(&ir_Base);
    
    //motor_stop();
    
    led_blinkAllLeds(250, 5);

    while(1U){

        //led_clearAllLeds();
        ir_setIRTX();
        //
        //rpsR = fRpsR/iCycleTime;
        //rpsL = fRpsL/iCycleTime;
        //
        //motor_set('R', 1, 70);
        //motor_set('L', 0, 50);

        //rpmR = encoder_getTPMCNT(0);
        //rpmL = encoder_getTPMCNT(1);
        //encoder_resetTPMCNT();
        
        //ir_sensor_runCalibration(IR_VectorValue);
        //ir_sensor_readNormal(&ir_Base, &ir_normalized);
        position = ir_sensor_returnLow(ir_Base);
        //position = ir_sensor_returnPosiTest(ir_rx_val);
        
        
        while(!uiFlagNextPeriod);
        uiFlagNextPeriod = 0;

    }//end while(1U)

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
