/*
implement character pointers in an unsorted array
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"

//create a struct
typedef struct set
{
	char**data;
	int len;
	int count;
} SET;

//creates the SET
//Big O: O(1)
SET *createSet(int maxElts)
{
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count=0;
	sp->len=maxElts;
	sp->data=malloc(sizeof(char*)*maxElts);
	assert(sp->data!=NULL);
	return sp;
}

//deletes all the information in the SET
//Big O: O(n)
void destroySet(SET *sp)
{
	assert(sp!=NULL);
	for (int i = 0; i < sp->count; i++)
	{
		free(sp->data[i]);
	}
	//deletes array
	free(sp->data);
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
static int search(SET *sp, char *elt)
{
	assert(sp!=NULL);
	assert(elt!=NULL);
	for (int i = 0; i<sp->count; i++)
	{
		if (strcmp(elt, sp->data[i])==0)
		{
			return i;
		}
	}
	return -1;
}

//adds a word to the array
//Big O: O(n);
void addElement(SET *sp, char *elt)
{
	assert(sp!=NULL);
	assert(elt!=NULL);
	if (sp->len<sp->count)
	{
		return;
	}
	//word already in array
	if (search(sp, elt)!=-1)
	{
		return;
	}
	//allocates memory using malloc, copies the string, and returns a pointer to the copy
	sp->data[sp->count]=strdup(elt);	
	sp->count++;
}

//deletes a word in the array
//Big O: O(n)
void removeElement(SET *sp, char *elt)
{
	//printf("entering remove\n");
	assert(sp!=NULL);
	assert(elt!=NULL);
	//x is the position returned in search
	int x = (search(sp,elt));
	if (x==-1)
	{
		return;
	}
	if ((sp->count) == 1)
	{
		(sp->count)--;
		return;
	}
	//move the end to the removed index
	sp->data[x] = sp->data[sp->count-1];
	(sp->count)--;
	//printf("exiting remove, %d \n",sp->count);
}

//find an element in the array
//Big O: O(n)
char *findElement(SET *sp, char *elt)
{
	assert(sp!=NULL);
	assert(elt!=NULL);
	int x = (search(sp, elt));
	if (x!=-1)
	{
		return sp->data[x];
	}
	return NULL;
}

//returns the words in the array
//Big O: O(1)
char **getElements(SET *sp)
{
	assert(sp!=NULL);
	char **new;
	new = malloc(sizeof(char*)*sp->count);
	assert(new!=NULL);
	return memcpy(new,sp->data,sizeof(char*)*sp->count);
	
}


