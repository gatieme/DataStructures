typedef struct
	{TNode *root;
	 int size;
	}BSTree;
void DeleteTree(TNode *t);
void SetBST(BSTree *T);
void FreeBST(BSTree *T);
int BSTSize(BSTree *T);
int BSTEmpty(BSTree *T);
TNode *GetRoot(BSTree *T);
TNode *BSTLocate(BSTree *T,DataType item);
void BSTInsert(BSTree *T,DataType item);
void BSTDelete(BSTree *T,DataType item);
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
	{TNode *t,*p,*new;
	 new=GetTNode(item,NULL,NULL);
	 if(T->size==0)
		{T->root=new;
		 T->size++;
		 return;
		}
	 t=T->root;
	 p=NULL;
	 while(t!=NULL)
		{p=t;
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
	}
void BSTDelete(BSTree *T,DataType item)
	{TNode *t,*p,*r,*pr;
	 t=T->root;
	 p=NULL;
	 while(t!=NULL)
		{if(item==t->data)
			break;
		 else
			{p=t;
			 if(item<t->data)
				t=t->left;
			 else
				t=t->right;
			}
		 }
	 if(t==NULL)
		return;
	 if(t->left==NULL)
		{if(p==NULL)
			T->root=t->right;
		 else if(p->left==t)
			p->left=t->right;
		 else
			p->right=t->right;
		 free(t);
		}
	 else
		{pr=t;
		 r=t->left;
		 while(r->right!=NULL)
			{pr=r;
			 r=r->right;
			}
		 t->data=r->data;
		 if(pr==t)
			pr->left=r->left;
		 else
			pr->right=r->left;
		 free(r);
		}
	 T->size--;
	}
void ClearBSTree(BSTree *T)
	{DeleteTree(T->root);
	 T->root=NULL;
	 T->size=0;
	}
