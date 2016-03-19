typedef struct
	{char *str;
	 int size;
	}String;
void SetString(String *S);
int StrSize(String *S);
int StrEmpty(String *S);
char StrGetData(String *S,int pos);
int StrCompare(String *S,String *T);
char *Trans(String *S);
void StrAssign(String *S,char *cs);
void StrConcat(String *S,String *S1,String *S2);
void SubString(String *T,String *S,int pos,int count);
void StrInsert(String *S,char *cs,int pos);
void StrInsert1(String *S,String *CS,int pos);
void StrDelete(String *S,int pos,int count);
void FreeString(String *S);
void ClearString(String *S);

void SetString(String *S)
	{S->str=(char *)malloc(sizeof(char));
	 if(S->str==NULL)
		{printf("overflow");
		 exit(1);
		}
	 *(S->str)='\0';
	 S->size=0;
	}
int StrSize(String *S)
	{return(S->size);
	}
int StrEmpty(String *S)
	{if(S->size==0)
		return(1);
	 return(0);
	}
char StrGetData(String *S,int pos)
	{if(pos<0||pos>S->size-1)
		{printf("pos in StrGetData is illegal!");
		 exit(1);
		}
	 return(S->str[pos]);
	}
int StrCompare(String *S,String *T)
	{return(strcmp(S->str,T->str));
	}
char *Trans(String *S)
	{return(S->str);
	}
void StrAssign(String *S,char *cs)
	{int n;
	 free(S->str);
	 n=strlen(cs)+1;
	 S->str=(char *)malloc(n*sizeof(char));
	 if(S->str==NULL)
		{printf("overflow");
		 exit(1);
		}
	 strcpy(S->str,cs);
	 S->size=n-1;
	}
void StrConcat(String *S,String *S1,String *S2)
	{int n;
	 free(S->str);
	 n=S1->size+S2->size+1;
	 S->str=(char *)malloc(n*sizeof(char));
	 if(S->str==NULL)
		{printf("overflow");
		 exit(1);
		}
	 strcpy(S->str,S1->str);
	 strcat(S->str,S2->str);
	 S->size=n-1;
	}
void SubString(String *T,String *S,int pos,int count)
	{int i,charsleft;
	 char *p,*q;
	 if(pos<0||pos>S->size-1)
		{printf("Pos in SubString is illegal!\n");
		 exit(1);
		}
	 if(count<0)
		{printf("Count in SubString is illegal!\n");
		 exit(1);
		}
	 free(T->str);
	 charsleft=S->size-pos;
	 if(count>charsleft)
	 count=charsleft;
	 T->str=(char *)malloc((count+1)*sizeof(char));
	 if(T->str==NULL)
		{printf("overflow");
		 exit(1);
		}
	 p=T->str;
	 q=S->str+pos;
	 for(i=1;i<=count;i++)
		*p++=*q++;
	 *p='\0';
	 T->size=count;
	}
void StrInsert(String *S,char *cs,int pos)
	{int n,i,charsleft;
	 char *temp,*p,*q;
	 if(pos<0||pos>S->size)
		{printf("Pos in StrInsert is illegal!\n");
		 exit(1);
		}
	 n=S->size+1;
	 temp=(char *)malloc(n*sizeof(char));
	 if(temp==NULL)
		{printf("overflow");
		 exit(1);
		}
strcpy(temp,S->str);
       free(S->str);
			 n=strlen(temp)+strlen(cs)+1;
       S->str=(char *)malloc(n*sizeof(char));
       if(S->str==NULL)
				{ printf("overflow");
					exit(1);
				}
       strcpy(S->str,temp);
       p=S->str+strlen(temp);
			 q=S->str+n-1;
       charsleft=strlen(temp)-pos+1;
       for(i=1;i<=charsleft;i++)
				*q--=*p--;
       p=S->str+pos;
       q=cs;
       while(*q!='\0')
				*p++=*q++;
       S->size=n-1;
       free(temp);
    }

   void StrInsert1(String *S,String *CS,int pos)
     { int n,i,charsleft;
       char *temp,*p,*q;
       if(pos<0||pos>S->size)
				{ printf("Pos in StrInsert is illegal!\n");
					exit(1);
				}
       n=S->size+1;
       temp=(char *)malloc(n*sizeof(char));
       if(temp==NULL)
				{ printf("overflow");
					exit(1);
				}
       strcpy(temp,S->str);
       free(S->str);
       n=S->size+CS->size+1;
       S->str=(char *)malloc(n*sizeof(char));
       if(S->str==NULL)
				{ printf("overflow");
					exit(1);
				}
       strcpy(S->str,temp);
       p=S->str+strlen(temp);
			 q=S->str+n-1;
       charsleft=strlen(temp)-pos+1;
       for(i=1;i<=charsleft;i++)
				*q--=*p--;
       p=S->str+pos;
       q=CS->str;
       while(*q!='\0')
				 *p++=*q++;
       S->size=n-1;
       free(temp);
    }

   void StrDelete(String *S,int pos,int count)
     { int i,n,charsleft;
       char *temp,*p,*q;
       if(pos<0||pos>S->size-1)
				{ printf("Pos in StrDelete is illegal!\n");
					exit(1);
				}
       if(count<0)
				{ printf("Count in StrDelete is illegal!\n");
					exit(1);
				}
       if(count==0)
				 return;
       n=S->size+1;
       temp=(char *)malloc(n*sizeof(char));
       if(temp==NULL)
				{ printf("overflow");
					exit(1);
				}
       strcpy(temp,S->str);
       if(count>=strlen(temp)-pos)
				 temp[pos]='\0';
       else
				{ p=temp+pos;
					q=temp+pos+count;
					while(*q!='\0')
						*p++=*q++;
					*p='\0';
				}
       free(S->str);
       n=strlen(temp)+1;
       S->str=(char *)malloc(n*sizeof(char));
       if(S->str==NULL)
				{ printf("overflow");
					exit(1);
				}
       strcpy(S->str,temp);
       S->size=n-1;
       free(temp);
     }

   void ClearString(String *S)
     { free(S->str);
       S->str=(char *)malloc(sizeof(char));
       if(S->str==NULL)
				{ printf("overflow");
					exit(1);
				}
			 *(S->str)='\0';
       S->size=0;
     }

   void FreeString(String *S)
     { free(S->str);
     }