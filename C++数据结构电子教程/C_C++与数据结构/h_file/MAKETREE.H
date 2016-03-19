TNode *MakeLBTree(SeqList *L)
	{int i,n=ListSize(L);
	 TNode *root,*ptr,*c;
	 Queue Q;
	 SetQueue(&Q,50);
	 if(ListEmpty(L))
		return(NULL);
	 root=(TNode*)malloc(sizeof(TNode));
	 SetTNode(root,GetData(L,0));
	 QInsert(&Q,root);
	 i=0;
	 while(!QEmpty(&Q))
		{ptr=QDelete(&Q);
		 if(2*i+1<n&&GetData(L,2*i+1)!='@')
			{c=GetTNode(GetData(L,2*i+1),NULL,NULL);
			 ptr->left=c;
			 QInsert(&Q,c);
			}
		 if(2*i+2<n&&GetData(L,2*i+2)!='@')
			{c=GetTNode(GetData(L,2*i+2),NULL,NULL);
			 ptr->right=c;
			 QInsert(&Q,c);
			}
		 i++;
		 while(i<n&&GetData(L,i)=='@')
			i++;
		}
	 FreeQueue(&Q);
	 return(root);
	}