
/*
implement character pointers in an unsorted array
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
#define EMPTY 0
#define FILLED 1
#define DELETED 2


//create a struct
typedef struct set
{
	char**data;
	int len;
	int count;
	int *flags;
} SET;

//given hash function
//Big O: O(n)
unsigned strhash(char*s)
{
	unsigned hash = 0;
	while(*s != '\0')
		hash = 31 * hash + *s++;
	return hash;
}

//creates the SET
//Big O: O(n)
SET *createSet(int maxElts)
{
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count=0;
	sp->len=maxElts;
	sp->data=malloc(sizeof(char*)*maxElts);
	assert(sp->data!=NULL);
	
	sp->flags = malloc(sizeof(int*)*maxElts);
	assert(sp->flags!=NULL);

	for (int i = 0; i < sp->len; i++)
	{
		sp->flags[i]=EMPTY;
	}

	return sp;
}

//deletes all the information in the SET
//Big O: O(n)
void destroySet(SET *sp)
{
	assert(sp!=NULL);
	for (int i = 0; i < sp->count; i++)
	{
		if (sp->flags[i] == FILLED)
			free(sp->data[i]);
	}
	//deletes array
	free(sp->data);
	free(sp->flags);
	//deletes struct
	free(sp);
}

//returns the number of elements
//Big O: O(1)
int numElements(SET *sp)
{
	assert(sp!=NULL);
	return sp->count;
}

//search for a word and returns the position it is 
//Big O: O(n^2)
static int search(SET *sp, char *elt, bool *found)
{
	assert(sp!=NULL);
	assert(elt!=NULL);
	*found=false;
	int deleted=-1;
	int index = 0;
	unsigned j = strhash(elt);
	//printf("entering for loop\n");	
	for(int i = 0; i < sp->len; i++)
	{
		int k = (j+i)%(sp->len);
		//printf("entering filled\n");	
		if (sp->flags[k]==FILLED)
		{
			if(strcmp(elt,sp->data[k])==0)
			{
				*found=true;
				return k;
			}	
		}
		//printf("entering deleted\n");		
		else if (sp->flags[k]==DELETED)
		{
			if(deleted==-1)
			{
				index=k;
				deleted=0;
			}			
		}
		//printf("entering empty\n");
		else //flags is EMPTY
		{
			*found=false;
			if(deleted==0)
			{
				return index;
			}		 
			return k;
		}
	}	
	*found=false;
	return -1;
}

//adds a word to the array
//Big O: O(n);
void addElement(SET *sp, char *elt)
{
	//printf("entering add\n");
	assert(sp!=NULL);
	assert(elt!=NULL);
	if (sp->len<sp->count)
	{
		return;
	}
	bool found;
	int x = (search(sp,elt,&found));	
	if (found==true)
	{
		return;
	}
	if (x == -1)
	{
		return;
	}

	//printf("adding\n");
	sp->data[x]=strdup(elt);
	(sp->count)++;
	(sp->flags[x])=FILLED;
	return;	
		
}

//deletes a word in the array
//Big O: O(n)
void removeElement(SET *sp, char *elt)
{
	//printf("entering remove\n");
	assert(sp!=NULL);
	assert(elt!=NULL);
	//x is the position returned in search
	bool found;	
	int x = (search(sp,elt,&found));
	if (found==false)
	{
		return;
	}
	free(sp->data[x]);
	sp->flags[x]=DELETED;
	(sp->count)--;
	//printf("exiting remove, %d \n",sp->count);
}

//find an element in the array
//Big O: O(n)
char *findElement(SET *sp, char *elt)
{
	assert(sp!=NULL);
	assert(elt!=NULL);
	bool found;
	int x = (search(sp, elt,&found));
	if (found==true)
	{
		return sp->data[x];
	}
	return NULL;
}

//returns the words in the array
//Big O: O(n)
char **getElements(SET *sp)
{
	assert(sp!=NULL);
	char **new;
	new = malloc(sizeof(char*)*sp->count);
	assert(new!=NULL);
	int j=0;
	for (int i = 0; i<sp->len;i++)
	{
		new[j++]=sp->data[i];
	}
	return new;	
}


