/******************************************************************************
 *
 * Module: Vehicle State Estimator
 *
 * File Name: uart.h
 *
 * Description: header file for UART driver
 *
 * Created on: Sep 22, 2019
 *
 * Author: Ahmed Eldakhly & Hesham Hafez
 *
 *******************************************************************************/
#ifndef UART_H_
#define UART_H_

/*******************************************************************************
 *                          Included Libraries                                 *
 *******************************************************************************/
#include "common_header.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
extern volatile uint8_t TimeState;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define START_TIME 10
#define END_TIME 20

#define TIVA1 1
#define TIVA2 2
#define TIVA_TYPE TIVA1

/*tiva 1 code*/
#if TIVA_TYPE == TIVA1
/*******************************************************************************
 *                      Global Variables for Tiva 1                            *
 *******************************************************************************/
extern volatile uint32_t time;
extern volatile uint32_t speed;

/*tiva 2 code*/
#elif TIVA_TYPE == TIVA2
/*******************************************************************************
 *                      Global Variables for Tiva 1                            *
 *******************************************************************************/
extern volatile uint32_t Distance;
extern volatile uint32_t OldSpeed;
extern volatile uint32_t RecentSpeed;
extern volatile uint32_t OldTime;
extern volatile uint32_t RecentTime;
#endif


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:   vUART_Init
 *
 * Description:     Initialize the UART Driver "UART0 & UART3"
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
extern void vUART_Init(void);

/*******************************************************************************
 * Function Name:   vUART_UART3Handler
 *
 * Description:     handle the interrupt service routine in the UART Driver "UART3"
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
extern void vUART_UART3Handler(void);

#endif /* UART_H_ */
