/* ***************************************************************** */
/* File name:        ir_sensor.c                                     */
/* File description: Header file containing the functions/methods    */
/*                   prototypes of ir_sensor.c                       */
/* Author name:      lmanco and hlucredi                                      */
/* Creation date:    07oct2016                                       */
/* Revision date:    07oct2016                                       */
/* ***************************************************************** */

/* **************************************************************** */
/* Method name:        ir_initIRTX                                  */
/* Method description: Configure the TX IR transistor port as GPIO  */
/* Input params:      n/a                                           */
/* Output params:     n/a                                           */
/* **************************************************************** */
void ir_initIRTX(void);

/* **************************************************************** */
/* Method name:        ir_setIRTX                                   */
/* Method description: Set the TX Transinstor of all TXs IR to turn */
/*                     them on                                      */
/* Input params:      n/a                                           */
/* Output params:     n/a                                           */
/* **************************************************************** */
void ir_setIRTX(void);

/* **************************************************************** */
/* Method name:        ir_clearIRTX                                 */
/* Method description: Turn off all TXs IR                          */
/* Input params:      n/a                                           */
/* Output params:     n/a                                           */
/* **************************************************************** */
void ir_clearIRTX(void);

/****************************************/
/* 	Single Sensor Read Function 	    */
/*INPUT: No 0 to 5 of selected sensor	*/
/*OUTPUT: 16 bit Value of sensor	    */
/****************************************/
int ir_sensor_readIR(int sensorIndex);

/****************************************/
/* 	Single Sensor Read Function 	    */
/*INPUT: No 0 to 5 of selected sensor	*/
/*OUTPUT: 16 bit Value of sensor	    */
/****************************************/
void ir_sensor_buildArray(int* IR[]);

/****************************************/
/* 	Array of Sensors	 	            */
/*INPUT: Int Vector of 6 positions	    */
/*OUTPUT: Vector with values readen	    */
/****************************************/
void ir_sensor_initCalibrationIR(int* IR_VectorValue[]);

/****************************************/
/* 	First Time Calibration IR	        */
/*INPUT: Int Vector of 12 positions	    */
/*OUTPUT: Vector with values readen	    */
/* Odd are maximum and Even minimun	    */
/****************************************/
void ir_sensor_calibrateArray(int* IR_VectorValue);

/****************************************/
/* ir_sensor_runCalibration             */
/* Run all functions to do the          */
/* to get all max and min off each      */
/* ir_sensor                            */
/* INPUT: *IR_VectorValue               */
/* OUTPUT: n/a                          */
/****************************************/
void ir_sensor_runCalibration(int* IR_VectorValue);

/****************************************/
/* 	Calibration IR Routine		        */
/*INPUT: Int Vector of 12 positions	    */
/*OUTPUT: Vector with values readen	    */
/* Replaces Maximum and Minimuns Values	*/
/* Odd are maximum and Even minimun	    */
/****************************************/
void ir_sensor_runCalibration(int* IR_VectorValue);

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
void ir_sensor_readNormal(int* IR_V, int* IR_normalized);

/****************************************/
/* Function: ir_sensor_doAbarrelRom	    */
/* INPUTS: in_Array (int*) - 4 position	*/
/* out_Spline (int*) - 4 position	    */
/* Receives in_Array as 4 points and	*/
/* calculates Catmull Rom to out_Spline	*/
/* P0, P1, P2, P3 - C, t, t2, t3	    */
/****************************************/
void ir_sensor_doAbarrelRom(int* in_Array, float out_Spline[]);

/****************************************/
/* Function: ir_sensor_intensityCheck	*/
/* INPUTS: in_Array (int*) - 6 position	*/
/* out_Deduc (int*) - 4 position        */
/* Receives in_Array as 6 points and	*/
/* returns lowest 4 values out_Deduc	*/
/* P0, P1, P2, P3, P4, P5		        */
/****************************************/
int ir_sensor_intensityCheck(int* in_Array, int* out_Deduc);

/****************************************************/
/* Function: ir_sensor_returnLow   	                */
/* Returns normalized location between 0 - 100 %	*/
/****************************************************/
int ir_sensor_returnLow(int *IR_Reference);

int ir_sensor_returnPosiTest(int ir_valNormal[]);