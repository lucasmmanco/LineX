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
/*					   Controller a motor           */
/* ************************************************ */
typedef struct PID_MOTOR{
	float kp, kd, ki;
	float sensor_previous;
	float error;
	float ref;
    float a, b; //line equation
	int pwmMin, pwmMax;//pwm limits
} PID_MOTOR;

/* ************************************************ */
/* Struct name:        PID_SPLINE                   */
/* Struct description: Representation of a PID      */
/*					   Controller for the Spline     */
/* ************************************************ */
typedef struct PID_SPLINE{
	float kp, kd, ki;
	float spline_previous;
	float error;
	float ref;
    float a, b; //line equation
	float velMin, velMax;//pwm limits
} PID_SPLINE;

void pid_motorInitializate(PID_MOTOR *pid_data, float vel[], int pwm[]);

int pid_motorUpdate(PID_MOTOR *pid_data, float sensorVal);

void pid_splineInitializate(PID_SPLINE *pid_data, float vel[]);

void pid_splineUpdate(PID_SPLINE *pid_data, float splineVal, int *velR, int *velL, int velMean);


#endif /* SOURCES_PID_H_ */
