/*
 * USART2_Config.h
 *
 *  Created on: Aug 5, 2023
 *      Author: amres
 */

#ifndef USART2_CONFIG_H_
#define USART2_CONFIG_H_
#define TRANSMITTER_disable       100
#define USART2_WORD_LENGTH       _8BIT_WORD_LENGTH
#define USART2_PARITY            PARITY_DISABLE
#define USART2_INTERRUPT         RXNE_INT_DISABLE

#define USART2_TRANSMITTER       TRANSMITTER_ENABLE
#define USART2_RECEIVER          RECEIVER_ENABLE

#define USART2_STOP_BITS         ONE_STOP_BIT

/*e.g. Baud Rate= 9600*/
	/*Tx/Rx Baud = 16000000/(16*9600)= 1000000/9600 = 104.1875*/
	/*Convert it to a hex val. to be placed in BRR Reg==> 104=0x68, 0.1875*16= 0x3*/
#define BAUDRATE9600_8MHZ     0x341
#define BAUDRATE9600_16MHZ    0x683
#define BAUDRATE115200_25MHZ  0xD9



#endif /* USART2_CONFIG_H_ */
