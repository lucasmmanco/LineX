/* ***************************************************************** */
/* File name:        serial_hal.c  	                                 */
/* File description:                                                 */
/*                                                                   */
/*                                                                   */
/* Author name:      Henrique Amitay & Lucas Manço                   */
/* Creation date:    28apr2016                                       */
/* Revision date:    28apr2016                                       */
/* ***************************************************************** */

#include "serial_hal.h"
#include "debugUart.h"
#include "print_scan.h"
#include "KL25Z/line_follower_mapping.h"
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"

/* ************************************************ */
/* Method name:        serial_setConfig 	        */
/* Method description: Set the configuration of     */
/*					    serial port                 */
/*					                                */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void serial_setConfig(void){
    debugUart_init();
}

/* ************************************************ */
/* Method name:        serial_receiveBuffer	        */
/* Method description: Verify if there is a data in */
/*					   serial port. If there is, it */
/*					   returns in a pointer of char */
/*                     the data.                    */
/* Input params:       char *                       */
/* Output params:      n/a                          */
/* ************************************************ */
void serial_receiveBuffer(char uiReceiveBuffer[]){

	char cChar;
	int i=0;

	while(cChar != 0x0a){


		if(UART0_BRD_S1_RDRF(UART0))
			{
				cChar = GETCHAR();
				uiReceiveBuffer[i] = cChar;
				i++;
			}
	}
}

/* ************************************************ */
/* Method name:        serial_sendBuffer         */
/* Method description: Send a message through serial*/
/*					   port.                        */
/*					                                */
/* Input params:       char[]                       */
/* Output params:      n/a                          */
/* ************************************************ */
void serial_sendBuffer(char buffer[]){
			int i=0;
			while(buffer[i] != NULL){
                PUTCHAR(buffer[i]);
                i++;
			}
}
