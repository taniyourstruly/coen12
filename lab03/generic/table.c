

/*
implement void pointers in an unsorted array
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
	void**data;
	int len;
	int count;
	char *flags;
	int (*compare)();
	unsigned(*hash)(); //function pointers provided by outsider program
} SET;


//creates the SET
//Big O: O(n)
SET *createSet(int maxElts, int(*compare)(), unsigned(*hash)())
{
	//(*sp->compare(...where the arguments go...)
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count=0;
	sp->len=maxElts;
	sp->data=malloc(sizeof(void*)*maxElts);
	assert(sp->data!=NULL);
	
	sp->flags = malloc(sizeof(void*)*maxElts);
	assert(sp->flags!=NULL);

	sp->hash=hash;
	sp->compare=compare;

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
		if (sp->flags[i] == FILLED&&sp->flags[i]==DELETED)
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
//Big O: O(n)
static int search(SET *sp, void *elt, bool *found)
{
	assert(sp!=NULL);
	assert(elt!=NULL);
	*found=false;
	int deleted=-1;
	int index = 0;
	unsigned j = (*sp->hash)(elt);
	//printf("entering for loop\n");	
	for(int i = 0; i < sp->len; i++)
	{
		int k = (j+i)%(sp->len);
		//printf("entering filled\n");	
		if (sp->flags[k]==FILLED)
		{
			if(((*sp->compare)(elt,sp->data[k]))==0)
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
void addElement(SET *sp, void *elt)
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
	sp->data[x]=elt;
	(sp->count)++;
	(sp->flags[x])=FILLED;
	return;	
		
}

//deletes a word in the array
//Big O: O(n)
void removeElement(SET *sp, void *elt)
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
	//free(sp->data[x]);
	sp->flags[x]=DELETED;
	(sp->count)--;
	//printf("exiting remove, %d \n",sp->count);
}

//find an element in the array
//Big O: O(n)
void * findElement(SET *sp, void *elt)
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
void* getElements(SET *sp)
{
	assert(sp!=NULL);
	void **new;
	new = malloc(sizeof(void*)*sp->count);
	assert(new!=NULL);
	int j=0;
	for (int i = 0; i<sp->len;i++)
	{
		if(sp->flags[i]==FILLED)
		{
			new[j++]=sp->data[i];
		}
	}
	return new;	
}


