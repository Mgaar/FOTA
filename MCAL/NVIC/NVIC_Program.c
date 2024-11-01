#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_Interface.h"
#include "NVIC_Private.h"
#include "NVIC_Config.h"

static u8 StaticGlobal_u8PriorityConfig;

/*Functions Prototypes*/
void MNVIC_voidEnablePerInt(u8 Copy_IntId)
{
    NVIC -> ISER[Copy_IntId / 32] = (1 << (Copy_IntId % 32));
}



void MNVIC_voidDisablePerInt(u8 Copy_IntId)
{
    NVIC -> ICER[Copy_IntId / 32] = (1 << (Copy_IntId % 32));
}

void MNVIC_voidSetPendingFlag(u8 Copy_IntId)
{
    NVIC -> ISPR[Copy_IntId / 32] = (1 << (Copy_IntId % 32));
}
void MNVIC_voidClrPendingFlag(u8 Copy_IntId)
{
    NVIC -> ICPR[Copy_IntId / 32] = (1 << (Copy_IntId % 32));
}

/*Copy_u8PriprityOption: GROUP4BITS_SUBGROUP0BITS, GROUP3BITS_SUBGROUP1BITS, GROUP2BITS_SUBGROUP2BITS, GROUP1BITS_SUBGROUP3BITS, GROUP0BITS_SUBGROUP4BITS*/
void MNVIC_voidSetPriorityConfig(u8 Copy_u8PriprityOption)
{
    StaticGlobal_u8PriorityConfig = VECT_KEY | (Copy_u8PriprityOption << 8);
    SCB -> AIRCR = StaticGlobal_u8PriorityConfig;
}

/*18, 1, 2*/
void MNVIC_voidSetIntPriority(u8 Copy_IntId, u8 Copy_u8GroupId, u8 Copy_u8SubGroupId)
{
    u8 Local_u8Priority = Copy_u8SubGroupId | (Copy_u8GroupId << ((StaticGlobal_u8PriorityConfig - 0x05FA0300)/256)); //0x05FA0400
    NVIC ->IPR[Copy_IntId] = (Local_u8Priority << 4);
}
