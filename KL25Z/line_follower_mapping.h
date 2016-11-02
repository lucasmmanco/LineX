/* ***************************************************************** */
/* File name:        line_follower_mapping.h                         */
/* File description: Header file containing the peripherals mapping  */
/*                     of the peripheral board for the Line Follower */
/* Author name:      lmanco                                          */
/* Creation date:    02oct2016                                       */
/* Revision date:                                                    */
/* ***************************************************************** */

#ifndef SOURCES_LINE_FOLLOWER_MAPPING_H_
#define SOURCES_LINE_FOLLOWER_MAPPING_H_

/* system includes */
#include <MKL25Z4.h>

/****************** General uC definitions *******************/

/* Clock gate control */
#define  CGC_CLOCK_DISABLED         0x00U
#define  CGC_CLOCK_ENABLED          0x01U

/* GPIO input / output */
#define GPIO_INPUT                  0x00U
#define GPIO_OUTPUT                 0x01U

/***********END OF General uC definitions********************/

/*                 LED Definitions                    */
#define LS_PORT_BASE_PNT            PORTE                                   /* peripheral port base pointer */
#define LS_GPIO_BASE_PNT            PTE

#define LS1_PIN                     20U                                      /* led #1 pin */
#define LS1_DIR_OUTPUT              (GPIO_OUTPUT << LS1_PIN)
#define LS1_ALT                     0x01u

#define LS2_PIN                     21U                                      /* led #2 pin */
#define LS2_DIR_OUTPUT              (GPIO_OUTPUT << LS2_PIN)
#define LS2_ALT                     0x01u

#define LS3_PIN                     22U                                      /* led #3 pin */
#define LS3_DIR_OUTPUT              (GPIO_OUTPUT << LS3_PIN)
#define LS3_ALT                     0x01u

#define LS4_PIN                     23U                                      /* led #4 pin */
#define LS4_DIR_OUTPUT              (GPIO_OUTPUT << LS4_PIN)
#define LS4_ALT                     0x01u

#define LS5_PIN                     29U                                      /* led #5 pin */
#define LS5_DIR_OUTPUT              (GPIO_OUTPUT << LS5_PIN)
#define LS5_ALT                     0x01u

#define LS6_PIN                     30U                                      /* led #6 pin */
#define LS6_DIR_OUTPUT              (GPIO_OUTPUT << LS6_PIN)
#define LS6_ALT                     0x01u

/*                IR TX Definitions                         */
#define IR_TX_PORT_BASE_PNT         PORTE
#define IR_TX_GPIO_BASE_PNT         PTE

#define IR_TX_PIN                   5U
#define IR_TX_DIR_OUTPUT            (GPIO_OUTPUT << IR_TX_PIN)
#define IR_TX_ALT                   0x01u

#endif
