/*
 * timer.h
 *
 *  Created on: Sep 21, 2019
 *      Author: hesha
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "common_header.h"

extern volatile uint32_t time;

extern void Timer0_Init(void);
extern void Timer0Handler(void);


#endif /* TIMER_H_ */
