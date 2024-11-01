/*
 * USART2_Private.h
 *
 *  Created on: Aug 5, 2023
 *      Author: amres
 */

#ifndef USART2_PRIVATE_H_
#define USART2_PRIVATE_H_
typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}USART_t;

//#define USART1			((volatile USART_t*)0x40011000)
//#define USART6			((volatile USART_t*)0x40011400)
#define USART2			    ((volatile USART_t*)0x40004400)




#endif /* USART2_PRIVATE_H_ */
