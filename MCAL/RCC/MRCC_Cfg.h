/*************************/
/* Mohamed Elgaar        */
/* 15-09-2023            */
/* v1.0                  */
/*************************/

#ifndef MRCC_CFG_H
#define MRCC_CFG_H

/*
HSI 
HSE 
PLL 
*/
#define CLOCK_SOURCE HSI
/*
PLL_HSI 
PLL_HSE_BYPASS
PLL_HSE_NBYBASS
*/
#define PLL_SOURCE PLL_HSI 
/*
HSE_Crystal
HSE_Rc
*/

#define HSE_SOURCE HSE_Crystal

#define PLLM 8 //division factor must be 2<= & <=63
#define PLLN (3*84)//multiplcation factor must be between 193 to 432
/*
PLL2 
PLL4 
PLL6 
PLL8 
*/
#define PLLP  PLL6 


#endif
