#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

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

#define MUSART1     ((volatile USART_t*)0x40011000)
#define MUSART6     ((volatile USART_t*)0x40011400)
#define MUSART2     ((volatile USART_t*)0x40044000)





#endif
