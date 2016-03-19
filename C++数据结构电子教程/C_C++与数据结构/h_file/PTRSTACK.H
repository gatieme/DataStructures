typedef struct
	{PtrDataType *data;
	 int max;
	 int top;
	}Stack;
void SetStack(Stack *S,int n);
void FreeStack(Stack *S);
int StackSize(Stack *S);
int StackEmpty(Stack *S);
int StackFull(Stack *S);
PtrDataType Peek(Stack *S);
void Push(Stack *S,PtrDataType item);
PtrDataType Pop(Stack *S);
void ClearStack(Stack *S);

void SetStack(Stack *S,int n)
	{S->data=(PtrDataType *)malloc(n*sizeof(PtrDataType));
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
PtrDataType Peek(Stack *S)
	{if(S->top==-1)
		{printf("Stack is empty!\n");
		 exit(1);
		}
	 return(S->data[S->top]);
	}
void Push(Stack *S,PtrDataType item)
	{if(S->top==S->max-1)
		{printf("Stack is full!\n");
		 exit(1);
		}
	 S->top++;
	 S->data[S->top]=item;
	}
PtrDataType Pop(Stack *S)
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