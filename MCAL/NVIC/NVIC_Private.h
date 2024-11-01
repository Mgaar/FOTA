/*File Gaurd*/
#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

//NVIC Base Address is 0xE000E100
typedef struct 
{
    volatile u32 ISER[32];   //volatile u32 ISER[8]; 
    volatile u32 ICER[32];
    volatile u32 ISPR[32];
    volatile u32 ICPR[32];
    volatile u32 IABR[32];
    volatile u32 RES[32];
    //volatile u32 IPR[60];
    volatile u8 IPR[90];
}NVIC_t;


#define NVIC    ((volatile NVIC_t*)0xE000E100)

//SCB Base Address --> 0xE000ED00
typedef struct
{
    volatile u32 CPUID;
    volatile u32 ICSR;
    volatile u32 VTOR;
    volatile u32 AIRCR;			
    volatile u32 SCR;
    volatile u32 CCR;
    volatile u32 SHPR[3];
    volatile u32 SHCSR;
    volatile u32 CFSR;
    volatile u32 HFSR;
    volatile u32 RESERVED;
    volatile u32 MMFAR;
    volatile u32 BFAR;
}SCB_t;

#define SCB		((volatile SCB_t*)0xE000ED00)

#define VECT_KEY    0x05FA0000
#endif