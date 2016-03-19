typedef struct dnode
	{EvDataType data;
	 struct dnode *left,*right;
	}DNode;
void SetDNode(DNode *front);
DNode *NextDNodeRight(DNode *ptr);
DNode *NextDNodeLeft(DNode *ptr);
void InsertRight(DNode *ptr,EvDataType item);
void InsertLeft(DNode *ptr,EvDataType item);
void DeleteDNode(DNode *ptr);

void SetDNode(DNode *front)
	{front->left=front;
	 front->right=front;
	}
DNode *NextDNodeRight(DNode *ptr)
	{return(ptr->right);
	}
DNode *NextDNodeLeft(DNode *ptr)
	{return(ptr->left);
	}
void InsertRight(DNode *ptr,EvDataType item)
	{DNode *q;
	 q=(DNode *)malloc(sizeof(DNode));
	 q->data=item;
	 q->right=ptr->right;
	 ptr->right->left=q;
	 q->left=ptr;
	 ptr->right=q;
	}
void InsertLeft(DNode *ptr,EvDataType item)
	{DNode *q;
	 q=(DNode *)malloc(sizeof(DNode));
	 q->data=item;
	 q->left=ptr->left;
	 ptr->left->right=q;
	 q->right=ptr;
	 ptr->left=q;
	}
void DeleteDNode(DNode *ptr)
	{ptr->left->right=ptr->right;
	 ptr->right->left=ptr->left;
	 free(ptr);
	}







