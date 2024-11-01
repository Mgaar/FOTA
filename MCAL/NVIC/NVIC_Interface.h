/*File Gaurd*/
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

/*Functions Prototypes*/
void MNVIC_voidEnablePerInt(u8 Copy_IntId);
void MNVIC_voidDisablePerInt(u8 Copy_IntId);
void MNVIC_voidSetPendingFlag(u8 Copy_IntId);
void MNVIC_voidClrPendingFlag(u8 Copy_IntId);
void MNVIC_voidSetPriorityConfig(u8 Copy_u8PriprityOption);
void MNVIC_voidSetIntPriority(u8 Copy_IntId, u8 Copy_u8GroupId, u8 Copy_u8SubGroupId);

#define GROUP4BITS_SUBGROUP0BITS            0b011  
#define GROUP3BITS_SUBGROUP1BITS            0b100   //4
#define GROUP2BITS_SUBGROUP2BITS            0b101   
#define GROUP1BITS_SUBGROUP3BITS            0b110
#define GROUP0BITS_SUBGROUP4BITS            0b111


#endif
