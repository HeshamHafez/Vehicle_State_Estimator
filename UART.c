
#include "UART.h"

#if TIVA_TYPE == TIVA1
volatile uint32_t speed=0;

#elif TIVA_TYPE == TIVA2
volatile uint32_t Distance=0;
volatile uint32_t OldSpeed=0;
volatile uint32_t RecentSpeed=0;
volatile uint32_t OldTime=0;
volatile uint32_t RecentTime=0;
#endif

void vUART_Init(void)
{
    /*
     *
     */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioConfig(0, 115200, SysCtlClockGet());
    /*
     *
     */
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
void vUART_UART3Handler(void)
{
    static uint8_t Startcheck = START_TIME;
    if((Startcheck == START_TIME) && (UARTCharGet (UART3_BASE ) == START_TIME))
    {
        UARTCharPut(UART3_BASE, time);
        UARTCharPut(UART3_BASE, speed);
        Startcheck = END_TIME;
    }
    else if((Startcheck == END_TIME) && (UARTCharGet (UART3_BASE ) == END_TIME))
    {
        UARTCharPut(UART3_BASE, time);
        UARTCharPut(UART3_BASE, speed);
        Startcheck = START_TIME;
    }
}
#elif TIVA_TYPE == TIVA2
/*for tiva 2*/
void vUART_UART3Handler(void)
{
RecentTime = UARTCharGet (UART3_BASE);
RecentSpeed = UARTCharGet (UART3_BASE );
Distance += ((RecentTime-OldTime)*OldSpeed);
OldSpeed = RecentSpeed;
OldTime = RecentTime;
}
#endif


