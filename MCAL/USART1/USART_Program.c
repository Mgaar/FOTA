#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "USART_Private.h"
#include "USART_Config.h"
#include "USART_Interface.h"
#include"STK_Interface.h"
#define Baud_Rate    0x341
#define Baud_RateForWifi    0xD9
#define  THRESHOLD_VALUE	9000000UL
#define RXNE_INT_ENABLE 1


void (*USART_CALLBACK)(void);

void USART_voidInit(void)
{

	u32 LOC_u64Mantissa = ( F_CPU ) / ( 16 * USART1_BAUD_RATE ) ;

	u32 LOC_u64Fraction = ( ( ( F_CPU * 100 ) / ( 16 * USART1_BAUD_RATE )  ) % 100 ) * 16 ;

	if( LOC_u64Fraction > 1500 ){ LOC_u64Mantissa += 1 ; LOC_u64Fraction  = 0 ; }

	#if MUSART1_STATUS == MUSART1_ENABLE

		MUSART1 -> SR = 0;

		#if   MUSART1_WORD_LENGTH == _8BIT_WORD_LENGTH

					CLR_BIT( MUSART1 -> CR1 , 12 );

		#elif MUSART1_WORD_LENGTH == _9BIT_WORD_LENGTH

					SET_BIT( MUSART1 -> CR1 , 12 );

		#endif

		#if   MUSART1_PARITY == PARITY_DISABLE

					CLR_BIT( MUSART1 -> CR1 , 10 );

		#elif MUSART1_PARITY == EVEN_PARITY

					SET_BIT( MUSART1 -> CR1 , 10 );
					CLR_BIT( MUSART1 -> CR1 , 11 );

		#elif MUSART1_PARITY == ODD_PARITY

					SET_BIT( MUSART1 -> CR1 , 10 );
					SET_BIT( MUSART1 -> CR1 , 11 );

		#endif

		#if  MUSART1_INTERRUPT == INT_DISABLE

					CLR_BIT( MUSART1 -> CR1 , 5 );
					CLR_BIT( MUSART1 -> CR1 , 6 );
					CLR_BIT( MUSART1 -> CR1 , 7 );

		#elif MUSART1_INTERRUPT == TXE_INT_ENABLE

					SET_BIT( MUSART1 -> CR1 , 7 );

		#elif MUSART1_INTERRUPT == TCE_INT_ENABLE

					SET_BIT( MUSART1 -> CR1 , 6 );

		#elif MUSART1_INTERRUPT == RXNE_INT_ENABLE

					SET_BIT( MUSART1 -> CR1 , 5 );

		#endif

		#if   MUSART1_TRANSMITTER == TRANSMITTER_ENABLE

					SET_BIT( MUSART1 -> CR1 , 3 );

		#elif MUSART1_TRANSMITTER == TRANSMITTER_DISABLE

					CLR_BIT( MUSART1 -> CR1 , 3 );

		#endif

		#if   MUSART1_RECEIVER == RECEIVER_ENABLE

					SET_BIT( MUSART1 -> CR1 , 2 );

		#elif MUSART1_RECEIVER == RECEIVER_DISBLE

					CLR_BIT( MUSART1 -> CR1 , 2 );

		#endif

		#if   MUSART1_STOP_BITS == ONE_STOP_BIT

					CLR_BIT( MUSART1 -> CR2 , 12 ); CLR_BIT( MUSART1 -> CR2 , 13 );

		#elif MUSART1_STOP_BITS == HALF_STOP_BIT

					SET_BIT( MUSART1 -> CR2 , 12 ); CLR_BIT( MUSART1 -> CR2 , 13 );

		#elif MUSART1_STOP_BITS == TWO_STOP_BIT

					CLR_BIT( MUSART1 -> CR2 , 12 ); SET_BIT( MUSART1 -> CR2 , 13 );

		#elif MUSART1_STOP_BITS == ONE_AND_HALF_STOP_BIT

					SET_BIT( MUSART1 -> CR2 , 12 ); SET_BIT( MUSART1 -> CR2 , 13 );


		#endif

		MUSART1 -> BRR = ( LOC_u64Mantissa << 4  ) | ( LOC_u64Fraction / 100 ) ;
		SET_BIT( MUSART1 -> CR1 , 13 );

	#elif MUSART1_STATUS == MUSART1_DISABLE
		CLR_BIT( MUSART1 -> CR1 , 0 );

	#endif

}













void USART_voidTransmit(u8* DataToBeTransmitted)
{
    u8 Local_u8Counter = 0;
    CLR_BIT ( MUSART1 -> SR, 5);
    while(DataToBeTransmitted[Local_u8Counter] != '\0')
    {
        MUSART1->DR = DataToBeTransmitted[Local_u8Counter];
        while ((GET_BIT(MUSART1->SR, 6))==0);
        Local_u8Counter++;    
    }
}
/*
 * ASSAF
 * */

void MUSART1_VidSendCharSync ( u8 Copy_u8Char ){

	MUSART1 -> DR = Copy_u8Char ;

	while( GET_BIT( MUSART1 -> SR , 6 ) == 0 );

	CLR_BIT( MUSART1 -> SR , 6 );

}

void MUSART1_VidSendStringSynch ( u8 * Copy_ptrString ){

	u8 LOC_u8Iterator = 0 ;

	while ( Copy_ptrString[ LOC_u8Iterator ] != '\0' )
	{

		MUSART1_VidSendCharSync( Copy_ptrString[ LOC_u8Iterator ] );
		LOC_u8Iterator++ ;

	}

}







u8 USART_voidRecieve()
{
	u8 DataToBerecieved =0;
    /*Check that the recieve buffer contains data*/
    while ((GET_BIT(MUSART1->SR, 5))== 0);

   DataToBerecieved = MUSART1->DR;
   return DataToBerecieved;
}


/*
 * Try this function
 * */

u8 USART_voidInhanceRecieve()
{
	MUSART1->DR=0;
	u8 DataToBerecieved=0,dummy_flag=0;
	u16 temp=0;
    /*Check that the recieve buffer contains data*/
    while ((GET_BIT(MUSART1->SR, 5) )== 0)
    {
    	temp++;
    	if(temp==2000)
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
     DataToBerecieved = MUSART1->DR;
  return DataToBerecieved;

}
u8 USART_BTRecieve(u8 * Copydata)
{
	u8 UART_Receiveflag=1;
	if((GET_BIT(MUSART1->SR, 5))==1)
		{
		*Copydata=MUSART1->DR ;
		}

	else
		{
			UART_Receiveflag=0;
		}

return UART_Receiveflag;
}
void MUSART1_VidSetCallBack(void (*ptr) (void))
{
	USART_CALLBACK=ptr;

}
void MUSART1_VidClearFlags( void ){

	/* Clear all flags */
	MUSART1 -> SR = 0;

}
u8 MUSART1_u8ReadDataRegister ( void ){

	return ( MUSART1 -> DR );

}
void USART1_IRQHandler(void){

	USART_CALLBACK();

}
