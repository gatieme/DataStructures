void MakeGraph(Graph *G)
	{float w;
	 char v1,v2,blank;
	 printf("\n Please input Graph_node:\n");
	 v1=getchar();
	 while(v1!='\n')
		{GraphInsert(G,v1);
		 v1=getchar();
		}
	 printf("Please input Graph_edge:\n");
	 scanf("%c%c%f%c",&v1,&v2,&w,&blank);
	 while(blank!='\n')
		{EdgeInsert(G,v1,v2,w);
		scanf("%c%c%f%c",&v1,&v2,&w,&blank);
		}
    EdgeInsert(G,v1,v2,w);
	}
void PrintGraph(Graph *G)
	{int i,j,n;
	 n=G->size;
	 for(i=0;i<n;i++)
		printf("%5c:",G->data[i]);
	 printf("\n");
	 for(i=0;i<n;i++)
		{for(j=0;j<n;j++)
		  printf("%6.1f",G->edge[i][j]);
		 printf("\n");
		}
	}


