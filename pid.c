/* ***************************************************************** */
/* File name:        pid.c                                           */
/* File description: PID controller                                  */
/* Author name:      Lucas Manço                                     */
/* Creation date:    01jul2016                                       */
/* Revision date:    01jul2016                                       */
/* ***************************************************************** */
    
#include "pid.h"


/* *************************************************** */
/* Method name:        pid_Initializate                */
/* Method description: Returns an initialized pid_data */
/* Input params:       PID_DATA*                       */
/* Output params:      n/a                             */
/* *************************************************** */
void pid_initializate(PID_DATA *pid_data){
    pid_data->kp = 1;
    pid_data->ki = 1;
    pid_data->kd = 1;

    pid_data->sensor_previous= 0;
    pid_data->error = 0;
    pid_data->ref = 0;

}

/* ************************************************ */
/* Method name:        pid_Update                   */
/* Method description: Returns the actuator value   */
/* Input params:       PID_DATA* = parameters of PID*/
/*                     sensoVal = value of sensor   */
/*                     ref = reference value        */
/* Output params:      double                       */
/* ************************************************ */
double pid_update(PID_DATA *pid_data, double sensorVal, int *pidTerms[]){
    double dP_term, dI_term, dD_term;
    double error, dif;

    error = pid_data->ref - sensorVal;

    dP_term = pid_data->kp * error;
    pid_data->error += error;

    dI_term = pid_data->ki * pid_data->error;
    dif = pid_data->sensor_previous - sensorVal;

    pid_data->sensor_previous = sensorVal;

    dD_term = pid_data->kd * dif;

    pidTerms[0] = (int) dP_term;
    pidTerms[1] = (int) dI_term;
    pidTerms[2] = (int) dD_term;
    
    return (dP_term + dI_term + dD_term);

}
