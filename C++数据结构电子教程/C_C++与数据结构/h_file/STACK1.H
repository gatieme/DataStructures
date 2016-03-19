typedef struct
	{DataType1 *data;
	 int max;
	 int top;
	}Stack1;
void SetStack1(Stack1 *S,int n);
void FreeStack1(Stack1 *S);
int StackSize1(Stack1 *S);
int StackEmpty1(Stack1 *S);
int StackFull1(Stack1 *S);
DataType1 Peek1(Stack1 *S);
void Push1(Stack1 *S,DataType1 item);
DataType1 Pop1(Stack1 *S);
void ClearStack1(Stack1 *S);

void SetStack1(Stack1 *S,int n)
	{S->data=(DataType1 *)malloc(n*sizeof(DataType1));
	 if(S->data==NULL)
		{printf("overflow");
		 exit(1);
		}
	 S->max=n;
	 S->top=-1;
	}
void FreeStack1(Stack1 *S)
	{free(S->data);
	}
int StackSize1(Stack1 *S)
	{return(S->top+1);
	}
int StackEmpty1(Stack1 *S)
	{if(S->top==-1)
		return(1);
	 return(0);
	}
int StackFull1(Stack1 *S)
	{if(S->top==S->max-1)
		return(1);
	 return(0);
	}
DataType1 Peek1(Stack1 *S)
	{if(S->top==-1)
		{printf("Stack is empty!\n");
		 exit(1);
		}
	 return(S->data[S->top]);
	}
void Push1(Stack1 *S,DataType1 item)
	{if(S->top==S->max-1)
		{printf("Stack is full!\n");
		 exit(1);
		}
	 S->top++;
	 S->data[S->top]=item;
	}
DataType1 Pop1(Stack1 *S)
	{if(S->top==-1)
		{printf("Pop an empty stack!\n");
		 exit(1);
		}
	 S->top--;
	 return(S->data[S->top+1]);
	}
void ClearStack1(Stack1 *S)
	{S->top=-1;
	}
