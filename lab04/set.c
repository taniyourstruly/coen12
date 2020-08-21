#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "list.h"
#include "set.h"

int CHAINLENGTH = 20;

typedef struct set{
	int count;
	int length;
	LIST**list;
	int (*compare)();
	unsigned (*hash)();
}SET;

//O(n): O(n)
SET *createSet(int maxElts, int(*compare)(), unsigned(*hash)())
{
	//printf("create set\n");
	int i;
	SET*sp;
	assert(compare!=NULL&&hash!=NULL);
	//printf("create sp\n");
	sp=malloc(sizeof(SET));
	assert(sp!=NULL);
	//initialize length; count; compare and hash;
	sp->length=maxElts/CHAINLENGTH;
	
	//printf("length created\n");
	sp->compare=compare;
	sp->hash=hash;
	sp->count=0;
	
	sp->list=malloc(sizeof(LIST*)*sp->length);
	
	//initialize array of lists
	//for each element in the lists array create a list
	//printf("entering loop\n");
	for (i = 0; i < sp->length; i++)
	{
		sp->list[i]=createList(compare);
		//printf("looping\n");
	}
	//printf("create set done\n");
	return sp;
}

//Big O: O(n)
void destroySet(SET*sp)
{
	assert(sp!=NULL);
	int i;
	for( i = 0; i < sp->length; i++)
	{
		free(sp->list[i]);
	}		
	free(sp->list);
	free(sp);			
}

//Big O: O(1)
int numElements(SET*sp)
{
	assert(sp!=NULL);
	return sp->count;
}

//Big O: O(1)
void addElement(SET*sp, void*elt)
{
	//printf("add element\n");
	assert(sp!=NULL&&elt!=NULL);
	unsigned i = (*sp->hash)(elt);
	int j = (i)%(sp->length);
	//call addFirst or addLast from list
	addFirst(sp->list[j],elt);
	sp->count++;
	//printf("add element done\n");		
}

//Big O: O(1)
void removeElement(SET*sp, void*elt)
{
	//printf("remove element\n");
	assert(sp!=NULL);
	assert(sp!=NULL&&elt!=NULL);
	unsigned i = (*sp->hash)(elt);
	int j = (i)%(sp->length);
	//call removeItem from list
	removeItem(sp->list[j],elt);
	sp->count--;
	//printf("remove element done\n");	
}

//Big O: O(1)
void *findElement(SET*sp, void*elt)
{
	//printf("find element\n");
	assert(sp!=NULL&&elt!=NULL);
	unsigned i =(*sp->hash)(elt);
	int j = (i)%(sp->length);
	//call findItem from list
	void*data=findItem(sp->list[j],elt);
	return data;
	//printf("find element done\n");
}

//Big O: O(n)
void *getElements(SET*sp)
{
	//printf("get element\n");
	assert(sp!=NULL);
	void**copy;
	copy = malloc(sizeof(void*)*sp->count);
	void**new;
	int i, j, c;
	for(i = 0, j = 0; i < sp->length; i++)
	{
		//call numItems from list
		c=numItems(sp->list[i]);
		new=getItems(sp->list[i]);
		memcpy(copy+j,new,sizeof(void*)*c);
		j+=c;
		free(new);
	}
	//printf("get element done\n");
	return copy;
}



