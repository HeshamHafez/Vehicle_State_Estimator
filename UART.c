/******************************************************************************
 *
 * Module: Vehicle State Estimator
 *
 * File Name: uart.c
 *
 * Description: source file for UART driver
 *
 * Created on: Sep 22, 2019
 *
 * Author: Ahmed Eldakhly & Hesham Hafez
 *
 *******************************************************************************/
/*******************************************************************************
 *                          Included Libraries                                 *
 *******************************************************************************/
#include "UART.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
volatile uint8_t TimeState = END_TIME;

/*tiva 1 code*/
#if TIVA_TYPE == TIVA1
/*******************************************************************************
 *                      Global Variables for Tiva 1                            *
 *******************************************************************************/
volatile uint32_t speed=0;

/*tiva 2 code*/
#elif TIVA_TYPE == TIVA2
/*******************************************************************************
 *                      Global Variables for Tiva 1                            *
 *******************************************************************************/
volatile uint32_t Distance=0;
volatile uint32_t OldSpeed=0;
volatile uint32_t RecentSpeed=0;
volatile uint32_t OldTime=0;
volatile uint32_t RecentTime=0;
#endif

/*******************************************************************************
 *                      Functions Definitions                                  *
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
void vUART_Init(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioConfig(0, 115200, SysCtlClockGet());

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC));
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    GPIOPinConfigure(GPIO_PC6_U3RX);
    GPIOPinConfigure(GPIO_PC7_U3TX);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART3));
    UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 9600,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTFIFOLevelSet(UART3_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
    UARTIntRegister(UART3_BASE, vUART_UART3Handler);
    UARTIntEnable(UART3_BASE, UART_INT_RX | UART_INT_RT);
}

/*For tiva 1*/
#if TIVA_TYPE == TIVA1
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
void vUART_UART3Handler(void)
{
    static uint8_t Startcheck = START_TIME;
    if((Startcheck == START_TIME) && (UARTCharGet (UART3_BASE ) == START_TIME))
    {
        UARTCharPut(UART3_BASE, time);
        UARTCharPut(UART3_BASE, speed);
        Startcheck = END_TIME;
        TimeState = START_TIME;

    }
    else if((Startcheck == END_TIME) && (UARTCharGet (UART3_BASE ) == END_TIME))
    {
        UARTCharPut(UART3_BASE, time);
        UARTCharPut(UART3_BASE, speed);
        Startcheck = START_TIME;
        TimeState = END_TIME;
    }
}

/*for tiva 2*/
#elif TIVA_TYPE == TIVA2
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
void vUART_UART3Handler(void)
{
    if(TimeState == END_TIME)
    {
        OldTime = UARTCharGet (UART3_BASE );
        OldSpeed = UARTCharGet (UART3_BASE );
        UARTprintf("Start Time to Measure: %d\n", OldTime);
        UARTprintf("Start Speed to Measure: %d\n", OldSpeed);
    }
    else if(TimeState == START_TIME)
    {
        RecentTime = UARTCharGet (UART3_BASE);
        RecentSpeed = UARTCharGet (UART3_BASE );
        Distance += ((RecentTime-OldTime)*OldSpeed);
        OldSpeed = RecentSpeed;
        OldTime = RecentTime;
        UARTprintf("Speed was changed to: %d\n", RecentSpeed);
        UARTprintf("Distance till now: %d\n", Distance);
    }
}
#endif


