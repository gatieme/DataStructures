typedef struct
	{TNode *root;
	 int size;
	}BSTree;

void DeleteTree(TNode *t);
void LL(TNode **a,TNode **b);
void RR(TNode **a,TNode **b);
void LR(TNode **a,TNode **b);
void RL(TNode **a,TNode **b);
void SetBST(BSTree *T);
void FreeBST(BSTree *T);
int BSTSize(BSTree *T);
int BSTEmpty(BSTree *T);
TNode *GetRoot(BSTree *T);
TNode *BSTLocate(BSTree *T,DataType item);
void BSTInsert(BSTree *T,DataType item);
void ClearBST(BSTree *T);

void DeleteTree(TNode *root)
	{if(root==NULL)
	 return;
	 if(root->left!=NULL)
		DeleteTree(root->left);
	 if(root->right!=NULL)
		DeleteTree(root->right);
	 free(root);
	}
void LL(TNode **a,TNode **b)
	{(*a)->balance=0;
	 (*a)->left=(*b)->right;
	 (*b)->balance=0;
	 (*b)->right=(*a);
	}
void RR(TNode **a,TNode **b)
	{(*a)->balance=0;
	 (*a)->right=(*b)->left;
	 (*b)->balance=0;
	 (*b)->left=(*a);
	}
void LR(TNode **a,TNode **b)
	{TNode *c;
	 c=(*b)->right;
	 (*a)->left=c->right;
	 (*b)->right=c->left;
	 c->left=(*b);
	 c->right=(*a);
	 switch(c->balance)
		{case 0: (*a)->balance=0;
					(*b)->balance=0;
					break;
		 case 1: (*a)->balance=-1;
					(*b)->balance=0;
					break;
		 case -1:(*a)->balance=0;
					(*b)->balance=1;
					break;
		}
	 c->balance=0;
	 (*b)=c;
	}
void RL(TNode **a,TNode **b)
	{TNode *c;
	 c=(*b)->left;
	 (*a)->right=c->left;
	 (*b)->left=c->right;
	 c->right=(*b);
	 c->left=(*a);
	 switch(c->balance)
		{case 0: (*a)->balance=0;
					(*b)->balance=0;
					break;
		 case 1: (*a)->balance=0;
					(*b)->balance=-1;
					break;
		 case -1:(*a)->balance=1;
					(*b)->balance=0;
					break;
		}
		c->balance=0;
		(*b)=c;
	}
void SetBST(BSTree *T)
	{T->root=NULL;
	 T->size=0;
	}
void FreeBST(BSTree *T)
	{DeleteTree(T->root);
	}
int BSTSize(BSTree *T)
	{return(T->size);
	}
int BSTEmpty(BSTree *T)
	{if(T->size==0)
		return(1);
	 else
		return(0);
	}
TNode *GetRoot(BSTree *T)
	{return(T->root);
	}
TNode *BSTLocate(BSTree *T,DataType item)
	{TNode *t;
	 t=T->root;
	 while(t!=NULL)
		{if(item==t->data)
			break;
		 else
			if(item<t->data)
				t=t->left;
			else
				t=t->right;
		}
	 return(t);
	}
void BSTInsert(BSTree *T,DataType item)
	{int d;
	 TNode *t,*p,*new,*a,*b,*f;
	 new=GetTNode(item,NULL,NULL);
	 if(T->size==0)
		{T->root=new;
		 T->size++;
		 return;
		}
	 t=T->root;p=NULL;
	 a=t;f=p;
	 while(t!=NULL)
		{if(t->balance!=0)
			{a=t;f=p;
			}
		 p=t;
		 if(item<t->data)
			t=t->left;
		 else
			t=t->right;
		}
	 if(item<p->data)
		p->left=new;
	 else
		p->right=new;
	 T->size++;
	 if(item<a->data)
		{b=t=a->left;
		}
	 else
		{b=t=a->right;
		}
	 while(t!=NULL&&t->data!=item)
		{if(item<t->data)
			{t->balance=1;
			 t=t->left;
			}
		 else
			{t->balance=-1;
			 t=t->right;
			}
		}
	 if(a->balance==0)
		{if(item<a->data)
			a->balance=1;
		 else
			a->balance=-1;
		 return;
		}
	 else
		if(item<a->data&&a->balance==-1||item>a->data&&a->balance==1)
			{a->balance=0;return;
			}
		else
			{if(a->balance==1)
				if(b->balance==1)
					LL(&a,&b);
				else
					LR(&a,&b);
			 else
				if(b->balance==-1)
					RR(&a,&b);
				else
					RL(&a,&b);
			 }
		if(f==NULL)
			T->root=b;
		else
			{if(f->left==a)
				f->left=b;
			 else
				f->right=b;
			}
		T->size++;
	}
void ClearBST(BSTree *T)
	{DeleteTree(T->root);
	 T->root=NULL;
	 T->size=0;
	}






















