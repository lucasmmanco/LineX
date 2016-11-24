/* ***************************************************************** */
/* File name:        pid.c                                           */
/* File description: PID controller                                  */
/* Author name:      Lucas Manço                                     */
/* Creation date:    01jul2016                                       */
/* Revision date:    01jul2016                                       */
/* ***************************************************************** */
    
#include "pid.h"


/* *************************************************** */
/* Method name:        pid_motorInitializate           */
/* Method description: Returns an initialized pid_motor*/
/* Input params:       PID_MOTOR*                      */
/*                     vel[]: min and max rotation     */
/*                     pwm[]: min and max pwm          */
/* Output params:      n/a                             */
/* *************************************************** */
void pid_motorInitializate(PID_MOTOR *pid_data, float vel[], int pwm[]){
    pid_data->kp = 1.0;
    pid_data->ki = 1.0;
    pid_data->kd = 1.0;

    pid_data->sensor_previous= 0.0;
    pid_data->error = 0.0;
    pid_data->ref = 0.0;
    
    float pwmMin = (float)pwm[0];
    float pwmMax = (float)pwm[1];
    float velMin = vel[0];
    float velMax = vel[1];

    
    pid_data->pwmMin = pwm[0];
    pid_data->pwmMax = pwm[1];
    
    pid_data->a = (pwmMax - pwmMin)/(velMax - velMin);
    pid_data->b = pwmMin - pid_data->a * velMin;

}

/* ************************************************ */
/* Method name:        pid_Update                   */
/* Method description: Returns the actuator value   */
/* Input params:       PID_DATA* = parameters of PID*/
/*                     sensoVal = value of sensor   */
/* Output params:      double                       */
/* ************************************************ */
int pid_motorUpdate(PID_MOTOR *pid_data, float sensorVal){
    float fP_term, fI_term, fD_term;
    float error, dif;
    float fNewVel = 0;
    int iNewPwm = 0;

    //Proportional Gain
    error = pid_data->ref - sensorVal;
    fP_term = pid_data->kp * error;
    
    //Integrative Gain
    pid_data->error += error;    
    fI_term = pid_data->ki * pid_data->error;

    //Derivative Gain
    dif = pid_data->sensor_previous - sensorVal;
    pid_data->sensor_previous = sensorVal;
    fD_term = pid_data->kd * dif;
    
    fNewVel = (fP_term + fI_term + fD_term);
    
    iNewPwm = (int)(pid_data->a * fNewVel + pid_data->b);
        
    if(iNewPwm > pid_data->pwmMax)
        iNewPwm = pid_data->pwmMax;
    if(iNewPwm < pid_data->pwmMin)
        iNewPwm = pid_data->pwmMin;
    
    return iNewPwm;
}

/* *************************************************** */
/* Method name:        pid_Initializate                */
/* Method description: Returns an initialized pid_data */
/* Input params:       PID_DATA*                       */
/*                     vel[]: min and max rotation     */
/* Output params:      n/a                             */
/* *************************************************** */
void pid_splineInitializate(PID_SPLINE *pid_data, float vel[]){   
    float vel_window = (vel[1] - vel[0])/2;
    
    pid_data->kp = 0.0; //DEFAULT
    pid_data->ki = 0.0; //DEFAULT
    pid_data->kd = 0.0; //DEFAULT
    pid_data->spline_previous= 0.0;
    pid_data->error = 0.0;
    pid_data->ref = 37.5;
    pid_data->velMin = vel[0];
    pid_data->velMax = vel[1];
    
    pid_data->a = -vel_window/37.5;
    pid_data->b = 0.0;

}

/* ************************************************ */
/* Method name:        pid_Update                   */
/* Method description: Returns the actuator value   */
/* Input params:       PID_DATA* = parameters of PID*/
/*                     splineVal = value of sensor  */
/*                     *velR = rigth motor speed    */
/*                     *velL = left motor speed     */
/* Output params:      double                       */
/* ************************************************ */
void pid_splineUpdate(PID_SPLINE *pid_data, float splineVal, float *velR, float *velL, float velMean){
    float fP_term, fI_term, fD_term;
    float error, dif;
    float fNewSpline = 0.0;
    float fVelIncrement= 0.0;
    float fNewVelR, fNewVelL;
    float window = 12.5;
    
    //if(splineVal > (pid_data->ref - window) || splineVal < (pid_data->ref + window)){
    //    pid_data->error = 0;
    //}
    //Proportional Gain
    error =  splineVal - pid_data->ref;
    fP_term = pid_data->kp * error;
    
    //Integrative Gain
    pid_data->error += error;    
    fI_term = pid_data->ki * pid_data->error;
    
    //Derivative Gain
    dif = pid_data->spline_previous - splineVal;
    pid_data->spline_previous = splineVal;
    fD_term = pid_data->kd * dif;
    
    fNewSpline = (fP_term + fI_term + fD_term);
    
    fNewSpline = (splineVal - pid_data->ref) * pid_data->kp;
    
    fVelIncrement = pid_data->a * fNewSpline + pid_data->b;
    
    if(fVelIncrement > (velMean - pid_data->velMin) || fVelIncrement > (pid_data->velMax - velMean)){
        fVelIncrement = (velMean - pid_data->velMin);
    }
    
    fNewVelR = velMean - fVelIncrement;
    fNewVelL = velMean + fVelIncrement;

    float vr = *velR;
    float vl = *velL;
     
    if(fNewVelR < pid_data->velMin)
        fNewVelR = pid_data->velMin;
    else if(fNewVelR > pid_data->velMax)
        fNewVelR = pid_data->velMax;

    if(fNewVelL < pid_data->velMin)
        fNewVelL = pid_data->velMin;
    else if(fNewVelL > pid_data->velMax)
        fNewVelL = pid_data->velMax;


    *velR = fNewVelR;
    *velL = fNewVelL;
        
}
