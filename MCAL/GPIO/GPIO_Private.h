/*************************/
/* Mohamed Elgaar        */
/* 17-09-2023            */
/* v1.0                  */
/*************************/

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H
/***** Ports Base addresses *****/
#define GPIOA_BASEADDRESS (0x40020000)
#define GPIOB_BASEADDRESS (0x40020400)
#define GPIOC_BASEADDRESS (0x40020800)
/* regs */
typedef struct 
{
u32 MODER;   //configure the I/O direction mode input - output - alternative function - adc
u32 OTYPER;  //cofigure output type 
u32 OSPEEDR; //configure the I/O output speed
u32 PUPDR;   //configure the I/O pull-up or pull-down
u32 IDR;     //Read input 
u32 ODR;     //write output 
u32 BSRR;
u32 LCKR;    //configuration lock register
u32 AFRL;    //alternate function low register
u32 AFRH;    // alternate function high register

}MGPIO_T;
/* ports */
#define GPIOA ((volatile MGPIO_T*)GPIOA_BASEADDRESS)
#define GPIOB ((volatile MGPIO_T*)GPIOB_BASEADDRESS)
#define GPIOC ((volatile MGPIO_T*)GPIOC_BASEADDRESS)
/* masks */
#define PINMODEMASK     0x00000003
#define OUTPUTMODEMASK  0x00000001
#define OUTPUTVALUEMASK 0x00000001
#define SPEEDMASK       0x00000003
#define INPUTMASK       0x00000003
#define RESETBASE               16
#endif
