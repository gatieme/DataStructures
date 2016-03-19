#include"node.h"
typedef struct
	{Node *front;
	 Node *rear;
	 int size;
	}LQueue;
void SetLQueue(LQueue *Q);
void FreeLQueue(LQueue *Q);
int LQSize(LQueue *Q);
int LQEmpty(LQueue *Q);
DataType LQGetData(LQueue *Q);
void LQSetData(LQueue *Q,DataType item);
void LQInsert(LQueue *Q,DataType item);
void LQDelete(LQueue *Q);
void ClearLQueue(LQueue *Q);

void SetLQueue(LQueue *Q)
	{Q->front=(Node *)malloc(sizeof(Node));
	 if(Q->front==NULL)
		{printf("overflow");
		 exit(1);
		}
	 SetNode(Q->front);
	 Q->rear=Q->front;
	 Q->size=0;
	}
void FreeLQueue(LQueue *Q)
	{while(NextNode(Q->front)!=NULL)
		DeleteAfter(Q->front);
	 free(Q->front);
	 }
int LQSize(LQueue *Q)
	{return(Q->size);
	}
int LQEmpty(LQueue *Q)
	{if(Q->size==0)
		return(1);
	 return(0);
	}
DataType LQGetData(LQueue *Q)
	{Node *ptr;
	 if(Q->size==0)
		{printf("Queue is empty!\n");
		 exit(1);
		}
	 ptr=NextNode(Q->front);
	 return(ptr->data);
	 }
void LQSetData(LQueue *Q,DataType item)
	{Node *ptr;
	 if(Q->size==0)
		{printf("Setting data to an empty LQueue!\n");
		 exit(1);
		}
	 ptr=NextNode(Q->front);
	 ptr->data=item;
	}
void LQInsert(LQueue *Q,DataType item)
	{InsertAfter(Q->rear,item);
	 Q->rear=NextNode(Q->rear);
	 Q->size++;
	}
void LQDelete(LQueue *Q)
	{Node *ptr;
	 if(Q->size==0)
		{printf("Deleting an empty LQueue!\n");
		 exit(1);
		}
	 DeleteAfter(Q->front);
	 Q->size--;
	 if(Q->size==0)
	 Q->rear=Q->front;
	}

void ClearLQueue(LQueue *Q)
	{while(NextNode(Q->front)!=NULL)
		DeleteAfter(Q->front);
	 Q->rear=Q->front;
	 Q->size=0;
	}