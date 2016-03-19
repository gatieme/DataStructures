#include"node.h"
typedef struct
	{Node *front;
	 int size;
	 }LList;
void SetLList(LList *L);
int LListSize(LList *L);
int LListEmpty(LList *L);
int LListLocate(LList *L,DataType item);
DataType LListGetData(LList *L,int pos);
void LListInsert(LList *L,DataType item,int pos);
void LListSetData(LList *L,DataType item,int pos);
void ClearLList(LList *L);
void FreeLList(LList *L);
void LListDelete(LList *L,int pos);

void SetLList(LList *L)
	{L->front=(Node *)malloc(sizeof(Node));
	 if(L->front==NULL)
		{printf("overflow\n");
		 exit(1);
		}
	 SetNode(L->front);
	 L->size=0;
	}
int LListSize(LList *L)
	{return(L->size);
	}
int LListEmpty(LList *L)
	{if(L->size==0)
		return(1);
	 else
		return(0);
	}
int LListLocate(LList *L,DataType item)
	{int i;
	 Node *ptr;
	 ptr=NextNode(L->front);
	 for(i=0;ptr!=NULL;i++)
		{if(item==ptr->data)
			return(i);
		 ptr=NextNode(ptr);
		}
	 return(-1);
	}

DataType LListGetData(LList *L,int pos)
	{int i;
	 Node *ptr;
	 if(pos<0||pos>L->size-1)
		{printf("Pos is illegal in LListGetData!\n");
		 exit(1);
		}
	 ptr=NextNode(L->front);
	 i=0;
	 while(i<pos)
		{ptr=NextNode(ptr);
		 i++;
		}
	 return(ptr->data);
	}
void LListSetData(LList *L,DataType item,int pos)
	{int i;
	 Node *ptr;
	 if(pos<0||pos>L->size-1)
		{printf("Pos is illegal in LListGetData!\n");
		 exit(1);
		}
	 ptr=NextNode(L->front);
	 for(i=0;i<pos;i++)
	 ptr=NextNode(ptr);
	 ptr->data=item;
	}
void LListDelete(LList *L,int pos)
	{int i;
	 Node *prevptr,*ptr;
	 if(pos<0||pos>L->size-1)
		{printf("Pos is illegal in LDelete!\n");
		 exit(1);
		}
	 prevptr=L->front;
	 ptr=NextNode(L->front);
	 for(i=0;i<pos;i++)
		{prevptr=ptr;
		 ptr=NextNode(ptr);
		}
	 DeleteAfter(prevptr);
	 L->size--;
	}
void LListInsert(LList *L,DataType item,int pos)
	{int i;
	 Node *prevptr,*ptr;
	 if(pos<0||pos>L->size)
		{printf("Pos is illegal in LListInsert!\n");
		 exit(1);
		}
	 prevptr=L->front;
	 ptr=NextNode(L->front);
	 for(i=0;i<pos;i++)
		{prevptr=ptr;
		 ptr=NextNode(ptr);
		}
	 InsertAfter(prevptr,item);
	 L->size++;
	}
void ClearLList(LList *L)
	{while(NextNode(L->front)!=NULL)
	 DeleteAfter(L->front);
	 L->size=0;
	}
void FreeLList(LList *L)
	{while(NextNode(L->front)!=NULL)
	 DeleteAfter(L->front);
	 free(L->front);
	}
