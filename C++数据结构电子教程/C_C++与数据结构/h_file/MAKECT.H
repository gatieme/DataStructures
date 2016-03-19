void MakeCT(CTree *T)
	{int i;
	 char p,c,blank;
	 printf("\n Please inpute CTNode_data:\n");
	 p=getchar();
	 while(p!='\n')
		{CTInsert(T,p);
		 p=getchar();
		}

	 printf("Please inpute parent_child_data:\n");
	 p=getchar();
	 c=getchar();
	 blank=getchar();
	 while(blank!='\n')
		{PCInsert(T,p,c);
		 p=getchar();
		 c=getchar();
		 blank=getchar();
		}
	 PCInsert(T,p,c);
	 printf("Please inpute root_data:\n");
	 p=getchar();
	 i=CTLocate(T,p);
	 T->root=i;
	}
void PrintCT(CTree *T)
	{int i,n;
	 CNode *ptr;
	 n=T->size;
	 for(i=0;i<n;i++)
		{printf("%c:",T->a[i].data);
		 ptr=T->a[i].front;
		 while(ptr!=NULL)
			{printf("%2d ",ptr->child);
			 ptr=ptr->next;
			}
		 printf("\n");
		}
	}
