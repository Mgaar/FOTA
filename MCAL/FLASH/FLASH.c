/*
 * FLASH.c
 *
 *  Created on: Oct 23, 2023
 *      Author: lenovo
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "FLASH_Inteface.h"
#include "FLASH_Private.h"

void MFDI_voidSectorErase(u8 Copy_u8SectorNumber)
{
	/*wait if Busy == 1 in SR*/
	while(GET_BIT(MFDI->SR , 16) ==1) ;

	/*Unlock flash if lock bit = 1*/
	if(GET_BIT(MFDI->CR , 31) == 1)
	{
		MFDI->KEYR = MFDI_KEY1 ;
		MFDI->KEYR = MFDI_KEY2 ;
	}

	/*Set Number Of Sectors  in CR */
	MFDI->CR &= 0XFFFFFF87 ;     /*clear bits from bit3 to bit6*/
	MFDI->CR |= Copy_u8SectorNumber<<3  ;

	/*Set SER bit --> to Activate Sector Erase*/
	SET_BIT(MFDI->CR,1) ;

	/*Set Starting Bit */
	SET_BIT(MFDI->CR,16) ;

	/*wait if Busy == 1 in SR*/
	while(GET_BIT(MFDI->SR , 16) ==1) ;

	/*Set EOP Bit in SR --> to Clear the Flag OF EOF */
	SET_BIT(MFDI->SR,0) ;

	/*Clear SER bit --> to Deactivate Sector Erase*/
	CLR_BIT(MFDI->CR,1) ;
}


void MFDI_voidEraseAppArea(u8 app)
{
	u8 LOC_u8Iterator ;
	u8 size=0;
	if (app==1)
	{
		LOC_u8Iterator = 2;
		size=5;
	}
	else if (app==2)
	{
		LOC_u8Iterator = 5;
				size=6;
	}
	for(  ; LOC_u8Iterator < size ; LOC_u8Iterator++)
	{
		MFDI_voidSectorErase(LOC_u8Iterator) ;
	}
}

void MFDI_voidFlashWrite(u32 Copy_u32Address ,u16* Copy_PtrData, u8 Copy_u8DataLength)
{
	u8 LOC_u8Iterator ;

	/*wait if Busy == 1 in SR*/
	while(GET_BIT(MFDI->SR , 16) ==1) ;

	/*Unlock flash if lock bit = 1*/
	if(GET_BIT(MFDI->CR , 31) == 1)
	{
		MFDI->KEYR = MFDI_KEY1 ;
		MFDI->KEYR = MFDI_KEY2 ;
	}

	/*Select PSize in CR --> Half Word*/
	MFDI->CR &= 0XFFFFFCFF ;     /*clear bits from bit8 to bit9  -->[1100]*/
	MFDI->CR |= WRITE_HALF_WORD<<8  ;

    for(LOC_u8Iterator = 0 ; LOC_u8Iterator < Copy_u8DataLength ; LOC_u8Iterator++ )
    {
	/*Set PG Bit in CR --> to Activate Programming Flash*/
	SET_BIT(MFDI->CR,0) ;

	/*Set Address to write to it
	 *
	 *((volatie u16 * )address) = Data[index] */
/* lw 3ayez tzbt el high address 5ly u32 yob2a u64*/
	*((volatile u16*)Copy_u32Address) = Copy_PtrData[LOC_u8Iterator]  ;
	Copy_u32Address +=2 ;

	/*wait if Busy == 1 in SR*/
	while(GET_BIT(MFDI->SR , 16) ==1) ;
	/*Set EOP Bit in SR --> to Clear the Flag OF EOF */
	SET_BIT(MFDI->SR,0) ;
	/*Clear PG bit --> to Deactivate Programming*/
	CLR_BIT(MFDI->CR,0) ;
    }
}



