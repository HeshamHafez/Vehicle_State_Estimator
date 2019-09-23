/******************************************************************************
 *
 * Module: Vehicle State Estimator
 *
 * File Name: timer.h
 *
 * Description: header file for timer driver
 *
 * Created on: Sep 22, 2019
 *
 * Author: Ahmed Eldakhly & Hesham Hafez
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

/*******************************************************************************
 *                          Included Libraries                                 *
 *******************************************************************************/
#include "common_header.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
extern volatile uint32_t time;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:   Timer0_Init
 *
 * Description:     Initialize the Timer Driver
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
extern void Timer0_Init(void);

/*******************************************************************************
 * Function Name:   Timer0Handler
 *
 * Description:     handle the interrupt service routine in the Timer Driver
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
extern void Timer0Handler(void);


#endif /* TIMER_H_ */
