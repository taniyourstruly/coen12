/*
implement character pointers in an sorted array
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
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
		free(sp->data[i]);
	//deletes array
	free(sp->data);
	//deletes struct
	free(sp);
}

//returns the number of elements
//Big O: O(1)
int numElements(SET *sp)
{
	//assert(sp!=NULL);
	return (sp->count);
}

//search for a word and returns the place where the word is 
//Big O: O(logn)
static int search(SET *sp, char *elt, bool *found)
{
	assert(sp!=NULL);
	assert(elt!=NULL);
	int mid, lo=0, hi=(sp->count-1);
	*found = true;
	while (lo<=hi)
	{
		mid = (lo+hi)/2;
		int x = strcmp(sp->data[mid],elt);	
		//word is in upper half
		if (x>0)
			hi = mid-1;
		//word is in lower half
		if (x<0)
			lo = mid+1;
		//if word is in the middle
		if (x==0)
			return mid;
	}
	*found=false;
	return lo;
}

//adds a word to the array
//Big O: O(n);
void addElement(SET *sp, char *elt)
{
	assert(sp!=NULL);
	assert(elt!=NULL);
	bool found;
	//x is the index of the word
	int x = (search(sp,elt,&found));
	if (sp->len<sp->count)
		return;
	//word already in array
	if (found==true)
		return;
	for (int i = sp->count; i>x ;i--)
		sp->data[i]=sp->data[i-1];		
	//allocates memory using malloc, copies the string, and returns a pointer to the copy
	sp->data[x]=strdup(elt);
	sp->count++;
}

//deletes a word in the array
//Big O: O(n)
void removeElement(SET *sp, char *elt)
{
	assert(sp!=NULL);
	assert(elt!=NULL);
	//x is the position returned in search
	bool found;
	int x = (search(sp,elt,&found));
	//word is not in array
	if (found==false)
		return;
	if ((sp->count) == 1)
	{
		(sp->count)--;
		return;
	}
	//moved the removed to the next index
	for (int i = x; i < (sp->count)-1; i++)
		sp->data[i]=sp->data[i+1];
	(sp->count)--;
}

//find an element in the array
//Big O: O(logn)
char *findElement(SET *sp, char *elt)
{
	assert(sp!=NULL);
	assert(elt!=NULL);
	bool found;
	int x = (search(sp, elt, &found));
	//if word is found, return the word
	if (found == true)
		return sp->data[x];
	return NULL;
}

//returns the words in a new array
//Big O: O(1)
char **getElements(SET *sp)
{
	assert(sp!=NULL);
	//creates a new array of char*
	char **new;
	new = malloc(sizeof(char*)*sp->count);
	assert(new!=NULL);
	//copy from sp->data to the new array
	return memcpy(new,sp->data,sizeof(char*)*sp->count);
	
}

