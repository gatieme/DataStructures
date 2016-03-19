typedef struct
	{TNode *ptr;
	 int xindent;
	 int ylevel;
	}PDataType;
#include"printq.h"
void PrintTree(TNode *root,int screenwidth)
	{int level=1,ofset=screenwidth/2;
	 PDataType p,c;
	 PQueue Q;
	 SetPQueue(&Q,50);
	 if(root==NULL)
		return;
	 p.ptr=root;
	 p.ylevel=level;
	 p.xindent=ofset;
	 PQInsert(&Q,p);
	 while(!PQEmpty(&Q))
		{p=PQDelete(&Q);
		 gotoxy(p.xindent,p.ylevel);
		 printf("%c",p.ptr->data);
		 if(p.ylevel!=level)
			{level++;
			 ofset=ofset/2;
			}
		if(p.ptr->left!=NULL)
			{c.ptr=p.ptr->left;
			c.ylevel=p.ylevel+1;
			 c.xindent=p.xindent-ofset/2;
			 PQInsert(&Q,c);
			}
		if(p.ptr->right!=NULL)
			{c.ptr=p.ptr->right;
			 c.ylevel=p.ylevel+1;
			 c.xindent=p.xindent+ofset/2;
			 PQInsert(&Q,c);
			}
		}
	 FreePQueue(&Q);
	}
void PrintTree1(TNode *root,int screenwidth) /* exercise */
	{int level=1,ofset=screenwidth/2;
	 PDataType p,c;
	 PQueue Q;
	 SetPQueue(&Q,50);
	 if(root==NULL)
		return;
	 p.ptr=root;
	 p.ylevel=level;
	 p.xindent=ofset;
	 gotoxy(p.xindent,p.ylevel);
	 printf("%c",p.ptr->data);
	 PQInsert(&Q,p);
	 while(!PQEmpty(&Q))
		{p=PQDelete(&Q);
		 if(p.ylevel!=level)
			{level++;
			 ofset=ofset/2;
			 }
		 if(p.ptr->left!=NULL)
			{c.ptr=p.ptr->left;
			 c.ylevel=p.ylevel+1;
			 c.xindent=p.xindent-ofset/2;
			 gotoxy(c.xindent,c.ylevel);
			 printf("%c",c.ptr->data);
			 PQInsert(&Q,c);
			}
		 if(p.ptr->right!=NULL)
			{c.ptr=p.ptr->right;
			 c.ylevel=p.ylevel+1;
			 c.xindent=p.xindent+ofset/2;
			 gotoxy(c.xindent,c.ylevel);
			 printf("%c",c.ptr->data);
			 PQInsert(&Q,c);
			}
		}
	 FreePQueue(&Q);
	}