#ifndef FLASH_INTERFACE_H_
#define FLASH_INTERFACE_H_

#define START_OF_SECTOR_2	0x08008000
#define RESET_HANDLER_ISR_2	0x08008004

/*
#define START_OF_SECTOR_1	0x08020000
#define RESET_HANDLER_ISR	0x08020004
*/

#define START_OF_SECTOR_5	0x08020000
#define RESET_HANDLER_ISR_5	0x08020004

void MFDI_voidEraseAppArea(u8 app) ;
void MFDI_voidFlashWrite(u32 Copy_u32Address ,u16* Copy_PtrData, u8 Copy_u8DataLength) ;
void MFDI_voidSectorErase(u8 Copy_u8SectorNumber) ;


#endif /* Mcu id config */
