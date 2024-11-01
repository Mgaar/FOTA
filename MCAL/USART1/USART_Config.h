#ifndef USART_CONFIG_H
#define USART_CONFIG_H

#define F_CPU                    16000000UL

/* USART1_Configuration */

#define MUSART1_STATUS            USART1_ENABLE
#define USART1_BAUD_RATE         115200

#define MUSART1_WORD_LENGTH       _8BIT_WORD_LENGTH
#define MUSART1_PARITY            PARITY_DISABLE
#define MUSART1_INTERRUPT         RXNE_INT_ENABLE

#define MUSART1_TRANSMITTER       TRANSMITTER_ENABLE
#define MUSART1_RECEIVER          RECEIVER_ENABLE
#define MUSART1_STOP_BITS         ONE_STOP_BIT
#endif
