typedef struct node
	{DataType data;
	 int balance;
	 struct node  *left,*right;
	}TNode;

void SetTNode(TNode *root,DataType item);
TNode* GetTNode(DataType item,TNode *left,TNode *right);

void SetTNode(TNode *root,DataType item)
	{root->data=item;
	 root->balance=0;
	 root->left=NULL;
	 root->right=NULL;
	}

TNode* GetTNode(DataType item,TNode *left,TNode *right)
	{TNode *ptr;
	 ptr=(TNode *)malloc(sizeof(TNode));
	 ptr->data=item;
	 ptr->balance=0;
	 ptr->left=left;
	 ptr->right=right;
	 return(ptr);
	}