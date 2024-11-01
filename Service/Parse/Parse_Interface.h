#ifndef PARSE_INTERFACE_H_
#define PARSE_INTERFACE_H_

u8 APARSER_u8AsciiToHex(u8 Copy_u8Asci) ;

u8 calculateHexChecksum(u8 *hexLine);
void APARSER_voidParseRecord(u8 * Copy_u8BufRecord) ;




void APARSE_voidParseData(u8* Copy_u8BufData) ;
#endif /* Mcu id config */
