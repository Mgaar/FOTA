/*************************/
/* Mohamed Elgaar        */
/* 15-09-2023            */
/* v1.0                  */
/*************************/

#ifndef MRCC_PRIVATE_H
#define MRCC_PRIVATE_H

#define MRCC_BASE_ADDRESS 0x40023800

typedef struct {
	volatile u32 CR;           /* RCC clock control register */
	volatile u32 PLLCFGR;      /* RCC PLL configuration register */
	volatile u32 CFGR;         /* RCC clock configuration register */
	volatile u32 CIR;          /* RCC clock interrupt register */
	volatile u32 AHB1RSTR;     /* RCC AHB1 peripheral reset register */
	volatile u32 AHB2RSTR;     /* RCC AHB2 peripheral reset register */
	volatile u32 Reserved0;        /* RCC AHB3 peripheral reset register */
	volatile u32 Reserved1;        /* reserved, 0x1C */
	volatile u32 APB1RSTR;     /* RCC APB1 peripheral reset register */
	volatile u32 APB2RSTR;     /* RCC APB2 peripheral reset register */
	volatile u32 Reserved2[2];      /* Reserved, 0x28,0x2C */
	volatile u32 AHB1ENR;      /* RCC AHB1 peripheral clock register */
	volatile u32 AHB2ENR;      /* RCC AHB2 peripheral clock register */
	volatile u32 Reserved3;        /* RCC AHB3 peripheral clock register */
	volatile u32 Reserved4;        /* Reserved, 0x3C*/
	volatile u32 APB1ENR;      /*     */
	volatile u32 APB2ENR;      /*     */
	volatile u32 Reserved5;        /*     */
	volatile u32 Reserved6;        /*     */
	volatile u32 AHB1LPENR;    /*     */
	volatile u32 AHB2LPENR;    /*     */
	volatile u32 Reserved7;        /*     */
	volatile u32 Reserved8;        /*     */
	volatile u32 APB1LPENR;    /*     */
	volatile u32 APB2LPENR;    /*     */
	volatile u32 Reserved9[2];     /*     */
	volatile u32 BDCR;         /*     */
	volatile u32 CSR;          /*     */
	volatile u32 RESERVED10[2];/*     */
	volatile u32 SSCGR;        /*     */
	volatile u32 PLLI2SCFGR;   /*     */
	volatile u32 RESERVED;     /*     */
	volatile u32 DCKCFGR;      /*     */
	
}MRCC_t;

#define MRCC ((volatile MRCC_t *)MRCC_BASE_ADDRESS)



#endif
