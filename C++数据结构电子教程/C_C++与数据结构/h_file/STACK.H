typedef struct
	{DataType *data;
	 int max;
	 int top;
	}Stack;
void SetStack(Stack *S,int n);
void FreeStack(Stack *S);
int StackSize(Stack *S);
int StackEmpty(Stack *S);
int StackFull(Stack *S);
DataType Peek(Stack *S);
void Push(Stack *S,DataType item);
DataType Pop(Stack *S);
void ClearStack(Stack *S);

void SetStack(Stack *S,int n)
	{S->data=(DataType *)malloc(n*sizeof(DataType));
	 if(S->data==NULL)
		{printf("overflow");
		 exit(1);
		}
	 S->max=n;
	 S->top=-1;
	}
void FreeStack(Stack *S)
	{free(S->data);
	}
int StackSize(Stack *S)
	{return(S->top+1);
	}
int StackEmpty(Stack *S)
	{if(S->top==-1)
		return(1);
	 return(0);
	}
int StackFull(Stack *S)
	{if(S->top==S->max-1)
		return(1);
	 return(0);
	}
DataType Peek(Stack *S)
	{if(S->top==-1)
		{printf("Stack is empty!\n");
		 exit(1);
		}
	 return(S->data[S->top]);
	}
void Push(Stack *S,DataType item)
	{if(S->top==S->max-1)
		{printf("Stack is full!\n");
		 exit(1);
		}
	 S->top++;
	 S->data[S->top]=item;
	}
DataType Pop(Stack *S)
	{if(S->top==-1)
		{printf("Pop an empty stack!\n");
		 exit(1);
		}
	 S->top--;
	 return(S->data[S->top+1]);
	}
void ClearStack(Stack *S)
	{S->top=-1;
	}
