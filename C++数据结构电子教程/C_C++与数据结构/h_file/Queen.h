typedef struct
	{int A[21],B[21],C[21];
	 int Y[8];
	}Queen;
void SetQueen(Queen *Q);
void PrintQueen(Queen *Q);

void SetQueen(Queen *Q)
	{int i;
	 for(i=0;i<21;i++)
		{Q->A[i]=0;
		 Q->B[i]=0;
		 Q->C[i]=0;
		}
	 for(i=0;i<8;i++)
		Q->Y[i]=-1;
	}

void PrintQueen(Queen *Q)
	{int i,x,y;
	 static total=0;
	 total++;
	 printf("%d\n",total);
	 for(y=0;y<8;y++)
		{for(x=0;x<8;x++)
			if(x!=Q->Y[y])
				printf(" # ");
			else
				printf(" o ");
		 printf("\n");
		}
	 printf("\n");
	 getch();
}