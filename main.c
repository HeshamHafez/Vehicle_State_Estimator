/******************************************************************************
 *
 * Module: Vehicle State Estimator main Application
 *
 * File Name: main.c
 *
 * Description: main Application
 *
 * Created on: Sep 22, 2019
 *
 * Author: Ahmed Eldakhly & Hesham Hafez
 *
 *******************************************************************************/
/*******************************************************************************
 *                          Included Libraries                                 *
 *******************************************************************************/
#include "timer.h"
#include "button.h"
#include "UART.h"


/*******************************************************************************
 *                             Main Function                                   *
 *******************************************************************************/
/*tiva one*/
#if TIVA_TYPE == TIVA1
int main(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
   volatile  uint8_t x=0;
    vUART_Init();
    Button_Init();
   // uint16_t j=1;
    for( x=0; x<4 ; x++)
    {
        time = ( (time *10) +   (UARTCharGet (UART0_BASE )-48));
       // j=j*10;
    }

    speed = UARTCharGet (UART0_BASE );
    Timer0_Init();

    while(1)
    {
        Button_press();
    }
}
/*Tiva 2*/
#elif TIVA_TYPE == TIVA2

int main(void)
{
    vUART_Init();
    Button_Init();
    UARTCharPut(UART3_BASE, START_TIME);
    OldTime = UARTCharGet (UART3_BASE );
    OldSpeed = UARTCharGet (UART3_BASE );
    while(1)
    {
        Button_press();
    }
}
#endif

