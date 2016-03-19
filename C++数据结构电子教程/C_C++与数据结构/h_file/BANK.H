typedef struct
	{int occurtime;
	 int ntype;
	}EvDataType;
#include"evdnode.h"
#include"evdllist.h"
typedef struct
	{int arrivaltime;
	 int servicetime;
	}DataType;
#include"lqueue.h"
typedef struct
	{DLList L;
	 LQueue Q[4];
	 int totaltime,cusnum,closetime;
	}Bank;

void SetBank(Bank *B,int closetime);
void FreeBank(Bank *B);
int BankEmpty(Bank *B);
EvDataType Customer(Bank *B);
void CustomerArrived(Bank *B,EvDataType en,int servicetime,int intertime);
void CustomerDeparture(Bank *B,EvDataType en);
void PrintDLList(Bank *B);
void PrintLQueue(Bank *B);

void SetBank(Bank* B,int closetime)
	{int i;  EvDataType en;
	 SetDLList(&(B->L));
	 en.occurtime=0;
	 en.ntype=-1;
	 DLListInsert(&(B->L),en);
	 for(i=0;i<4;i++)
		SetLQueue(&(B->Q[i]));
	 B->totaltime=0;
	 B->cusnum=0;
	 B->closetime=closetime;
	}
void FreeBank(Bank *B)
	{int i;
	 for(i=0;i<4;i++)
		FreeLQueue(&(B->Q[i]));
	 FreeDLList(&(B->L));
	}
int BankEmpty(Bank *B)
	{if(DLListEmpty(&(B->L)))
		return(1);
	 return(0);
	}
EvDataType Customer(Bank *B)
	{EvDataType en;
	 en=DLListGetData(&(B->L),0);
	 DLListDelete(&(B->L),0);
	 return(en);
	}
void CustomerArrived(Bank *B,EvDataType en,int servicetime,int intertime)
	{int i,min;
	 DataType cn;
	 EvDataType en1;
	 en1.occurtime=en.occurtime+intertime;
	 en1.ntype=-1;
	 if(en1.occurtime<=B->closetime)
		DLListInsert(&(B->L),en1);
	 cn.arrivaltime=en.occurtime;
	 cn.servicetime=servicetime;
	 min=0;
	 for(i=1;i<4;i++)
		if(LQSize(&(B->Q[min]))>LQSize(&(B->Q[i])))
			min=i;
	 LQInsert(&(B->Q[min]),cn);
	 B->cusnum++;
	 if(LQSize(&(B->Q[min]))==1)
		{en1.occurtime=en.occurtime+servicetime;
		 en1.ntype=min;
		 DLListInsert(&(B->L),en1);
		}
	}
void CustomerDeparture(Bank *B,EvDataType en)
	{int i;
	 DataType cn;EvDataType en1;
   i=en.ntype;     cn=LQGetData(&(B->Q[i]));
   B->totaltime=B->totaltime+(en.occurtime-cn.arrivaltime);
   LQDelete(&(B->Q[i]));
   if(!LQEmpty(&(B->Q[i])))
    {cn=LQGetData(&(B->Q[i]));
		en1.occurtime=en.occurtime+cn.servicetime; en1.ntype=i;
      DLListInsert(&(B->L),en1);
     }
  }



void PrintDLList(Bank *B)
	{int n,i;
	 EvDataType en;
	 n=DLListSize(&(B->L));
	 for(i=0;i<n;i++)
		{en=DLListGetData(&(B->L),i);
		 printf("(%-2d   %2d)\n",en.occurtime,en.ntype);
		}
	}
void PrintLQueue(Bank *B)
	{int i,pos,n;
	 DataType cn;
	 Node *ptr;
	 for(i=0;i<4;i++)
		{printf("%d ",i);
		 n=LQSize(&(B->Q[i]));
		 ptr=NextNode((B->Q[i]).front);
		 for(pos=0;pos<n;pos++)
			{cn=ptr->data;
			 printf("  (%-2d  %2d) ",cn.arrivaltime,cn.servicetime);
			 ptr=NextNode(ptr);
			}
		 printf("\n");
		}
	}

