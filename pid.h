/* ***************************************************************** */
/* File name:        pid.h                                           */
/* File description: PID controller                                  */
/* Author name:      Lucas Manço                                     */
/* Creation date:    01jul2016                                       */
/* Revision date:    01jul2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_PID_H_
#define SOURCES_PID_H_

/* ************************************************ */
/* Struct name:        PID_DATA                     */
/* Struct description: Representation of a PID      */
/*					   Controller                   */
/* ************************************************ */
typedef struct PID_DATA{
	double kp, kd, ki;
	int sensor_previous;
	double error;
	int ref;
} PID_DATA;

void pid_initializate(PID_DATA *pid_data);

double pid_update(PID_DATA *pid_data, double sensorVal, int *pidTerms[]);

#endif /* SOURCES_PID_H_ */
