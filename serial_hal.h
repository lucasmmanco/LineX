/* ***************************************************************** */
/* File name:        serial_hal.h    	                             */
/* File description:                                                 */
/*                                                                   */
/*                                                                   */
/* Author name:      Henrique Amitay & Lucas Manço                   */
/* Creation date:    28apr2016                                       */
/* Revision date:    28apr2016                                       */
/* ***************************************************************** */

#include "debugUart.h"
#include "print_scan.h"

/* ************************************************ */
/* Method name:        serial_setConfig 	        */
/* Method description: Set the configuration of     */
/*					    serial port                 */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void serial_setConfig(void);

/* ************************************************ */
/* Method name:        serial_receiveBuffer	        */
/* Method description: Verify if there is a data in */
/*					   serial port. If there is, it */
/*					   returns in a pointer of char */
/*                     the data.                    */
/* Input params:       char *                       */
/* Output params:      n/a                          */
/* ************************************************ */
void serial_receiveBuffer(char * uiReceiveBuffer);

/* ************************************************ */
/* Method name:        serial_sendBuffer         */
/* Method description: Send a message through serial*/
/*					   port.                        */
/*					                                */
/* Input params:       char[]                       */
/* Output params:      n/a                          */
/* ************************************************ */
void serial_sendBuffer(char buffer[]);
