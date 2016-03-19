typedef struct
	{PDataType *data;
	 int max;
	 int front,rear,size;
	}PQueue;
void SetPQueue(PQueue *Q,int n);
void FreePQueue(PQueue *Q);
int PQSize(PQueue *Q);
int PQEmpty(PQueue *Q);
int PQFull(PQueue *Q);
PDataType PQGetData(PQueue *Q,int pos);
void PQInsert(PQueue *Q,PDataType item);
PDataType PQDelete(PQueue *Q);
void ClearPQueue(PQueue *Q);

void SetPQueue(PQueue *Q,int n)
	{Q->data=(PDataType *)malloc(n*sizeof(PDataType));
	 Q->max=n;
	 Q->front=0;
	 Q->rear=0;
	 Q->size=0;
	}
void FreePQueue(PQueue *Q)
	{free(Q->data);
	}
PDataType PQGetData(PQueue *Q,int pos)
	{if(pos<0||pos>Q->size-1)
		{printf("Pos is illegal!\n");
		 exit(1);
		}
	 return(Q->data[(Q->front+pos)%Q->max]);
	}
int PQSize(PQueue *Q)
	{return(Q->size);
	}
int PQEmpty(PQueue *Q)
	{if(Q->size==0)
		return(1);
	 return(0);
	}
int PQFull(PQueue *Q)
	{if(Q->size==Q->max)
		return(1);
	 return(0);
	}
void PQInsert(PQueue *Q,PDataType item)
	{if(Q->size==Q->max)
		{printf("Queue is full!\n");
		 exit(1);
		}
	 Q->data[Q->rear]=item;
	 Q->rear=(Q->rear+1)%Q->max;
	 Q->size++;
	}
PDataType PQDelete(PQueue *Q)
	{PDataType item;
	 if(Q->size==0)
		{printf("deleting from an empty queue!\n");
		 exit(1);
		}
	 item=Q->data[Q->front];
	 Q->front=(Q->front+1)%Q->max;
	 Q->size--;
	 return(item);
	}
void ClearPQueue(PQueue *Q)
	{Q->front=0;
	 Q->rear=0;
	 Q->size=0;
	}