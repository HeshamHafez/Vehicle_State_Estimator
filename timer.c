/*
 * timer.c
 *
 *  Created on: Sep 21, 2019
 *      Author: hesha
 */

#include "timer.h"

volatile uint32_t time = 0;

void Timer0_Init(void)
{
    // Enable the Timer0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    // Wait for the Timer0 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));

    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC_UP);

    TimerIntRegister(TIMER0_BASE, TIMER_A ,Timer0Handler);

    TimerLoadSet(TIMER0_BASE , TIMER_A , SysCtlClockGet());

    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    TimerEnable(TIMER0_BASE, TIMER_A);
}

void Timer0Handler(void)
{
    TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    time++;
    UARTprintf("%d\n", time);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0xFF);
}

