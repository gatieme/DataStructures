typedef struct
	{DNode *front,*currptr;
	 int size;
	}DLList;
void SetDLList(DLList *L);
void FreeDLList(DLList *L);
int DLListSize(DLList *L);
int DLListEmpty(DLList *L);
int DLListLocate(DLList *L,EvDataType item);
EvDataType DLListGetData(DLList *L,int pos);
void DLListInsert(DLList *L,EvDataType item);
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
void FreeDLList(DLList *L)
	{while(NextDNodeRight(L->front)!=L->front)
		DeleteDNode(NextDNodeRight(L->front));
	 free(L->front);
	}
int DLListSize(DLList *L)
	{return(L->size);
	}
int DLListEmpty(DLList *L)
	{if(L->size==0)
		return(1);
	 return(0);
	}
int DLListLocate(DLList *L,EvDataType item)
	{int i;
	 DNode *ptr;
	 ptr=NextDNodeRight(L->front);
	 for(i=0;ptr!=L->front;i++)
		{if(item.occurtime==ptr->data.occurtime)
			return(i);
		 ptr=NextDNodeRight(ptr);
		}
	 return(-1);
	}
EvDataType DLListGetData(DLList *L,int pos)
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
void DLListInsert(DLList *L,EvDataType item)
	{DNode *ptr;
	 if(L->size==0)
		{InsertRight(L->front,item);
		 L->currptr=NextDNodeRight(L->front);
		}
	 else
		{ptr=L->currptr;
		 if(item.occurtime<=ptr->data.occurtime)
			{while(ptr!=L->front&&item.occurtime<ptr->data.occurtime)
			 ptr=NextDNodeLeft(ptr);
			 InsertRight(ptr,item);
			 L->currptr=NextDNodeRight(ptr);
			}
		 else
			{while(ptr!=L->front&&item.occurtime>ptr->data.occurtime)
				ptr=NextDNodeRight(ptr);
			 InsertLeft(ptr,item);
			 L->currptr=NextDNodeLeft(ptr);
			}
		}
	 L->size++;
	}
/*void DLListDelete(DLList *L,EvDataType item)
	{DNode *ptr;
	 ptr=NextDNodeRight(L->front);
	 while(ptr!=L->front&&item!=DNodeGetData(ptr))
		ptr=NextDNodeRight(ptr);
	 if(ptr!=L->front)
		{if(ptr==L->currptr)
			{if(NextDNodeRight(ptr)!=NULL)
				L->currptr=NextDNodeRight(ptr);
			 else if(NextDNodeLeft(ptr)!=NULL)
				L->currptr=NextDNodeLeft(ptr);
			 else
				L->currptr=L->front;
			 DeleteDNode(ptr);
			 L->size--;
		}
	}  */

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













