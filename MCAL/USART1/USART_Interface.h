#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

void USART_voidInit(void);
void MUSART1_VidSendStringSynch ( u8 * Copy_ptrString );
u8 USART_voidRecieve();
u8 USART_voidInhanceRecieve();
u8 USART_BTRecieve(u8 * Copydata);
void MUSART1_VidSendCharSync ( u8 Copy_u8Char );
void MUSART1_VidSetCallBack(void (*ptr) (void));
void MUSART1_VidClearFlags( void );
u8 MUSART1_u8ReadDataRegister ( void );

u8 USART_voidInhanceRecieve2(void);
u8 USART1_u8ReceiveTimeOut(u32 Copy_u32timeout);
u8 u8ValidateCmd(u32 Copy_u32timeout);
#endif
