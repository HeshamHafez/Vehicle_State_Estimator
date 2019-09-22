
/*tiva one*/

#include "timer.h"
#include "button.h"
#include "UART.h"
#if TIVA_TYPE == TIVA1
int main(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    vUART_Init();
    Button_Init();
    time = UARTCharGet (UART3_BASE );
    speed = UARTCharGet (UART3_BASE );
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

