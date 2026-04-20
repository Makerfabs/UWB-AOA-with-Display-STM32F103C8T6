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
