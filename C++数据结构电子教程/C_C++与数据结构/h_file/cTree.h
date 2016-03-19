typedef struct cnode
	{int child;
	 struct cnode *next;
	}CNode;
typedef struct
	{DataType data;
	 CNode *front,*rear;
	}CTNode;
typedef struct
	{CTNode *a;
	 int max,root,size;
	}CTree;
void SetCT(CTree *T,int n);
void FreeCT(CTree *T);
int CTLocate(CTree *T,DataType item);
void CTInsert(CTree *T,DataType item);
void PCInsert(CTree *T,DataType p,DataType c);
void ClearCT(CTree *T);

void SetCT(CTree *T,int n)
	{T->a=(CTNode *)malloc(n*sizeof(CTNode));
	 if(T->a==NULL)
		{printf("overflow!\n");
		 exit(1);
		}
	 T->max=n;
	 T->root=-1;
	 T->size=0;
	}

void FreeCT(CTree *T)
	{int i;
	 CNode *ptr;
	 for(i=T->size-1;i>-1;i--)
		while(T->a[i].front!=NULL)
			{ptr=T->a[i].front;
			 T->a[i].front=ptr->next;
			 free(ptr);
			}
	 free(T->a);
	}

int CTLocate(CTree *T,DataType item)
	{int i=0;
	 while(i<T->size&&item!=T->a[i].data)
		i++;
	 if(i<T->size)
		return(i);
	 return(-1);
	}

void CTInsert(CTree *T,DataType item)
	{if(T->size==T->max)
		{printf("overflow!");
		 exit(1);
		}
	 T->a[T->size].data=item;
	 T->a[T->size].front=NULL;
	 T->a[T->size].rear=NULL;
	 T->size++;
	}

void PCInsert(CTree *T,DataType p,DataType c)
	{int i,j;
	 CNode *q;
	 i=CTLocate(T,p);
	 j=CTLocate(T,c);
	 q=(CNode*)malloc(sizeof(CNode));
	 q->child=j;
	 q->next=NULL;
	 if(T->a[i].front==NULL)
		{T->a[i].front=q;
		 T->a[i].rear=q;
		}
	 else
		{T->a[i].rear->next=q;
		 T->a[i].rear=q;
		}
	}

void ClearCT(CTree *T)
	{int i;
	 CNode *ptr;
	 for(i=T->size-1;i>-1;i--)
		while(T->a[i].front!=NULL)
			{ptr=T->a[i].front;
			 T->a[i].front=ptr->next;
			 free(ptr);
			}
	 T->root=-1;
	 T->size=0;
	}