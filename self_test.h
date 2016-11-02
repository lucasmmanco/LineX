/* **************************************************************** */
/* File name:        self_test.h                                    */
/* File description: Header file containing the functions/methods   */
/*                   interfaces for self test of all LineX          */
/*                   peripherics                                    */
/* Author name:      lmanco                                         */
/* Creation date:    02out2016                                      */
/* Revision date:    02nov2016                                      */
/* **************************************************************** */

#ifndef SOURCES_SELF_TEST_H_
#define SOURCES_SELF_TEST_H_

#include "self_test.h"

/* **************************************************************************** */
/* Method name:        selfTest_IR                                              */
/* Method description: Test the functionalaty of RX IR observing the variantion */
/*                    of the signal of each RX IR when the TX IR is up and down */
/* Input params:      n/a                                                       */
/* Output params:     1 if it's everything OK or the number of the error        */
/* **************************************************************************** */
int selfTest_IR(void){}

/* **************************************************************************** */
/* Method name:        selfTest_motor                                           */
/* Method description: Test the functionalaty of motor observing the variantion */
/*                    of the speed when PWM Duty Cicle is 100% and 0%           */
/* Input params:      n/a                                                       */
/* Output params:     1 if it's everything OK or the number of the error        */
/* **************************************************************************** */
int selfTest_motor(void){}

/* **************************************************************************** */
/* Method name:        selfTest_IR                                              */
/* Method description: Test the functionalaty of encoder checking the variantion*/
/*                    of the signal when PWM Duty Cicle is 100% and 0%          */
/* Input params:      n/a                                                       */
/* Output params:     1 if it's everything OK or the number of the error        */
/* **************************************************************************** */
int selfTest_encoder(void){}


#endif /* SOURCES_SELF_TEST_H_ */