

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
#include "pid.h"

/* system includes */
#include "fsl_debug_console.h"

/* defines */
#define CYCLIC_EXECUTIVE_PERIOD         1000*1000 /* 10000 100 micro seconds */

volatile unsigned int uiFlagNextPeriod = 0;         /* cyclic executive flag */

int iEncR = 0;
int iEncL = 0;
float iCycleTime = 1; //(CYCLIC_EXECUTIVE_PERIOD/1000000);

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
    iEncR = encoder_getTPMCNT(0);
    iEncL = encoder_getTPMCNT(1);
}

int main(void){

    main_boardInit();

    tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, main_cyclicExecuteIsr);

    int position = 0;
    
    float fRpsR, fRpsL;
    PID_MOTOR pidR, pidL;
    
    int iPwmRefR[2] = {0, 97}; //pwm[0] = min pwm e pwm[1] = max pwm
    int iPwmRefL[2] = {0, 97};
    float fVelRefR[2] = {0.0, 0.0}; //vel[0] = min vel e vel[1] = max vel
    float fVelRefL[2] = {0.0, 0.0};
    int iPwmR = 0;
    int iPwmL = 0;
    
    int stt = 0;
    int iTimer = 0;
    int ir_rx_index = 0;
    int ir_rx_val[6] = {0, 0, 0, 0, 0, 0};
    int ir_Base[12], ir_normalized[6];
    
    //int error = selfTest_IR();
    //error = selfTest_motor_and_encoder();

    //for(iTimer=0; iTimer < 40; iTimer++)
    //    util_genDelay10ms();

    led_setAllLeds();
    //ir_setIRTX();
    //ir_sensor_runCalibration(&ir_Base);

    selfTest_motorCalibration(fVelRefR, fVelRefL, iPwmRefR, iPwmRefL);
        
    pid_motorInitializate(&pidR, fVelRefR, iPwmRefR);
    pid_motorInitializate(&pidL, fVelRefL, iPwmRefL);
    
    pidR.kp = 0.2180;   //0.3645;       //0.2180;     //0.2645;
    pidR.ki = 0.2595;   //0.5455;       //0.2560;     //0.521;
    pidR.kd = 0.0041;   //0.0045;       //0.0041;     //0.0045;
    
    pidL.kp = 0.2205;   //0.2545;
    pidL.ki = 0.2605;   //0.3105;
    pidL.kd = 0.0045;   //0.0045;
    
    led_blinkAllLeds(200, 5);

    while(1U){

        //led_clearAllLeds();
        //ir_setIRTX();
        
        pidR.ref = 1.9;
        pidL.ref = 1.9;
        
        fRpsR = ((float)(iEncR)/(20.0*iCycleTime));
        fRpsL = ((float)(iEncL)/(20.0*iCycleTime));
        
        iPwmR = pid_motorUpdate(&pidR, fRpsR);
        iPwmL = pid_motorUpdate(&pidL, fRpsL);
        
        motor_set('R', 1, iPwmR);
        motor_set('L', 1, iPwmL);

      
        //ir_sensor_runCalibration(IR_VectorValue);
        //ir_sensor_readNormal(&ir_Base, &ir_normalized);
        //position = ir_sensor_returnLow(ir_Base);
        //position = ir_sensor_returnPosiTest(ir_rx_val);
        
        
        while(!uiFlagNextPeriod);
        uiFlagNextPeriod = 0;

    }//end while(1U)

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
