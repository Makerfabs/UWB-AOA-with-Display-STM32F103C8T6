#include <stdint.h>

#ifndef _WINT_T
#define _WINT_T
typedef uint32_t wint_t;
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <usart.h>
#include "OSAL.h"

/***********************************************
Function: Create a empty stack;
************************************************/
void osal_CreateQueue(PQUEUE Q,int maxsize)
{
#ifdef ST_CHIP
#else
	Q->pMsg=(Message *)malloc(sizeof(Message)*maxsize);
	if(NULL==Q->pMsg)
	{
		_dbg_printf("Memory allocation failure");
		while(1);
	}
#endif
	Q->front=0;
	Q->rear=0;
	Q->maxsize=maxsize;
}

/***********************************************
Function: Print the stack element;
************************************************/
void osal_TraverseQueue(PQUEUE Q)
{
	//int tmp;
	int i=Q->front;
	_dbg_printf("Q->front :%d,rear: %d\n",Q->front,Q->rear);

	while(i%Q->maxsize!=Q->rear)
	{
		_dbg_printf("i :%d",i);
		_dbg_printf("flag:%d ",Q->pMsg[i].flag);
		_dbg_printf("len:%d ",Q->pMsg[i].len);
		_dbg_printf("msg :");
		#if 0
		for(tmp = 0; tmp < Q->pMsg[i].len; tmp++){
			_dbg_printf("%x ",Q->pMsg[i].buf[tmp]);
		}
		#else
			_dbg_printf("%s ",Q->pMsg[i].buf);

		#endif
		_dbg_printf("\n");
		i++;
	}
	_dbg_printf("\n");
}

bool osal_FullQueue(PQUEUE Q)
{
	if(Q->front==(Q->rear+1)%Q->maxsize)
		return TRUE;
	else
		return FALSE;
}

bool osal_EmptyQueue(PQUEUE Q)
{
	if(Q->front==Q->rear)
		return TRUE;
	else
		return FALSE;
}

bool osal_Enqueue(PQUEUE Q, Message val)
{
	if(osal_FullQueue(Q)){
		//_dbg_printf("osal_Enqueue fault \n");
		return FALSE;
	}
	else
	{
		Q->pMsg[Q->rear].flag = val.flag;
		Q->pMsg[Q->rear].len = val.len;
		memcpy(Q->pMsg[Q->rear].buf, val.buf, val.len);
		Q->rear=(Q->rear+1)%Q->maxsize;
		//_dbg_printf("osal_Enqueue success \n");
		return TRUE;
	}
}

bool osal_Dequeue(PQUEUE Q, Message *val)
{
	if(osal_EmptyQueue(Q))
	{
		return FALSE;
	}
	else
	{
		//*val=Q->pMsg[Q->front];
		memcpy(&(val->flag), &Q->pMsg[Q->front].flag, sizeof(Message));		//赋值结构体
		memset(&Q->pMsg[Q->front].flag, 0, sizeof(Message));				//清除结构体
		Q->front=(Q->front+1)%Q->maxsize;
		if(val->len > QUEUE_MSG_LEN){
			_dbg_printf("error queue msg\n");
			return FALSE;
		}
		return TRUE;
	}
}


void osal_itoa (unsigned int n,char s[])
{
	int i,j;
	char sw_data[32];
	//if((sign=n)<0)//
	//n=-n;//
	i=0;
	do{
		s[i++]=n%10+'0';//
	}
	while ((n/=10)>0);//

	s[i]='\0';
	for(j=i;j>=0;j--){//
		sw_data[i-j] = s[j];
	}
	for(j=1;j<=i;j++){//
		s[j-1] = sw_data[j];
	}
}


void osal_Str2Byte(const char* source, uint8_t* dest, int sourceLen)
{
    short i;
    unsigned char highByte, lowByte;

    for (i = 0; i < sourceLen; i += 2)
    {
        highByte = toupper(source[i]);
        lowByte  = toupper(source[i + 1]);

        if (highByte > 0x39)
            highByte -= 0x37;
        else
            highByte -= 0x30;

        if (lowByte > 0x39)
            lowByte -= 0x37;
        else
            lowByte -= 0x30;

        dest[i / 2] = (highByte << 4) | lowByte;
    }
}


void osal_Hex2Str( const char *sSrc,  char *sDest, int nSrcLen )
{
	int  i;
	char szTmp[3];

	for( i = 0; i < nSrcLen; i++ )
	{
		sprintf( szTmp, "%02X", (uint8_t) sSrc[i] );
		memcpy( &sDest[i * 2], szTmp, 2 );
	}
}

unsigned short osal_Transfer_Byte(unsigned short value)
{
	unsigned short tmp = value;

	value = 0;
#if 1
	value |= (tmp & 0x0100)>> 5;
	value |= (tmp & 0x0200)>> 7;
	value |= (tmp & 0x0400)>> 9;
	value |= (tmp & 0x0800)>> 11;
#else
	value = (tmp & 0xaa)>> 1 | (tmp & 0x55)<<1;
	value = (tmp & 0xcc)>> 2 | (tmp & 0x33)<<2;
	value = (tmp & 0xf0)>> 4 | (tmp & 0x0f)<<4;
#endif
	return value;
}

