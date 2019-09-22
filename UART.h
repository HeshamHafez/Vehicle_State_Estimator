
#ifndef UART_H_
#define UART_H_

#include "common_header.h"

#define START_TIME 10
#define END_TIME 20

#define TIVA1 1
#define TIVA2 2
#define TIVA_TYPE TIVA2

#if TIVA_TYPE == TIVA1

extern volatile uint32_t time;
extern volatile uint32_t speed;

#elif TIVA_TYPE == TIVA2
extern volatile uint32_t Distance;
extern volatile uint32_t OldSpeed;
extern volatile uint32_t RecentSpeed;
extern volatile uint32_t OldTime;
extern volatile uint32_t RecentTime;
#endif



extern void vUART_Init(void);
extern void vUART_UART3Handler(void);

#endif /* UART_H_ */
