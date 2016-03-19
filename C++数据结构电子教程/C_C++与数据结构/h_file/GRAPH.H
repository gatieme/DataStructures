typedef struct
{ DataType *data;
    int *visited;
    float **edge;
    int max,size;
}Graph;
void SetGraph(Graph *G,int n);
void FreeGraph(Graph *G);
void SetVisited(Graph *G);
int GraphLocate(Graph *G,DataType item);
void GraphInsert(Graph *G,DataType item);
void EdgeInsert(Graph *G,DataType v1,DataType v2,float w);
void ClearGraph(Graph *G);

void SetGraph(Graph *G,int n)
	{int i,j;
	 G->data=(DataType*)malloc(n*sizeof(DataType));
	 G->visited=(int *)malloc(n*sizeof(int));
	 G->edge=(float **)malloc(n*sizeof(float*));
	 for(i=0;i<n;i++)
		G->edge[i]=(float *)malloc(n*sizeof(float));
	 for(i=0;i<n;i++)
		G->visited[i]=0;
	 for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			G->edge[i][j]=0;
	 G->max=n;
	 G->size=0;
	}

void FreeGraph(Graph *G)
	{int i;
	 free(G->data);
	 free(G->visited);
	 for(i=0;i<G->max;i++)
		free(G->edge[i]);
	 free(G->edge);
	}
void SetVisited(Graph *G)
	{int i;
	 for(i=0;i<G->max;i++)
		G->visited[i]=0;
	}
int GraphLocate(Graph *G,DataType item)
	{int i;
	 for(i=0;i<G->size&&item!=G->data[i];i++);
		if(i<G->size)
			return(i);
	 return(-1);
	}
void GraphInsert(Graph *G,DataType item)
	{if(G->size==G->max)
		{printf("Graph is full!\n");
		 exit(1);
		}
	 G->data[G->size]=item;
	 G->size++;
	}
void EdgeInsert(Graph *G,DataType v1,DataType v2,float w)
	{int i,j,k;
	 for(k=0;k<G->size;k++)
		{if(v1==G->data[k])
			i=k;
		 if(v2==G->data[k])
			j=k;
		}
	 G->edge[i][j]=w;
	}

void ClearGraph(Graph *G)
	{int i,j;
	 for(i=0;i<G->max;i++)
		for(j=0;j<G->max;j++)
			G->edge[i][j]=0;
	 for(i=0;i<G->max;i++)
		G->visited[i]=0;
	 G->size=0;
	}