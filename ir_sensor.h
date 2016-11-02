/* ***************************************************************** */
/* File name:        ir_sensor.c                                     */
/* File description: Header file containing the functions/methods    */
/*                   prototypes of ir_sensor.c                       */
/* Author name:      lmanco                                          */
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