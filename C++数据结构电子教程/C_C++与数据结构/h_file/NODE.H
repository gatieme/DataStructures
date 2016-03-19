typedef struct node
	{DataType data;
	 struct node *next;
	 }Node;
void SetNode(Node *front);
Node *NextNode(Node *ptr);
void InsertAfter(Node *ptr,DataType item);
void DeleteAfter(Node *ptr);

void SetNode(Node *front)
	{front->next=NULL;
	}
Node *NextNode(Node *ptr)
	{return(ptr->next);
	}
void InsertAfter(Node *ptr,DataType item)
	{Node *q;
	 q=(Node *)malloc(sizeof(Node));
	 if(q==NULL)
		{printf("overflow!");
		 exit(1);
		}
	 q->data=item;
	 q->next=ptr->next;
	 ptr->next=q;
	}
void DeleteAfter(Node *ptr)
	{Node *q;
	 q=ptr->next;
	 if(q!=NULL)
		{ptr->next=q->next;
		 free(q);
		}
	}