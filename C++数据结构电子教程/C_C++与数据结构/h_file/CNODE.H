typedef struct cnode
	{int child;
	 struct cnode *next;
	}CNode;
void CInsertAfter(CNode *ptr,int i);
void CDeleteAfter(CNode *ptr);

void CInsertAfter(CNode *ptr,int i)
	{CNode *q;
	 q=(CNode *)malloc(sizeof(CNode));
	 if(q==NULL)
		{printf("overflow");
		 exit(1);
		}
	 q->child=i;
	 q->next=ptr->next;
	 ptr->next=q;
	}
void CDeleteAfter(CNode *ptr)
	{CNode *q;
	 q=ptr->next;
	 if(q!=NULL)
		{ptr->next=q->next;
		 free(q);
		}
	}
