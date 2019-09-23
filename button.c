/******************************************************************************
 *
 * Module: Vehicle State Estimator
 *
 * File Name: Button.c
 *
 * Description: source file for BCM Driver
 *
 * Created on: Sep 22, 2019
 *
 * Author: Ahmed Eldakhly & Hesham Hafez
 *
 *******************************************************************************/

/*******************************************************************************
 *                          Included Libraries                                *
 *******************************************************************************/
#include "button.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
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
void Button_Init(void)
{
    /* Initialize port f */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    /*Unlock GPIO Pin 0*/
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
    /*Pin 0 and Pin 4 are inputs and pull up*/
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}


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
void Button_press(void)
{
    /*Tiva one code*/
#if TIVA_TYPE==TIVA1
    /*For tiva 1*/
    if(TimeState == START_TIME)
    {
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0)
        {
            speed+=10;
            UARTprintf("Speed: %d\n",speed);
            UARTCharPut(UART3_BASE, time);
            UARTCharPut(UART3_BASE, speed);
        }
        while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0);
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) ==0)
        {
            if(speed > 0)
            {
                speed-=10;
                UARTprintf("Speed: %d\n",speed);
                UARTCharPut(UART3_BASE, time);
                UARTCharPut(UART3_BASE, speed);
            }

        }
        while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0);
    }
    /*Tiva two code*/
#elif TIVA_TYPE==TIVA2
    /* flag */

    /*for tiva 2*/
    if(TimeState == END_TIME)
    {
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0)
        {
            UARTCharPut(UART3_BASE, START_TIME);
            TimeState = START_TIME;
            UARTprintf("Measure start\n");
            while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0);
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(TimeState == START_TIME)
    {
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) ==0)
        {
            UARTCharPut(UART3_BASE, END_TIME);
            RecentTime = UARTCharGet (UART3_BASE);
            RecentSpeed = UARTCharGet (UART3_BASE );
            Distance += ((RecentTime-OldTime)*OldSpeed);
            OldSpeed = RecentSpeed;
            OldTime = RecentTime;
            UARTprintf("All Distance: %d\n", Distance);
            while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0);
        }
        else
        {
            /*Do Nothing*/
        }
    }
#endif
}
