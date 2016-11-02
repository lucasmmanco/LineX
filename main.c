

#include "KL25Z/line_follower_mapping.h"
#include "mcg_hal.h"
#include "adc.h"
#include "led_hal.h"
#include "ir_sensor.h"
#include "tc_hal.h"

/* system includes */
#include "fsl_debug_console.h	"

/* defines */
#define CYCLIC_EXECUTIVE_PERIOD         50*10000 /* 10000 100 micro seconds */

volatile unsigned int uiFlagNextPeriod = 0;         /* cyclic executive flag */

void main_boardInit(void){
    //Clock
    mcg_clockInit();

    //ADC
     adc_initADCModule();
    //LEDs
    led_initLed();
    //IR TX
    ir_initIRTX();

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

}

int main(void){
    main_boardInit();

    tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, main_cyclicExecuteIsr);

    ir_initIRTX();

    int stt = 0;
    int ir_rx_index = 0;
    int ir_rx_val[6] = {0, 0, 0, 0, 0, 0};

    while(1U){
        switch(stt){
            case 0: //STATE 0
                adc_initConvertion(ir_rx_index);
                stt = 1;
                break;
            case 1: //STATE 1
                if(&adc_isAdcDone){
                    ir_rx_val[ir_rx_index] = &adc_getConvertionValue;
                    ir_rx_index++;
                }
                //Check and set Led
                if(ir_rx_val[ir_rx_index] > 0){
                    led_setLed(ir_rx_index);
                }
                else
                    led_clearLed(ir_rx_index);
                //Change state
                if(ir_rx_index >= 6)
                    stt = 2;
                else
                    stt = 0;
                break;
            case 2: //STATE 2
                stt = 0;
        }

        while(!uiFlagNextPeriod);
        uiFlagNextPeriod = 0;

    }//end while(1U)

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
