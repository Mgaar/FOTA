/*************************/
/* Mohamed Elgaar        */
/* 15-09-2023            */
/* v1.0                  */
/*************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "MRCC_Private.h"
#include "MRCC_Interface.h"
#include "MRCC_Cfg.h"

void MRCC_vInit (void)
{
	#if CLOCK_SOURCE==HSI
	
		SET_BIT(MRCC->CR,0);
		while (!GET_BIT(MRCC->CR,1));
	    CLR_BIT(MRCC->CFGR,0);
		CLR_BIT(MRCC->CFGR,1);
		
	#elif  CLOCK_SOURCE==HSE
	
	#if HSE_SOURCE==HSE_Crystal
    CLR_BIT(MRCC->CR,18);
	SET_BIT(MRCC->CR,16);
	while (!GET_BIT(MRCC->CR,17));
	SET_BIT(MRCC->CFGR,0);
    CLR_BIT(MRCC->CFGR,1);
	
	#elif HSE_SOURCE==HSE_Rc
	SET_BIT(MRCC->CR,18);
	SET_BIT(MRCC->CR,16);
	while (!GET_BIT(MRCC->CR,17));
	SET_BIT(MRCC->CFGR,0);
	CLR_BIT(MRCC->CFGR,1);
	#endif
	
	#elif CLOCK_SOURCE==PLL
	#if PLL_SOURCE==PLL_HSI
	SET_BIT(MRCC->CR,0);
	while (!GET_BIT(MRCC->CR,1));
	MRCC->PLLCFGR&=0xffffffc0;
	MRCC->PLLCFGR|=(u32)PLLM;
	MRCC->PLLCFGR&=0xffff803f;
	MRCC->PLLCFGR|=(u32)(PLLN<<6);
	MRCC->PLLCFGR&=0xfffcffff;
	MRCC->PLLCFGR|=(u32)(PLLN<<16);
	SET_BIT(MRCC->CR,24);
	while (!GET_BIT(MRCC->CR,25));
	CLR_BIT(MRCC->CFGR,0);
	SET_BIT(MRCC->CFGR,1);
	
	#elif PLL_SOURCE==PLL_HSE_BYPASS
    SET_BIT(MRCC->CR,18);
	SET_BIT(MRCC->CR,16);
	while (!GET_BIT(MRCC->CR,17));
	MRCC->PLLCFGR&=0xffffffc0;
	MRCC->PLLCFGR|=(u32)PLLM;
	MRCC->PLLCFGR&=0xffff803f;
	MRCC->PLLCFGR|=(u32)(PLLN<<5);
	MRCC->PLLCFGR&=0xfffcffff;
	MRCC->PLLCFGR|=(u32)(PLLN<<16);
	SET_BIT(MRCC->CR,24);
	while (!GET_BIT(MRCC->CR,25));
	CLR_BIT(MRCC->CFGR,0);
	SET_BIT(MRCC->CFGR,1);
	#elif PLL_SOURCE==PLL_HSE_NBYPASS
	CLR_BIT(MRCC->CR,18);
	SET_BIT(MRCC->CR,16);
	while (!GET_BIT(MRCC->CR,17));
	MRCC->PLLCFGR&=0xffffffc0;
	MRCC->PLLCFGR|=(u32)PLLM;
	MRCC->PLLCFGR&=0xffff803f;
	MRCC->PLLCFGR|=(u32)(PLLN<<5);
	MRCC->PLLCFGR&=0xfffcffff;
	MRCC->PLLCFGR|=(u32)(PLLP<<16);
	SET_BIT(MRCC->CR,24);
	while (!GET_BIT(MRCC->CR,25));
	CLR_BIT(MRCC->CFGR,0);
	SET_BIT(MRCC->CFGR,1);
	#endif
	#endif
	
}
u8 MRCC_u8EnablePeripheralClock (u8 Copy_u8Bus,u8 Copy_u8Peripheral)
{
	u8 Local_Error_state = OK;
	switch (Copy_u8Bus)
	{
	case AHB1:SET_BIT(MRCC->AHB1ENR,Copy_u8Peripheral); break; 
    case AHB2:SET_BIT(MRCC->AHB2ENR,Copy_u8Peripheral); break;
    case APB1:SET_BIT(MRCC->APB1ENR,Copy_u8Peripheral); break;
    case APB2:SET_BIT(MRCC->APB2ENR,Copy_u8Peripheral); break;
    default  :Local_Error_state=NOK;break; 	
	}
	return Local_Error_state;
	
}
u8 MRCC_u8DisablePeripheralClock (u8 Copy_u8Bus,u8 Copy_u8Peripheral)
{
	u8 Local_Error_state = OK;
	switch (Copy_u8Bus)
	{
	case AHB1:CLR_BIT(MRCC->AHB1ENR,Copy_u8Peripheral); break; 
    case AHB2:CLR_BIT(MRCC->AHB2ENR,Copy_u8Peripheral); break;
    case APB1:CLR_BIT(MRCC->APB1ENR,Copy_u8Peripheral); break;
    case APB2:CLR_BIT(MRCC->APB2ENR,Copy_u8Peripheral); break;
    default  :Local_Error_state=NOK;break; 	
	}
	return Local_Error_state;
}

void MRCC_vEnableCSS(void)
{
	SET_BIT(MRCC->CR,19);
}
void MRCC_vDisableCSS(void)
{
	CLR_BIT(MRCC->CR,19);
}
