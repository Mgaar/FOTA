#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include"ESP_Interface.h"
#include"ESP_Config.h"

#include "USART_Interface.h"
#include "USART_Private.h"

#include "GPIO_Interface.h"

#include"STK_Interface.h"

#include "MCU_ID.h"

#include <stdio.h>
#include <string.h>

volatile u8 Data_Wifi[20000];
static volatile  u16 j=0;
static u16 counter;

void yarab (void)
{
	Data_Wifi[j]=MUSART1->DR;
	j++;
}

u8 ESP_Init(void)
{
	u8 result=0;
	MUSART1_VidSetCallBack(&yarab);
	clear_buffer();
	u8 counter =0;
	while(result==0&&counter<255)
	{
		MUSART1_VidSendStringSynch( (u8 *)"ATE0\r\n" );
		result=CheckRecieve(1);
		counter++;
		clear_buffer();
	}
	if (counter == 255)
		return 0x55;
	counter =0;
	MSTK_voidSetBusyWait(2000);
	result=0;
	/*Set Station mode */
	while(result==0&&counter <255)
	{
		MUSART1_VidSendStringSynch((u8 *)"AT+CWMODE=1\r\n");
		MSTK_voidSetBusyWait(2000);
		result=CheckRecieve(1);
		counter++;
		clear_buffer();
	}
	if (counter == 255)
		return 0x55;

	return 1;
}


u8 CheckRecieve(u8 casenum)
{
	u8 back=0;

	for(u8 ch=0;ch<100;ch++)
	{
		if (casenum==1)
		{
			if(Data_Wifi[ch]=='O'&&Data_Wifi[ch+1]=='K')
			{

				back=1;
				return 1;
				break;

			}

		}

		if (casenum==2)
		{

			if(Data_Wifi[ch]=='W'&&Data_Wifi[ch+1]== 'I'&&Data_Wifi[ch+5]=='C')
			{
				back=1;
				return 1;
				break;
			}

		}

		if(casenum==3)
		{

			if(Data_Wifi[ch]=='C'&&Data_Wifi[ch+1]=='O')
			{
				back=1;

				return 1;
				break;

			}
		}
		if(casenum==4)
		{
			if(Data_Wifi[ch]=='>')
			{
				back=1;
				return 1;
				break;
			}
		}
	}

	return back;
}

void clear_buffer(void)
{
	j=0;
	for(u8 i=0;i<100;i++)

	{
		Data_Wifi[i]=0;
	}
}

u8 Router_Connection(u8 *WIFI_Name,u8* Password)
{
	u8 recieve=0;

	u8 counter =0;

	while(recieve==0&&counter<30)
	{
		MUSART1_VidSendStringSynch((u8 *)"AT+CWJAP_CUR=\"");
		MUSART1_VidSendStringSynch((u8 *)WIFI_Name);
		MUSART1_VidSendStringSynch((u8 *)"\",\"" );
		MUSART1_VidSendStringSynch((u8 *)Password);
		MUSART1_VidSendStringSynch((u8 *)"\"\r\n");
		MSTK_voidSetBusyWait(2*2000000);
		recieve=CheckRecieve(2);
		counter++;
		clear_buffer();

	}
	if (counter==30)
		return 0x55;
	return 1;

}



u8 ConnectToServer(u8 * IP,u8 *PORT)
{
	u8 recieve=0;
	u8 counter=0;
	while(recieve==0&&counter<255)
	{
		MUSART1_VidSendStringSynch((u8 *)"AT+CIPSTART=\"TCP\",\"" );
		MUSART1_VidSendStringSynch((u8 *)IP);
		MUSART1_VidSendStringSynch((u8 *)"\",");
		MUSART1_VidSendStringSynch((u8 *)PORT);
		MUSART1_VidSendStringSynch((u8 *)"\r\n");
		MSTK_voidSetBusyWait(20000);

		counter++;
		recieve=CheckRecieve(3);
		clear_buffer();
	}
	if (counter==255)
		return 0x55;
	return 1;

}


u8 SendLength(u8 *Length)
{
	clear_buffer();
	u8 recieve=0;
	u8 counter=0;
	while(recieve==0&&counter<255)
	{
		MUSART1_VidSendStringSynch((u8 *)"AT+CIPSEND=" );
		MUSART1_VidSendStringSynch((u8 *)Length);
		MUSART1_VidSendStringSynch((u8 *)"\r\n");
		MSTK_voidSetBusyWait(10000);
		recieve=CheckRecieve(4);
		counter++;
		clear_buffer();

	}
	if (counter==255)
		return 0x55;
	return 1;

}


u8 isclosed(u16 num)
{




	for(u16 ch=0;ch<=num;ch++)
	{

		if(Data_Wifi[ch]=='C'&&Data_Wifi[ch+1]=='L')
		{
			Data_Wifi[ch]=0;
			Data_Wifi[ch+1]=0;

			return 0;

		}
	}

	return 1;
}


u8 GET (const u8*num,u8*GET,u16 size)
{

	u16 counter=0;
	u8 recieve=0;
	j=0;
	MUSART1_VidSendStringSynch((u8 *)GET);
	MUSART1_VidSendStringSynch((u8 *)num);
	MUSART1_VidSendStringSynch((u8*)"\r\n");

	while (isclosed(size)&&counter<5000)
	{
		counter++;
	}
	if (counter == 5000)
		return 0x55;



	return recieve;
}

u8 appversion(u8*GET,u16 size)
{

	u16 counter=0;
	u8 recieve=0;
	j=0;
	MUSART1_VidSendStringSynch((u8 *)GET);
	MUSART1_VidSendStringSynch((u8*)"\r\n");

	while (isclosed(size)&&counter<5000)
	{
		counter++;
	}
	if (counter == 5000)
		return 0x55;



	return recieve;
}

u8 isupdate(void)
{
	u8 flag=0;
	u8 r=0;
	r=ConnectToServer((u8*)"23.179.32.37",(u8*)"80");

	if (r==0x55)
		return 0x55;
	r=SendLength((u8*)"57");

	if (r==0x55)
		return 0x55;
	r=GET (id,(u8*)"GET http://itifotayarab.freevar.com/script.php?number=",100);

	if (r==0x55)
		return 0x55;
	for(u8 ch=0;ch<=100;ch++)
	{

		if(Data_Wifi[ch]==':')
		{
			flag=	(Data_Wifi[ch+1]-'0');


		}
	}

	clear_buffer();

if (flag)
{
	MSTK_voidSetBusyWait(20000);
	r=ConnectToServer((u8*)"23.179.32.37",(u8*)"80");
		if (r==0x55)
			return 0x55;
		r=SendLength((u8*)"46");
		if (r==0x55)
			return 0x55;
		r=appversion ((u8*)"GET http://itifotayarab.freevar.com/bank.txt",100);
		if (r==0x55)
			return 0x55;
		for(u8 ch=0;ch<=100;ch++)
		{

			if(Data_Wifi[ch]==':')
			{
				flag=	(Data_Wifi[ch+1]);


			}
		}



}

clear_buffer();



	return flag;

}


void updatedone(void)
{
	u8 flag=0;

	while (!flag)
	{
		ConnectToServer((u8*)"23.179.32.37",(u8*)"80");
		SendLength((u8*)"58");
		GET (id,(u8*)"GET http://itifotayarab.freevar.com/script3.php?number=",100);

		for(u8 ch=0;ch<=100;ch++)
		{

			if(Data_Wifi[ch]==':')
			{
				flag=	(Data_Wifi[ch+1]-'0');


			}
		}
	}

	clear_buffer();

}









u8 extractline(u8*line)
{
	u8 flag=0;
	u8 i=0;
	u8 ret=0;
	if (counter==0)
	{
		counter=30;
	}
	for (;ret==0;counter++)
	{
		if (Data_Wifi[counter]=='+')
		{
			flag=1;
			while (flag)
			{
				counter++;
				if (Data_Wifi[counter]==':')
				{
					flag=0;
					counter++;
				}
			}

		}

		if ((Data_Wifi[counter]>='0'&&Data_Wifi[counter]<='9')||(Data_Wifi[counter]>='A'&&Data_Wifi[counter]<='F'))
		{

			line[i]=Data_Wifi[counter];
			line++;

		}
		else if (Data_Wifi[counter]=='X')
		{
			line[i]=0;
			ret=1;
		}
		else if ((Data_Wifi[counter]==0)&&(Data_Wifi[counter+1]==0)&&Data_Wifi[counter+2]=='O')
		{
			line[i]=0;
			counter=0;
			ret=2;
		}
		else if (Data_Wifi[counter]=='o'&&Data_Wifi[counter+1]=='n'&&Data_Wifi[counter+2]=='e')
		{
			line[i]=0;
			counter=0;
			ret=3;
		}


	}
	return ret;
}

u8 Request400 (void)
{
	static u16 i;
	u8 index[5];
	u8 r=0;
	sprintf((char*)index, "%d", i);
	r=ConnectToServer((u8*)"23.179.32.37",(u8*)"80");
	if (r==0x55)
		return 0x55;
	if (i==0)
	{
		r=SendLength((u8*)"56");
		if (r==0x55)
			return 0x55;
		i=399;
	}
	else if (i<1000)
	{
		r=SendLength((u8*)"58");
		if (r==0x55)
			return 0x55;
		i=i+400-2;
	}
	else
	{
		r=SendLength((u8*)"59");
		if (r==0x55)
			return 0x55;
		i=i+400;
	}

	r=GET (index,(u8*)"GET http://itifotayarab.freevar.com/script2.php?line=",20000);
	if (r==0x55)
		return 0x55;
	return 1;


}








