/*
 * ESP_Interface.h
 *
 *  13 oct 2023
 *      Author:Elg3ar
 */

#ifndef ESP_INTERFACE_H_
#define ESP_INTERFACE_H_


u8 ESP_Init(void);
void clear_buffer(void);
u8 CheckRecieve(u8 casenum);
u8 SendLength(u8 *Length);
u8 GetData(u8*GET,u8*LINE);
 u8 ConnectToServer(u8 * IP,u8 *PORT);
 u8 Router_Connection(u8 *WIFI_Name,u8* Password);
 u8 GET (const u8*num,u8*GET,u16 size);
 u8 isclosed(u16 num);
 u8 isconnected(void);
 u8 isupdate(void);
 u8 extractline(u8*line);
 u8 Request400 (void);
 void reporterror(void);
#endif /* ESP_INTERFACE_H_ */
