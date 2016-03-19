#include"dnode.h"
typedef struct
	{DNode *front,*currptr;
	 int size;
	}DLList;
void SetDLList(DLList *L);
void FreeDLList(DLList *L);
int DLListSize(DLList *L);
int DLListEmpty(DLList *L);
int DLListLocate(DLList *L,DataType item);
DataType DLListGetData(DLList *L,int pos);
void DLListInsert(DLList *L,DataType item);
void DLListDelete(DLList *L,int pos);
void ClearDLList(DLList *L);

void SetDLList(DLList *L)
	{L->front=(DNode *)malloc(sizeof(DNode));
	 if(L->front==NULL)
		{printf("overflow");
		 exit(1);
		}
	 SetDNode(L->front);
	 L->currptr=L->front;
	 L->size=0;
	}
int DLListSize(DLList *L)
	{return(L->size);
	}
int DLListEmpty(DLList *L)
	{if(L->size==0)
		return(1);
	 return(0);
	}
int DLListLocate(DLList *L,DataType item)
	{int i;
	 DNode *ptr;
	 ptr=NextDNodeRight(L->front);
	 for(i=0;ptr!=L->front;i++)
		{if(item==ptr->data)
			return(i);
		 ptr=NextDNodeRight(ptr);
		}
	 return(-1);
	}
DataType DLListGetData(DLList *L,int pos)
	{int i;
	 DNode *ptr;
	 if(pos<0||pos>L->size-1)
		{printf("Pos is out of range!\n");
		 exit(1);
		}
	 ptr=NextDNodeRight(L->front);
	 for(i=0;i<pos;i++)
		ptr=NextDNodeRight(ptr);
		return(ptr->data);
	}
void DLListInsert(DLList *L,DataType item)
	{DNode *ptr;
	 if(L->size==0)
		{InsertRight(L->front,item);
		 L->currptr=NextDNodeRight(L->front);
		}
	 else
		{ptr=L->currptr;
		 if(item<=ptr->data)
			{while(ptr!=L->front&&item<ptr->data)
				ptr=NextDNodeLeft(ptr);
			 InsertRight(ptr,item);
			 L->currptr=NextDNodeRight(ptr);
			}
		 else
			{while(ptr!=L->front&&item>ptr->data)
				ptr=NextDNodeRight(ptr);
			 InsertLeft(ptr,item);
			 L->currptr=NextDNodeLeft(ptr);
			}
		}
	 L->size++;
	}
void DLListDelete(DLList *L,int pos)
	{int i;
	 DNode *ptr;
	 if(pos<0||pos>L->size-1)
		{printf("Pos in Delete is illegal");
		 exit(1);
		}
	 ptr=NextDNodeRight(L->front);
	 for(i=0;i<pos;i++)
		ptr=NextDNodeRight(L->front);
	 if(ptr==L->currptr)
		{if(NextDNodeRight(ptr)==L->front)
			L->currptr=NextDNodeLeft(ptr);
		 else
			L->currptr=NextDNodeRight(ptr);
		}
	 DeleteDNode(ptr);
	 L->size--;
	}
void ClearDLList(DLList *L)
	{while(NextDNodeRight(L->front)!=L->front)
		DeleteDNode(NextDNodeRight(L->front));
	 L->currptr=L->front;
	 L->size=0;
	}
void FreeDLList(DLList *L)
	{while(NextDNodeRight(L->front)!=L->front)
		DeleteDNode(NextDNodeRight(L->front));
	 free(L->front);
	}
