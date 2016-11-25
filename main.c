

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
#define CYCLIC_EXECUTIVE_PERIOD         500*1000 /* micro seconds */

volatile unsigned int uiFlagNextPeriod = 0;         /* cyclic executive flag */

int iEncR = 0;
int iEncL = 0;
int flagEnc = 0;
float iCycleTime = 0.075; //(CYCLIC_EXECUTIVE_PERIOD/1000000);

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
    
    //if(flagEnc == 0){
        iEncR = encoder_getTPMCNT(0);
        iEncL = encoder_getTPMCNT(1);
        //flagEnc = 0;
    //}
    //else
    //    flagEnc++;
}

int main(void){

    main_boardInit();

    tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, main_cyclicExecuteIsr);

    int position = 0;
    
    float fRpsR, fRpsL, fRefL, fRefR;
    PID_MOTOR pidR, pidL;
    PID_SPLINE pidS;
    
    int iPwmRefR[2] = {0, 97}; //pwm[0] = min pwm e pwm[1] = max pwm
    int iPwmRefL[2] = {0, 97};
    float fVelRefR[2] = {0.0, 0.0}; //vel[0] = min vel e vel[1] = max vel
    float fVelRefL[2] = {0.0, 0.0};
    int iPwmR = 60;
    int iPwmL = 60;
    
    int stt = 0;
    int iTimer = 0;
    int ir_Base[12];
    float velRange[2] = {0.5, 2.0};
    
    int error = selfTest_IR();
    //error = selfTest_motor_and_encoder();

    //for(iTimer=0; iTimer < 40; iTimer++)
    //    util_genDelay10ms();

    led_setAllLeds();
    ir_setIRTX();
    ir_sensor_runCalibration(&ir_Base);
    
    selfTest_motorCalibration(fVelRefR, fVelRefL, iPwmRefR, iPwmRefL);
    
    
    
    if(fVelRefL[0] > fVelRefR[0])
        velRange[0] = fVelRefL[0];
    else
        velRange[0] = fVelRefL[0];
        
    if(fVelRefL[1] < fVelRefR[1])
        velRange[1] = fVelRefL[1];
    else
        velRange[1] = fVelRefL[1];
    
    pid_motorInitializate(&pidR, fVelRefR, iPwmRefR);
    pid_motorInitializate(&pidL, fVelRefL, iPwmRefL);
    pid_splineInitializate(&pidS, velRange);
    
    pidR.kp = 0.0634;   //0.2180;   //0.3645;       //0.2180;     //0.2645;
    pidR.ki = 0.1589;   //0.2595;   //0.5455;       //0.2560;     //0.521;
    pidR.kd = 0.0002;   //0.0041;   //0.0045;       //0.0041;     //0.0045;
              
    pidL.kp = 0.0644;   //0.2205;   //0.2545;
    pidL.ki = 0.1599;   //0.2605;   //0.3105;
    pidL.kd = 0.0002;   //0.0045;   //0.0045;
    
    pidS.kp = 10;
    pidS.ki = 25;
    pidS.kd = 2;
    
    pidR.ref = 0.5;
    pidL.ref = 0.5;
    fRefR = 0.5;
    fRefL = 0.5;
    
    led_blinkAllLeds(200, 5);
    
    tc_installLptmr0(75000, main_cyclicExecuteIsr);

    while(1U){

        //led_clearAllLeds();
        ir_setIRTX();
        
        fRpsR = ((float)(iEncR)/(20.0*iCycleTime));
        fRpsL = ((float)(iEncL)/(20.0*iCycleTime));
        
        iPwmR = pid_motorUpdate(&pidR, fRpsR);
        iPwmL = pid_motorUpdate(&pidL, fRpsL);
        
        motor_set('R', 1, iPwmR);
        motor_set('L', 1, iPwmL);

        position = ir_sensor_returnLow(ir_Base);
        pid_splineUpdate(&pidS, position, &fRefR, &fRefL, 0.5);
        
        pidR.ref = fRefR;
        pidL.ref = fRefL;
        
        //Somente para testes
        //position = ir_sensor_returnPosiTest(ir_rx_val);
        
        
        while(!uiFlagNextPeriod);
        uiFlagNextPeriod = 0;

    }//end while(1U)

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
