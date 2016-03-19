typedef struct TNode
	{DataType data;
	 struct TNode  *left,*right;
	}TNode;
void SetTNode(TNode *ptr,DataType item);
TNode *GetTNode(DataType item,TNode *left,TNode *right);

void SetTNode(TNode *ptr,DataType item)
	{ptr->left=NULL;
	 ptr->right=NULL;
	 ptr->data=item;
	}
TNode *GetTNode(DataType item,TNode *left,TNode *right)
	{TNode *ptr;
	 ptr=(TNode *)malloc(sizeof(TNode));
	 ptr->left=left;
	 ptr->right=right;
	 ptr->data=item;
	 return(ptr);
	}


