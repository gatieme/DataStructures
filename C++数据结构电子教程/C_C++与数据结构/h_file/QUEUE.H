typedef struct
	{DataType *data;
	 int max;
	 int front,rear,size;
	}Queue;
void SetQueue(Queue *Q,int n);
void FreeQueue(Queue *Q);
int QSize(Queue *Q);
int QEmpty(Queue *Q);
int QFull(Queue *Q);
DataType QGetData(Queue *Q);
void QInsert(Queue *Q,DataType item);
DataType QDelete(Queue *Q);
void ClearQueue(Queue *Q);

void SetQueue(Queue *Q,int n)
	{Q->data=(DataType *)malloc(n*sizeof(DataType));
	 Q->max=n;
	 Q->front=0;
	 Q->rear=0;
	 Q->size=0;
	}
void FreeQueue(Queue *Q)
	{free(Q->data);
	}
DataType QGetData(Queue *Q)
	{if(Q->size==0)
		{printf("Queue is Empty!\n");
		 exit(1);
		}
	 return(Q->data[Q->front]);
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
void QInsert(Queue *Q,DataType item)
	{if(Q->size==Q->max)
		{printf("Queue is full!\n");
		 exit(1);
		}
	 Q->data[Q->rear]=item;
	 Q->rear=(Q->rear+1)%Q->max;
	 Q->size++;
	}
DataType QDelete(Queue *Q)
	{DataType item;
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