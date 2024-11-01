/*************************/
/* Mohamed Elgaar        */
/* 17-09-2023            */
/* v1.0                  */
/*************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H
void MGPIO_voidSetPinMode (u8 copy_u8Port,u8 copy_u8Pin,u8 copy_u8Mode);
void MGPIO_voidSetOutputPinMode (u8 copy_u8Port,u8 copy_u8Pin,u8 copy_u8Mode,u8 copy_u8Speed);
void MGPIO_voidSetInputPinMode (u8 copy_u8Port,u8 copy_u8Pin,u8 copy_u8Mode );
void MGPIO_voidSetPinValue (u8 copy_u8Port,u8 copy_u8Pin,u8 copy_u8Value);
void MGPIO_u8GetPinValue (u8 copy_u8Port,u8 copy_u8Pin,u8 *copy_u8Value);
void MGPIO_voidSetPinValueBSRR(u8 copy_u8Port,u8 copy_u8Pin,u8 copy_u8Value);
void MGPIO_voidTogPinMode (u8 copy_u8Port,u8 copy_u8Pin);
void MGPIO_voidSetPinAltFun(u8 Copy_u8PortName ,u8 Copy_u8PinNum, u8 Copy_u8AlFun);


/* ports */
#define MGPIOA  0
#define MGPIOB  1
#define MGPIOC  2

/*Pins*/
#define    PIN_0       0
#define    PIN_1       1
#define    PIN_2       2
#define    PIN_3       3
#define    PIN_4       4
#define    PIN_5       5
#define    PIN_6       6
#define    PIN_7       7
#define    PIN_8       8
#define    PIN_9       9
#define    PIN_10      10
#define    PIN_11      11
#define    PIN_12      12
#define    PIN_13      13
#define    PIN_14      14
#define    PIN_15      15

/* pin value */
#define MGPIO_HIGH 1
#define MGPIO_LOW  0

/* pin mode*/
#define MGPIO_INPUT 0
#define MGPIO_OUTPUT 1
#define MGPIO_AltrenativeFunc 2
#define MGPIO_ADC 3

/*INPUT MODE*/
#define    MGPIO_INPUT_FLOATING_MODE      0
#define    MGPIO_INPUT_PULLUP_MODE      1
#define    MGPIO_INPUT_PULLDOWN_MODE    2

/*OUTPUT MODE*/
#define    MGPIO_OUTPUT_PUSHPULL_MODE      0
#define    MGPIO_OUTPUT_OPENDRAIN_MODE     1




/*output speed*/
#define MGPIO_SPEED_LOW  0
#define MGPIO_SPEED_MED  1
#define MGPIO_SPEED_HIGH 2
#define MGPIO_SPEED_VERYHIGH 3


#endif
