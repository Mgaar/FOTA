/*
 * BL.c
 *
 *  Created on: Oct 23, 2023
 *      Author: lenovo
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "MRCC_Interface.h"
#include "USART_Interface.h"
#include "GPIO_Interface.h"
#include "ESP_Interface.h"
#include "STK_Interface.h"
#include "NVIC_Interface.h"
#include "BL_Interface.h"
#include "USART2_Interface.h"
#include "FLASH_Inteface.h"
#include "Parse_Interface.h"
#include "BL_Private.h"
#include "MSCB_Private.h"


typedef void (*APP_Call)(void) ;

APP_Call Add_To_Call =0 ;

extern u32 GLB_u32Address;
u8 arr[5];
void BL_Init(void)
{
	u8 r=0;
	u32 numer=0;
	MRCC_vInit();
	MRCC_u8EnablePeripheralClock(AHB1,0);
	MRCC_u8EnablePeripheralClock(AHB1,1);
	MRCC_u8EnablePeripheralClock(APB2,4);
	MRCC_u8EnablePeripheralClock(APB1,17);



	MGPIO_voidSetPinMode(MGPIOA,2,MGPIO_AltrenativeFunc);
	MGPIO_voidSetPinMode(MGPIOA,3,MGPIO_AltrenativeFunc);

	MGPIO_voidSetPinAltFun(MGPIOA,2,7);
	MGPIO_voidSetPinAltFun(MGPIOA,3,7);
	USART2_voidInit();


	MGPIO_voidSetPinMode(MGPIOB,6,MGPIO_AltrenativeFunc);
	MGPIO_voidSetPinMode(MGPIOB,7,MGPIO_AltrenativeFunc);
	MGPIO_voidSetPinAltFun(MGPIOB,6,7);
	MGPIO_voidSetPinAltFun(MGPIOB,7,7);
	MNVIC_voidSetPriorityConfig(GROUP3BITS_SUBGROUP1BITS);
	MGPIO_voidSetPinMode(MGPIOA,5,MGPIO_OUTPUT);
	MGPIO_voidSetOutputPinMode(MGPIOA,5,MGPIO_OUTPUT_PUSHPULL_MODE,MGPIO_SPEED_LOW);
	MSTK_voidInit();
	USART_voidInit();
	MNVIC_voidEnablePerInt(37);
	USART2_voidTransmit("start \n");



	r=ESP_Init();
	if(r==0x55)
		BL_VoidJumptoApp();

	MGPIO_voidSetPinValue(MGPIOA,5,MGPIO_HIGH);


	r=Router_Connection((u8*)"Elgaar",(u8*)"12345678");
	if(r==0x55)
		BL_VoidJumptoApp();


	USART2_voidTransmit("Hello WIFI connected\n");

}


void BL_Runnable(void)
{
	u8 u=0;
	u8 s=0;
	u8 ext=0;
	u8 line[50];
	u16 arr[1]={0x01};


	s=isupdate();
	arr[0]=s;
	arr[1]=0;
    USART2_voidTransmit(arr);
    USART2_voidTransmit("\nwe got s\n");

	if (s==0x55)
		BL_VoidJumptoApp();
	if (s)
	{

		u=Request400();
		if(u==0x55)
			BL_VoidJumptoApp();
		if (s=='A')
		{
			MFDI_voidEraseAppArea(1);
				USART2_voidTransmit("app a\n");

		}

		else
		{
			MFDI_voidEraseAppArea(2);
			GLB_u32Address=0x08020000;
				USART2_voidTransmit("app b\n");

		}



		while (ext!=3)
		{
			ext=extractline(line);

			if (ext==1)
			{

				if (calculateHexChecksum(line))
				{
					USART2_voidTransmit(line);
						USART2_voidTransmit("\n");

					APARSER_voidParseRecord(line);
				}

				//	else
				//		BL_VoidJumptoApp();

			}
			else if (ext==2)
			{
				u=Request400();

					USART2_voidTransmit("request 400\n");

				if(u==0x55)
					BL_VoidJumptoApp();

			}
			else if (ext==3)
			{

				updatedone();
					USART2_voidTransmit("update done\n");

				if (s=='A')
				{
					arr[0]=0x00;
				}

				MFDI_voidSectorErase(1);
				MFDI_voidFlashWrite( 0x08004000,arr,1);
				   USART2_voidTransmit("app stored\n");

				BL_VoidJumptoApp();
			}



		}

	}
	else
	{
		BL_VoidJumptoApp();

	}


}



void BL_VoidJumptoApp(void)
{

		USART2_voidTransmit("Jumping \n");
	MGPIO_voidSetPinValue(MGPIOA,5,MGPIO_LOW);

	MNVIC_voidDisablePerInt(37);
	if ((*(u16*)(0x08004000))==0x01)
	{
		//		/*Move Vector Table*/
		USART2_voidTransmit("to b \n");

		SCB_VTOR = START_OF_SECTOR_5 ; //Starting of Sector 1 [Application]

		/*Set Address to call with Reset Handeler_ISR [startup code of Application]*/
		Add_To_Call = *(APP_Call*) RESET_HANDLER_ISR_5 ;

		Add_To_Call() ; //jump Reset handler [startup code]
	}
	else
	{
		USART2_voidTransmit("to a\n");
		/*Move Vector Table*/

		SCB_VTOR = START_OF_SECTOR_2 ; //Starting of Sector 1 [Application]

		/*Set Address to call with Reset Handeler_ISR [startup code of Application]*/
		Add_To_Call = *(APP_Call*) RESET_HANDLER_ISR_2 ;

		Add_To_Call() ; //jump Reset handler [startup code]

	}

}





