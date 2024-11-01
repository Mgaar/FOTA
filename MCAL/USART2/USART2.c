/*
 * USART2.c
 *
 *  Created on: Aug 5, 2023
 *      Author: amres
 */


#include "BIT_MATH.h"
#include "STD_TYPES.h"
//#include"GPIO_Interface.h"
#include "USART2_Private.h"
#include "USART2_Interface.h"
#include "USART2_Config.h"
#include"STK_Interface.h"
#define Baud_Rate    0x341
#define Baud_RateForWifi    0x0D9
#define  THRESHOLD_VALUE	9000000UL
void (*USART2_CallBack)(void);
#define F_CPU                    16000000UL
#define USART2_BAUD_RATE         9600

void USART2_voidInit(void)
{
	u32 LOC_u64Mantissa = ( F_CPU ) / ( 16 * USART2_BAUD_RATE ) ;

		u32 LOC_u64Fraction = ( ( ( F_CPU * 100 ) / ( 16 * USART2_BAUD_RATE )  ) % 100 ) * 16 ;

		if( LOC_u64Fraction > 1500 ){ LOC_u64Mantissa += 1 ; LOC_u64Fraction  = 0 ; }
	/*Enable Rx*/
	#if USART2_RECEIVER==RECEIVER_ENABLE
		SET_BIT(USART2->CR1, 2);

	#elif USART2_RECEIVER==RECEIVER_DISABLE
		CLR_BIT(USART2->CR1, 2);
	#endif

		/*Enable Tx-*/
	#if USART2_TRANSMITTER==TRANSMITTER_ENABLE
		SET_BIT(USART2->CR1, 3);
	#elif USART2_TRANSMITTER==TRANSMITTER_DISABLE
		CLR_BIT(USART2->CR1, 3);
	#endif

		/*Enable Interrupt*/
	#if USART2_INTERRUPT==TXE_INT_ENABLE
		SET_BIT( USART2 -> CR1 , 7 );
	#elif USART2_INTERRUPT == TCE_INT_ENABLE
		SET_BIT( USART2 -> CR1 , 6 );
	#elif USART2_INTERRUPT == RXNE_INT_ENABLE
		SET_BIT( USART2 -> CR1 , 5 );
	#endif

	/*Word Length*/
	#if USART2_WORD_LENGTH==_8BIT_WORD_LENGTH
		CLR_BIT(USART2 -> CR1, 12);
	#elif USART2_WORD_LENGTH==_9BIT_WORD_LENGTH
		SET_BIT(USART2 -> CR1, 12);
	#endif

	/*Parity Bit*/
	#if USART2_PARITY==PARITY_DISABLE
		CLR_BIT(USART2->CR1, 10);
	#elif USART2_PARITY==EVEN_PARITY
		SET_BIT(USART2->CR1,10);
		CLR_BIT(USART2->CR1,9);
	#elif USART2_PARITY==ODD_PARITY
		SET_BIT(USART2->CR1,10);
		SET_BIT(USART2->CR1,9);
	#endif

	/*Stop BITS*/
	#if USART2_STOP_BITS == ONE_STOP_BIT
		CLR_BIT(USART2->CR2,12);
		CLR_BIT(USART2->CR2,13);
	#elif USART2_STOP_BITS == HALF_STOP_BIT
		SET_BIT(USART2->CR2,12);
		CLR_BIT(USART2->CR2,13);
	#elif USART2_STOP_BITS == TWO_STOP_BIT
		CLR_BIT(USART2->CR2,12);
		SET_BIT(USART2->CR2,13);
	#endif

	/*Baud Rate = 9600, USART1 connected to APB2, 8MHZ*/
	//USART1 -> BRR = BAUDRATE9600_8MHZ;

	/*Baud Rate = 9600, USART1 connected to APB2, 16MHZ*/
	//USART1 -> BRR = BAUDRATE9600_16MHZ;

	/*Baud Rate = 9600, USART1 connected to APB2, 25MHZ for wifi module*/
	USART2 -> BRR = ( LOC_u64Mantissa << 4  ) | ( LOC_u64Fraction / 100 ) ;

	SET_BIT(USART2 -> CR1 ,13);
	USART2 -> SR = 0;
}
void USART2SendChar(u8 data)
{
	USART2 -> DR = data;

			/*Poll till the char transmitted successfully*/
			while(GET_BIT(USART2->SR,6)==0);
	}
void USART2_voidTransmit(u8* DataToBeTransmitted)
{
	u16 Local_u8Counter = 0;
	while(DataToBeTransmitted[Local_u8Counter] != '\0')
	{
		USART2 -> DR = DataToBeTransmitted[Local_u8Counter];

		/*Poll till the char transmitted successfully*/
		while(GET_BIT(USART2->SR,6)==0);
		Local_u8Counter++;
	}
}




void USART2_voidReceive(u8* DataToBeReceived)
{
	/*Checked if the received buffer contains Data*/

	while(GET_BIT(USART2 -> SR,5)==0);
	*DataToBeReceived =  (USART2 -> DR);
}


u8 USART2_u8ReturnReceive(void)
{
	while(GET_BIT(USART2 -> SR,5)==0);
	return (USART2 -> DR);
}
u8 USART2_voidInhanceRecieve()
{
	USART2->DR=0;
	u8 DataToBerecieved=0,dummy_flag=0;
	u16 temp=0;
    /*Check that the recieve buffer contains data*/
    while ((GET_BIT(USART2->SR, 5) )== 0)
    {
    	temp++;
    	if(temp==1000)
    	{

    		dummy_flag=1;

    		break;


    	}

    }
    if(dummy_flag==1)
    {
		DataToBerecieved=255;
    }
    else
     DataToBerecieved = USART2->DR;
  return DataToBerecieved;

}

void USART2_u8ReceiveString(u8* DataToBeReceived, char Copy_charTerminator)
{
	u8 Local_u8Iterator;
	do
	{
		DataToBeReceived[Local_u8Iterator]=USART2_u8ReturnReceive;
		Local_u8Iterator++;
	}while(DataToBeReceived[Local_u8Iterator-1] != Copy_charTerminator);
	DataToBeReceived[Local_u8Iterator-1]='\0';
}

void USART2_voidTransmitSingleCharSynch(u8 ARG_u8DataToBeTransmitted)
{
	USART2 -> DR = ARG_u8DataToBeTransmitted;
	while(GET_BIT(USART2->SR,6)==0);
	CLR_BIT(USART2->SR,6);
}

u8 USART2_u8ReceiveArrayOfCharsSync(u32 ARG_u32TimeOut)
{
	u32 Local_u32TimeOut=0;
	u8 Local_u8ReceiveData=0;
	while((GET_BIT((USART2 -> SR),5)) == 0)
	{
		Local_u32TimeOut++;
		if(Local_u32TimeOut == ARG_u32TimeOut)
		{
			Local_u8ReceiveData = 255;
			break;
		}
	}
	if (Local_u8ReceiveData == 0)
	{
		Local_u8ReceiveData = USART2 -> DR;
	}
	return Local_u8ReceiveData;
}

void USART2_voidResetFlags(void)
{
	USART2 -> SR = 0;
}

u8 USART2_u8ReadDataRegisterAsynch( void ){

	return (USART2 -> DR);

}

void USART2_VidSetCallBack( void (*ptr) (void) ){

	USART2_CallBack = ptr ;

}

void USART2_IRQHandler(void)
{
	USART2_CallBack();

}
