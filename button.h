/******************************************************************************
 *
 * Module: Vehicle State Estimator
 *
 * File Name: Button.h
 *
 * Description: header file for button
 *
 * Created on: Sep 22, 2019
 *
 * Author: Ahmed Eldakhly & Hesham Hafez
 *
 *******************************************************************************/

#ifndef BUTTON_H_
#define BUTTON_H_

 /*******************************************************************************
  *                          Included Libraries                                 *
  *******************************************************************************/
#include "common_header.h"
#include "UART.h"


 /*******************************************************************************
  *                      Functions Prototypes                                   *
  *******************************************************************************/

 /*******************************************************************************
  * Function Name:   Button_Init
  *
  * Description:     Initialize the Button
  *
  * Inputs:          NULL
  *
  * Outputs:         NULL
  *
  * Return:          NULL
  *******************************************************************************/
extern void Button_Init(void);

/*******************************************************************************
 * Function Name:   Button_press
 *
 * Description:     function to do tasks after press the Button
 *
 * Inputs:          NULL
 *
 * Outputs:         NULL
 *
 * Return:          NULL
 *******************************************************************************/
extern void Button_press(void);



#endif /* BUTTON_H_ */
