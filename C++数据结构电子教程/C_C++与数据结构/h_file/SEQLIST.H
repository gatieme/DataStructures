typedef struct
	{DataType *data;
	 int max, size;
	}SeqList;
void SetList(SeqList *L,int n);
void FreeList(SeqList *L);
int ListSize(SeqList *L);
int ListEmpty(SeqList *L);
int ListFull(SeqList *L);
DataType GetData(SeqList *L,int pos);
int Locate( SeqList *L,DataType item);
void SetData(SeqList *L,DataType item,int pos);
void Insert(SeqList *L,DataType item,int pos);
void InsertRear(SeqList *L, DataType item);
void Delete(SeqList *L,int pos);
void ClearList(SeqList *L);

void SetList(SeqList *L,int n)
	{L->data=(DataType *)malloc(n*sizeof(DataType));
	 L->max=n;
	 L->size=0;
	}
void FreeList(SeqList *L)
	{free(L->data);
	}
int ListSize(SeqList *L)
	{return(L->size);
	}
int ListEmpty(SeqList *L)
	{if(L->size==0)
		return(1);
	 return(0);
	}
int ListFull(SeqList *L)
	{if(L->size==L->max)
		return(1);
	 return(0);
	}
DataType GetData(SeqList *L,int pos)
	{if(pos<0||pos>L->size-1)
		{printf("Pos in GetData is out of range!\n");
		 exit(1);
		}
	 return(L->data[pos]);
	}
int Locate(SeqList *L,DataType item)
	{int i=0;
	 while(i<=L->size-1&&item!=L->data[i])
		i++;
	 if(i<=L->size-1)
		return(i);
	 return(-1);
	}
void SetData(SeqList *L,DataType item,int pos)
	{if(pos<0||pos>L->size-1)
		{printf("Pos in SetData is out of range!\n");
		 exit(1);
		}
	 L->data[pos]=item;
	}
void Insert(SeqList *L,DataType item,int pos)
	{int j;
	 if(L->size==L->max)
		{printf("SeqList is full!\n");
		 exit(1);
		}
	 if(pos<0||pos>L->size)
		{printf("Pos in Insert is out of range!\n");
		 exit(1);
		}
	 for(j=L->size-1;j>=pos;j--)
		L->data[j+1]=L->data[j];
	 L->data[pos]=item;
	 L->size++;
	}
void InsertRear(SeqList *L, DataType item)
	{if(L->size==L->max)
		{printf("SeqList overflow!");
		 exit(1);
		}
	 L->data[L->size]=item;
	 L->size++;
	}
void Delete(SeqList *L,int pos)
	{int j;
	 if(L->size==0)
		{printf("Delete an empty list!\n");
		 exit(1);
		}
	 if(pos<0||pos>L->size-1)
		{printf("Pos in Delete is out of range\n");
		 exit(1);
		}
	 for(j=pos+1;j<=L->size-1;j++)
		L->data[j-1]=L->data[j];
	 L->size--;
	}
void ClearList(SeqList *L)
	{L->size=0;
	}
