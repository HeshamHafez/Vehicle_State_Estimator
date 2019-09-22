/*
 * button.c
 *
 *  Created on: Sep 21, 2019
 *      Author: hesha
 */

#include "button.h"




void Button_Init(void)
{
    /*
     * initialize port f
     */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}


void Button_press(void)
{
#if TIVA_TYPE==TIVA1
    /*For tiva 1*/
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0)
    {
        speed++;
        UARTCharPut(UART3_BASE, time);
        UARTCharPut(UART3_BASE, speed);
    }
    while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0);
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) ==0)
    {
        if(speed > 0)
        {
            speed--;
            UARTCharPut(UART3_BASE, time);
            UARTCharPut(UART3_BASE, speed);
        }

    }
    while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0);
#elif TIVA_TYPE==TIVA2
    /* flag */

    /*for tiva 2*/
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0)
    {
        UARTCharPut(UART3_BASE, START_TIME);

    }
    while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0);
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) ==0)
    {
        UARTCharPut(UART3_BASE, END_TIME);
        RecentTime = UARTCharGet (UART3_BASE);
        RecentSpeed = UARTCharGet (UART3_BASE );
        Distance += ((RecentTime-OldTime)*OldSpeed);
        OldSpeed = RecentSpeed;
        OldTime = RecentTime;
        UARTprintf("%d\n", Distance);

    }
    while(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0);
#endif
}
