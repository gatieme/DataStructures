typedef struct
	{PtrDataType *data;
	 int max;
	 int front,rear,size;
	}Queue;
void SetQueue(Queue *Q,int n);
void FreeQueue(Queue *Q);
int QSize(Queue *Q);
int QEmpty(Queue *Q);
int QFull(Queue *Q);
PtrDataType QGetData(Queue *Q,int pos);
void QInsert(Queue *Q,PtrDataType item);
PtrDataType QDelete(Queue *Q);
void ClearQueue(Queue *Q);

void SetQueue(Queue *Q,int n)
	{Q->data=(PtrDataType *)malloc(n*sizeof(PtrDataType));
	 Q->max=n;
	 Q->front=0;
	 Q->rear=0;
	 Q->size=0;
	}
void FreeQueue(Queue *Q)
	{free(Q->data);
	}
PtrDataType QGetData(Queue *Q,int pos)
	{if(pos<0||pos>Q->size-1)
		{printf("Pos is illegal!\n");
		 exit(1);
		}
	 return(Q->data[(Q->front+pos)%Q->max]);
	}
int QSize(Queue *Q)
	{return(Q->size);
	}
int QEmpty(Queue *Q)
	{if(Q->size==0)
		return(1);
	 return(0);
	}
int QFull(Queue *Q)
	{if(Q->size==Q->max)
		return(1);
	 return(0);
	}
void QInsert(Queue *Q,PtrDataType item)
	{if(Q->size==Q->max)
		{printf("Queue is full!\n");
		 exit(1);
		}
	 Q->data[Q->rear]=item;
	 Q->rear=(Q->rear+1)%Q->max;
	 Q->size++;
	}
PtrDataType QDelete(Queue *Q)
	{PtrDataType item;
	 if(Q->size==0)
		{printf("deleting from an empty queue!\n");
		 exit(1);
		}
	 item=Q->data[Q->front];
	 Q->front=(Q->front+1)%Q->max;
	 Q->size--;
	 return(item);
	}
void ClearQueue(Queue *Q)
	{Q->front=0;
	 Q->rear=0;
	 Q->size=0;
	}