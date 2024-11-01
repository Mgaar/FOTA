/*
 * USART2_Interface.h
 *
 *  Created on: Aug 5, 2023
 *      Author: amres
 */

#ifndef USART2_INTERFACE_H_
#define USART2_INTERFACE_H_
void USART2_voidInit(void);


void USART2_voidInit(void);
void USART2_voidTransmit(u8* DataToBeTransmitted);
void USART2_voidReceive(u8* DataToBeReceived);
u8 USART2_u8ReturnReceive(void);
void USART2_u8ReceiveString(u8* DataToBeReceived, char Copy_charTerminator);
void USART2_voidTransmitSingleCharSynch(u8 ARG_u8DataToBeTransmitted);
u8 USART2_u8ReceiveArrayOfCharsSync(u32 ARG_u32TimeOut);
void USART2_voidResetFlags(void);
u8 USART2_u8ReadDataRegisterAsynch(void);
void USART2_VidSetCallBack( void (*ptr) (void));

u8 USART2_voidInhanceRecieve();
#endif /* USART2_INTERFACE_H_ */
