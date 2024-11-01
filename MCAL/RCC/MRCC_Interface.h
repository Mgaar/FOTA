/*************************/
/* Mohamed Elgaar        */
/* 15-09-2023            */
/* v1.0                  */
/*************************/

#ifndef MRCC_INTERFACE_H
#define MRCC_INTERFACE_H

void MRCC_vInit (void);
u8 MRCC_u8EnablePeripheralClock (u8 Copy_u8Bus,u8 Copy_u8Peripheral);
u8 MRCC_u8DisablePeripheralClock (u8 Copy_u8Bus,u8 Copy_u8Peripheral);
void MRCC_vEnableCSS(void);
void MRCC_vDisableCSS(void);









/*
HSI 
HSE 
PLL 
*/
#define HSI 0
#define HSE 1
#define PLL 2

/*
PLL_HSI 
PLL_HSE 
 
*/
#define PLL_HSI 0
#define PLL_HSE 1 
/*
HSE_Crystal
HSE_Rc
*/

#define HSE_Crystal 0
#define HSE_Rc      1

#define AHB1 0
#define AHB2 1
#define APB1 2
#define APB2 3

#define PLL2 0
#define PLL4 1
#define PLL6 2
#define PLL8 3

#define OK 1
#define NOK 0


#endif
