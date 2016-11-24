/* ***************************************************************** */
/* File name:        ir_sensor.c                                    */
/* File description: This file has a couple of useful functions to   */
/*                   control and read IR sensors of the Line Follower*/
/* Author name:      lmanco and hlucredi                                       */
/* Creation date:    07oct2016                                       */
/* Revision date:    07oct2016                                       */
/* ***************************************************************** */

#include "ir_sensor.h"
#include "util.h"
#include "adc.h"
#include "motor_hal.h"
#include <math.h>

#include "KL25Z/line_follower_mapping.h"

/* **************************************************************** */
/* Method name:        ir_initIRTX                                  */
/* Method description: Configure the TX IR transistor port as GPIO  */
/* Input params:      n/a                                           */
/* Output params:     n/a                                           */
/* **************************************************************** */
void ir_initIRTX(void){
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pin as gpio */
    PORTE_PCR5 = PORT_PCR_MUX(IR_TX_PIN);
    
    GPIOE_PDDR |= GPIO_PDDR_PDD(IR_TX_DIR_OUTPUT);
}

/* **************************************************************** */
/* Method name:        ir_setIRTX                                   */
/* Method description: Set the TX Transinstor of all TXs IR to turn */
/*                     them on                                      */
/* Input params:      n/a                                           */
/* Output params:     n/a                                           */
/* **************************************************************** */
void ir_setIRTX(void){
    GPIOE_PSOR = GPIO_PSOR_PTSO( (0x01U << IR_TX_PIN));
}

/* **************************************************************** */
/* Method name:        ir_clearIRTX                                 */
/* Method description: Turn off all TXs IR                          */
/* Input params:      n/a                                           */
/* Output params:     n/a                                           */
/* **************************************************************** */
void ir_clearIRTX(void){
    GPIOE_PCOR = GPIO_PCOR_PTCO( (0x01U << IR_TX_PIN));
}

/****************************************/
/* 	Single Sensor Read Function 	    */
/*INPUT: No 0 to 5 of selected sensor	*/
/*OUTPUT: 16 bit Value of sensor	    */
/****************************************/
int ir_sensor_readIR(int sensorIndex){

	/* Selects single IR pair */
	adc_initConvertion(sensorIndex);
	/* Checks if job is done */
    while(!adc_isAdcDone()){}
	/* Return read value */
	int value = adc_getConvertionValue();
    while(adc_isAdcDone()){}
    return value;
}

/****************************************/
/* 	Array of Sensors	 	            */
/*INPUT: Int Vector of 6 positions	    */
/*OUTPUT: Vector with values readen	    */
/****************************************/
void ir_sensor_buildArray(int* IR[]){

	/* Swipes trought 6 sensors */
	for(int i=0; i<6; i++)
		IR[i] = ir_sensor_readIR(i);
	
}

/****************************************/
/* 	First Time Calibration IR	        */
/*INPUT: Int Vector of 12 positions	    */
/*OUTPUT: Vector with values readen	    */
/* Odd are maximum and Even minimun	    */
/****************************************/
void ir_sensor_initCalibrationIR(int* IR_VectorValue[]){
    
    int i;
	int IR_Readen[6];

	ir_sensor_buildArray(IR_Readen);

	/* First time reading */
	for(i=0; i<6; i++){
		IR_VectorValue[2*i+1] = IR_Readen[i];	// odd values are maximum
		IR_VectorValue[2*i] = IR_Readen[i];	// even values are minimun
	}
}

/****************************************/
/* 	Calibration IR Routine		        */
/*INPUT: Int Vector of 12 positions	    */
/*OUTPUT: Vector with values readen	    */
/* Replaces Maximum and Minimuns Values	*/
/* Odd are maximum and Even minimun	    */
/****************************************/
void ir_sensor_calibrateArray(int* IR_VectorValue){
	
    int i;
    
	int IR_Readen[6];
	
	/* Read sensor values */
	ir_sensor_buildArray(IR_Readen);

	/* Calibration check */
	for(i=0; i<6; i++){
		/* Check if new value is higher than older */
		if(IR_Readen[i] > IR_VectorValue[2*i+1])
			IR_VectorValue[2*i+1] = IR_Readen[i];	// odd values are maximum
		
		/* Check if new value is lower than older */
		else if(IR_Readen[i] < IR_VectorValue[2*i])
            IR_VectorValue[2*i] = IR_Readen[i];	// even values are minimun 
	}
}

/****************************************/
/* ir_sensor_runCalibration             */
/* Run all functions to do the          */
/* to get all max and min off each      */
/* ir_sensor                            */
/* INPUT: *IR_VectorValue               */
/* OUTPUT: n/a                          */
/****************************************/
void ir_sensor_runCalibration(int* IR_VectorValue){
    
    ir_sensor_initCalibrationIR(IR_VectorValue);
    
    int iTimer = 0;
    
    motor_set('R', 1, 60);
    motor_set('L', 0, 60);
    
    while(iTimer < 50){
        ir_sensor_calibrateArray(IR_VectorValue);
        util_genDelay10ms();
        iTimer++;
    }
    
    iTimer = 0;
    motor_set('R', 0, 60);
    motor_set('L', 1, 60);
    
    while(iTimer < 100){
        ir_sensor_calibrateArray(IR_VectorValue);
        util_genDelay10ms();
        iTimer++;
    }
    
    iTimer = 0;
    motor_set('R', 1, 60);
    motor_set('L', 0, 60);
    
    while(iTimer < 49){
        ir_sensor_calibrateArray(IR_VectorValue);
        util_genDelay10ms();
        iTimer++;
    }
    
    motor_stop();
    
}

/****************************************/
/* 	Normalized Sensor Reading	        */
/* Info: Builds an array with normalized*/
/* sensor reading			            */
/*INPUT: IR_V - Vector with maximun and	*/
/*	minimun values from calibration	    */
/*	 IR_normalized - vector for	        */
/*	normalized reading		            */
/*OUTPUT: IR_normalized - new values	*/
/* Odd are maximum and Even minimun	    */
/****************************************/
void ir_sensor_readNormal(int* IR_V, int* IR_normalized){

	/* Read sensor values */
	ir_sensor_buildArray(IR_normalized);

	for(int i=0; i<6; i++){
		
		/* Normalize readen values */
		IR_normalized[i] = 100*(((float)IR_normalized[i] - (float)IR_V[2*i])/((float)IR_V[2*i+1] - (float)IR_V[2*i]));
		
	}
}

//////////////////////////// Cálculo de Spline

/****************************************/
/* Function: ir_sensor_doAbarrelRom	    */
/* INPUTS: in_Array (int*) - 4 position	*/
/* out_Spline (int*) - 4 position	    */
/* Receives in_Array as 4 points and	*/
/* calculates Catmull Rom to out_Spline	*/
/* P0, P1, P2, P3 - C, t, t2, t3	    */
/****************************************/
void ir_sensor_doAbarrelRom(int* in_Array, float out_Spline[]){
	
	/* 2*P0/2	*/
	out_Spline[0] = (float)in_Array[1];

	/*	(-P0 +P1)t/2t	*/
	out_Spline[1] = ((float)in_Array[2] - (float)in_Array[0])/2;

	/*	2*P0 -5*P1 +4*P2 -P3 t^2	*/
	out_Spline[2] = (2*(float)in_Array[0] - 5*(float)in_Array[1] + 4*(float)in_Array[2] - in_Array[3])/2;

	/*	-P0 +3*P1 -3*P2 +P3	*/
	out_Spline[3] = (- (float)in_Array[0] + 3*(float)in_Array[1] - 3*(float)in_Array[2] + (float)in_Array[3])/2;

}

/****************************************/
/* Function: ir_sensor_intensityCheck	*/
/* INPUTS: in_Array (int*) - 6 position	*/
/* out_Deduc (int*) - 4 position        */
/* Receives in_Array as 6 points and	*/
/* returns lowest 4 values out_Deduc	*/
/* P0, P1, P2, P3, P4, P5		        */
/****************************************/
int ir_sensor_intensityCheck(int* in_Array, int* out_Deduc){
	
	int iHighpoint = 0;
    int i=0;
    int iMax = 0;

	while(i<6){
		/* Vetor de maiores valores	*/
		if(iHighpoint < in_Array[i]){
			iHighpoint = in_Array[i];	// Atualiza maior valor
			iMax = i;	// Salva o sensor referência
		}
		i++;	
	}
    
    if(iMax == 0 || iMax == 1){	
		/* Margem Esquerda */
		out_Deduc[0] = in_Array[0];
		out_Deduc[1] = in_Array[0];
		out_Deduc[2] = in_Array[1];
		out_Deduc[3] = in_Array[2];
        
        if(iMax == 1 & in_Array[0] > in_Array[2])
            iMax--;    //Correção para posterior Tratamento
	}
	else if(iMax == 5 || iMax == 4){
		/* Margem Direita */
		out_Deduc[0] = in_Array[3];
		out_Deduc[1] = in_Array[4];
		out_Deduc[2] = in_Array[5];
		out_Deduc[3] = in_Array[5];
	}
	else{
	/*	Sinal posterior maior que anterior	*/
		if(in_Array[iMax-1] < in_Array[iMax+1]){
		
			out_Deduc[0] = in_Array[iMax-1];
			out_Deduc[1] = in_Array[iMax];
			out_Deduc[2] = in_Array[iMax+1];
			out_Deduc[3] = in_Array[iMax+2];
		}
	/*	Sinal posterior menor que anterior	*/
		if(in_Array[iMax-1] >= in_Array[iMax+1]){
			out_Deduc[0] = in_Array[iMax-2];
			out_Deduc[1] = in_Array[iMax-1];
			out_Deduc[2] = in_Array[iMax];
			out_Deduc[3] = in_Array[iMax+1];
            iMax--;    // Correção para posterior tratamento
		}
	}
    
	return iMax;
}

/* Returns normalized location between 0 - 100 %	*/
int ir_sensor_returnLow(int *IR_Reference){
	
	int Vector[6], Gaussian[4], Position;
    
    float Equation[4];

	ir_sensor_readNormal(IR_Reference, &Vector);

	Position = ir_sensor_intensityCheck(Vector, Gaussian);

	ir_sensor_doAbarrelRom(Gaussian, Equation);

	float a, b, c;
	float Result1, Result2;

	a = Equation[3]*3;
	b = Equation[2]*2;
	c = Equation[1];

	Result1 = (-b + sqrt((b*b)-4*a*c))/(2*a);

	Result2 = (-b - sqrt((b*b)-4*a*c))/(2*a);
	
	if(Result1 > 0 && Result1 < 1){
		Result1 = Result1;
	}
	else if(Result2 > 0 && Result2 < 1){
		Result1 = Result2;
	}
    else if(Result2 > Result1){ 
        Result1 = Result2;
    }
    //if(Result1 > 1 )
    //    Result1 = Result1 - 1.0;

    //CHecar essas condicoes para Position=0 e Position=5!!!
    if(Result1 > 1 && (Position==5 || Position==0)){
        Result1 = Result1 - 1.0;
    }
    
	Result1 = (15*Position + 15*Result1);//*100/75;
	
	return Result1;

}

int ir_sensor_returnPosiTest(int ir_valNormal[]){
    
    int Gaussian[4];// = {14, 57, 45, 45};

	int Position;
    
    float Equation[4];
    
    Position = ir_sensor_intensityCheck(ir_valNormal, Gaussian);

    //Position = 1;
    
	ir_sensor_doAbarrelRom(Gaussian, Equation);

	float a, b, c;
	float Result1, Result2;

	a = Equation[3]*3;
	b = Equation[2]*2;
	c = Equation[1];

	Result1 = (-b + sqrt((b*b)-4*a*c))/(2*a);

	Result2 = (-b - sqrt((b*b)-4*a*c))/(2*a);
	
	if(Result1 > 0 && Result1 < 1){
		
		Result1 = Result1;
	}
	else if(Result2 > 0 && Result2 < 1){

		Result1 = Result2;
	}
    else
        Result1 = 0;

	Result1 = (15*Position + 15*Result1)*100/75;
	
	return Result1;
     
}
