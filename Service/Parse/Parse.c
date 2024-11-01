/*
 * Parse.c
 *
 *  Created on: Oct 23, 2023
 *      Author: lenovo
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "FLASH_Inteface.h"
#include "Parse_Interface.h"

u32 GLB_u32Address  = 0x08000000;


u16 GLB_u16Data[100] ;

u8 APARSER_u8AsciiToHex(u8 Copy_u8Asci)
{

	u8 LOC_u8Result = 0 ;

	if((Copy_u8Asci >=48) && (Copy_u8Asci <=57) )
	{
		LOC_u8Result = Copy_u8Asci - 48 ;
	}
	else
	{
		LOC_u8Result = Copy_u8Asci  - 55 ;
	}

	return LOC_u8Result ;

}



void APARSER_voidParseRecord(u8 * Copy_u8BufRecord)
{
	switch(Copy_u8BufRecord[7])
	{
	case '0' : APARSE_voidParseData(Copy_u8BufRecord);  break ;
	case '4' :setaddress(Copy_u8BufRecord);          break ;
	case '1' : /*End Of File*/                          break ;
	}

}
//02 0000 04 0800 F2
void setaddress(u8* Copy_u8Bufaddress)
{
	/*For Address 4 Digits*/
		u8 LOC_u8Digit0 ;
		u8 LOC_u8Digit1 ;
		u8 LOC_u8Digit2 ;
		u8 LOC_u8Digit3 ;
	/*Receive Low part Address Address*/
		LOC_u8Digit0 = APARSER_u8AsciiToHex(Copy_u8Bufaddress[8]);
		LOC_u8Digit1 = APARSER_u8AsciiToHex(Copy_u8Bufaddress[9]);
		LOC_u8Digit2 = APARSER_u8AsciiToHex(Copy_u8Bufaddress[10]);
		LOC_u8Digit3 = APARSER_u8AsciiToHex(Copy_u8Bufaddress[11]);
		GLB_u32Address=0;
	GLB_u32Address=(LOC_u8Digit0<<28)| (LOC_u8Digit1<<24) | (LOC_u8Digit2<<20) |(LOC_u8Digit3<<16);
}
void APARSE_voidParseData(u8* Copy_u8BufData)
{

	/*For Character Count*/
	u8 LOC_u8CCDigitHigh ;
	u8 LOC_u8CCDigitLow ;
	u8 LOC_u8CharacterCount ;

	/*For Address 4 Digits*/
	u8 LOC_u8Digit0 ;
	u8 LOC_u8Digit1 ;
	u8 LOC_u8Digit2 ;
	u8 LOC_u8Digit3 ;

	/*Iterator For Data  Loop*/
	u8 LOC_u8Result = 0 ;


	/*Receive CC*/
	LOC_u8CCDigitHigh = APARSER_u8AsciiToHex(Copy_u8BufData[0]) ;
	LOC_u8CCDigitLow  = APARSER_u8AsciiToHex(Copy_u8BufData[1]);
	LOC_u8CharacterCount =  LOC_u8CCDigitHigh<<4 | LOC_u8CCDigitLow ;
	/*Receive Low part Address Address*/
	LOC_u8Digit0 = APARSER_u8AsciiToHex(Copy_u8BufData[2]);
	LOC_u8Digit1 = APARSER_u8AsciiToHex(Copy_u8BufData[3]);
	LOC_u8Digit2 = APARSER_u8AsciiToHex(Copy_u8BufData[4]);
	LOC_u8Digit3 = APARSER_u8AsciiToHex(Copy_u8BufData[5]);

	GLB_u32Address &= 0xFFFF0000 ;  ///4000

	GLB_u32Address |= (LOC_u8Digit0<<12) | (LOC_u8Digit1<<8) | (LOC_u8Digit2<<4) |(LOC_u8Digit3)  ;


	for(LOC_u8Result = 0 ; LOC_u8Result < (LOC_u8CharacterCount / 2) ; LOC_u8Result++  )
	{
		/*Receive  Half Word Data [4 Digits]*/
		LOC_u8Digit0 = APARSER_u8AsciiToHex(Copy_u8BufData[(4 * LOC_u8Result) + 8]);
		LOC_u8Digit1 = APARSER_u8AsciiToHex(Copy_u8BufData[(4 * LOC_u8Result) + 9]);
		LOC_u8Digit2 = APARSER_u8AsciiToHex(Copy_u8BufData[(4 * LOC_u8Result) + 10]);
		LOC_u8Digit3 = APARSER_u8AsciiToHex(Copy_u8BufData[(4 * LOC_u8Result) + 11]);
		/*because little Endian*/
		GLB_u16Data[LOC_u8Result] = (LOC_u8Digit2<<12) | (LOC_u8Digit3<<8) | (LOC_u8Digit0<<4) |(LOC_u8Digit1)  ;
	}
	MFDI_voidFlashWrite(GLB_u32Address,GLB_u16Data,(LOC_u8CharacterCount / 2));
}

u8 calculateHexChecksum(u8 *hexLine) {
   u8 checksum = 0;
   u8 byte=0;
   u8 i=0;
      while (hexLine[i+2])
      {
    	  byte=(APARSER_u8AsciiToHex(hexLine[i])<<4)+APARSER_u8AsciiToHex(hexLine[i+1]);
    	          checksum += byte;
    	          i+=2;
      }
      checksum=0x100 - checksum;
      byte=(APARSER_u8AsciiToHex(hexLine[i])<<4)+APARSER_u8AsciiToHex(hexLine[i+1]);

   if (checksum==byte)
    return 1;
    else
    	return 0;
}


