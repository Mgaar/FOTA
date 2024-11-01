/*************************/
/* Mohamed Elgaar        */
/* 17-09-2023            */
/* v1.0                  */
/*************************/



#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GPIO_Interface.h"
#include "GPIO_Private.h"
#include "GPIO_Cfg.h"



void MGPIO_voidSetPinMode (u8 copy_u8Port,u8 copy_u8Pin,u8 copy_u8Mode)
{
switch (copy_u8Port)
{
case MGPIOA:
GPIOA->MODER&=~(PINMODEMASK<<(copy_u8Pin*2));
GPIOA->MODER|=(u32)(copy_u8Mode<<(copy_u8Pin*2));
break;
case MGPIOB:
GPIOB->MODER&=~(PINMODEMASK<<(copy_u8Pin*2));
GPIOB->MODER|=(u32)(copy_u8Mode<<(copy_u8Pin*2));
break;
case MGPIOC:
GPIOC->MODER&=~(PINMODEMASK<<(copy_u8Pin*2));
GPIOC->MODER|=(u32)(copy_u8Mode<<(copy_u8Pin*2));
break;
default : 
//error 
break;	
}
	
}
 
void MGPIO_voidSetOutputPinMode (u8 copy_u8Port,u8 copy_u8Pin,u8 copy_u8Mode,u8 copy_u8Speed)
{
switch (copy_u8Port)
{
case MGPIOA:
GPIOA->OTYPER&=~(OUTPUTMODEMASK<<(copy_u8Pin));
GPIOA->OTYPER|=(u32)(copy_u8Mode<<(copy_u8Pin));
GPIOA->OSPEEDR&=~(SPEEDMASK<<(copy_u8Pin*2));
GPIOA->OSPEEDR|=(u32)(copy_u8Speed<<(copy_u8Pin*2));
break;
case MGPIOB:
GPIOB->OTYPER&=~(OUTPUTMODEMASK<<(copy_u8Pin));
GPIOB->OTYPER|=(u32)(copy_u8Mode<<(copy_u8Pin));
GPIOB->OSPEEDR&=~(SPEEDMASK<<(copy_u8Pin*2));
GPIOB->OSPEEDR|=(u32)(copy_u8Speed<<(copy_u8Pin*2));
break;
case MGPIOC:
GPIOC->OTYPER&=~(OUTPUTMODEMASK<<(copy_u8Pin));
GPIOC->OTYPER|=(u32)(copy_u8Mode<<(copy_u8Pin));
GPIOC->OSPEEDR&=~(SPEEDMASK<<(copy_u8Pin*2));
GPIOC->OSPEEDR|=(u32)(copy_u8Speed<(copy_u8Pin*2));
break;
default : 
//error 
break;		
}	
}

void MGPIO_voidSetInputPinMode (u8 copy_u8Port,u8 copy_u8Pin,u8 copy_u8Mode )
{
	switch (copy_u8Port)
{
case MGPIOA:

GPIOA->PUPDR&=~(INPUTMASK<<(copy_u8Pin*2));
GPIOA->PUPDR|=(u32)(copy_u8Mode<<(copy_u8Pin*2));
break;
case MGPIOB:

GPIOB->PUPDR&=~(INPUTMASK<<(copy_u8Pin*2));
GPIOB->PUPDR|=(u32)(copy_u8Mode<<(copy_u8Pin*2));
break;
case MGPIOC:

GPIOC->PUPDR&=~(INPUTMASK<<(copy_u8Pin*2));
GPIOC->PUPDR|=(u32)(copy_u8Mode<<(copy_u8Pin*2));
break;
default : 
//error 
break;
}
}
void MGPIO_voidSetPinValue (u8 copy_u8Port,u8 copy_u8Pin,u8 copy_u8Value)
{

switch (copy_u8Port)
{	
case MGPIOA:
GPIOA->ODR&=~(OUTPUTVALUEMASK<<copy_u8Pin);
GPIOA->ODR|=(copy_u8Value<<copy_u8Pin);

break;
case MGPIOB:
GPIOB->ODR&=~(OUTPUTVALUEMASK<<copy_u8Pin);
GPIOB->ODR|=(copy_u8Value<<copy_u8Pin);

break;
case MGPIOC:
GPIOC->ODR&=~(OUTPUTVALUEMASK<<copy_u8Pin);
GPIOC->ODR|=(copy_u8Value<<copy_u8Pin);
break;
default : 
//error 
break;
}
	
}

void MGPIO_voidGetPinValue (u8 copy_u8Port,u8 copy_u8Pin,u8 *copy_u8Value)
{
switch (copy_u8Port)
{	
case MGPIOA:
*copy_u8Value = GET_BIT((GPIOA->IDR),copy_u8Pin);
break;
case MGPIOB:

*copy_u8Value=GET_BIT((GPIOB->IDR),copy_u8Pin);
break;
case MGPIOC:

*copy_u8Value=GET_BIT(GPIOC->IDR,copy_u8Pin);
break;
default : 
//error 
break;
}
}


void MGPIO_voidSetPinValueBSRR(u8 copy_u8Port,u8 copy_u8Pin,u8 copy_u8Value)
{
	
switch (copy_u8Port)
{	
case MGPIOA:
if (copy_u8Value==1)
{

	SET_BIT(GPIOA->BSRR,(copy_u8Pin));
}
else 
{

    SET_BIT(GPIOA->BSRR,(copy_u8Pin+RESETBASE));

}
break;
case MGPIOB:

if (copy_u8Value)
{

	SET_BIT(GPIOB->BSRR,(copy_u8Pin));
}
else 
{

    SET_BIT(GPIOB->BSRR,(copy_u8Pin+RESETBASE));

}
break;
case MGPIOC:


if (copy_u8Value)
{

	SET_BIT(GPIOC->BSRR,(copy_u8Pin));
}
else 
{

    SET_BIT(GPIOC->BSRR,(copy_u8Pin+RESETBASE));

}
break;
default : 
//error 
break;
}	
	
	
}

void MGPIO_voidTogPinMode (u8 copy_u8Port,u8 copy_u8Pin)
{

	switch (copy_u8Port)
	{
	case MGPIOA:
		TOG_BIT(GPIOA->ODR,copy_u8Pin);

	break;
	case MGPIOB:
		TOG_BIT(GPIOB->ODR,copy_u8Pin);

	break;
	case MGPIOC:
		TOG_BIT(GPIOC->ODR,copy_u8Pin);
	break;
	default :
	//error
	break;
	}

}


void MGPIO_voidSetPinAltFun(u8 Copy_u8PortName ,u8 Copy_u8PinNum, u8 Copy_u8AlFun) 
{
	if(Copy_u8PinNum <=7U)
	{
		switch(Copy_u8PortName)
		{
		case MGPIOA:GPIOA->AFRL  |=(u32)(Copy_u8AlFun << (4U*Copy_u8PinNum)) ; break ;
		case MGPIOB:GPIOB->AFRL  |=(u32)(Copy_u8AlFun << (4U*Copy_u8PinNum)) ; break ;
		case MGPIOC:GPIOC->AFRL  |=(u32)(Copy_u8AlFun << (4U*Copy_u8PinNum)) ; break ;
		default : break ;
		}
	}
	else
	{
		switch(Copy_u8PortName)
		{
		case MGPIOA:GPIOA->AFRH  |=(u32)(Copy_u8AlFun << (4U*(Copy_u8PinNum%8))) ; break ;
		case MGPIOB:GPIOB->AFRH  |=(u32)(Copy_u8AlFun << (4U*(Copy_u8PinNum%8))) ; break ;
		case MGPIOC:GPIOC->AFRH  |=(u32)(Copy_u8AlFun << (4U*(Copy_u8PinNum%8))) ; break ;
		default : break ;
		}

	}
}
