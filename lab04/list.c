


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

typedef struct node{
	void *data;
	struct node*next;
	struct node*prev;
}NODE;

typedef struct list{
	int count;
	struct node*head;
	int (*compare)();
}LIST;

//big O: O(1)
LIST *createList(int (*compare)())
{
	LIST *lp = malloc(sizeof(LIST));
	assert(lp!=NULL);
	lp->count = 0;
	lp->compare = compare;
	lp->head=malloc(sizeof(NODE));
	assert(lp->head!=NULL);
	lp->head->next=lp->head; //head points to itself
	lp->head->prev=lp->head; 
	return lp;
}

//big O: O(n)
void destroyList(LIST *lp)
{
	NODE *pDel, *pNext;
	assert(lp!=NULL);
	pDel=lp->head;
	do{
		pNext=pDel->next;
		free(pDel);
		pDel=pNext;
	} while (pDel!=lp->head);
	free(lp);
}

//big O: O(1)
int numItems(LIST *lp)
{
	assert(lp!=NULL);
	return (lp->count);
}

//big O: O(1)
void addFirst(LIST *lp, void *item)
{
	assert(lp!=NULL);


	//create new node
	NODE *new = malloc(sizeof(NODE));
	assert(new!=NULL);
	new->data=item;
	
	//inserting new Node
	new->next=lp->head->next;
	new->prev=lp->head;
	lp->head->next->prev=new;
	lp->head->next=new;
	
	lp->count++;
}

//big O: O(1)
void addLast(LIST *lp, void *item)
{

	assert(lp!=NULL);
	
	//create new node
	NODE *new = malloc(sizeof(NODE));
	assert(new!=NULL);
	new->data=item;
	
	//inserting new Node
	new->prev=lp->head->prev;
	new->next=lp->head;
	lp->head->prev->next=new;
	lp->head->prev=new;

	lp->count++;
}

//big O: O(1)
void *removeFirst(LIST *lp)
{
	assert(lp!=NULL);
	
	//set node to be deleted
	NODE *pDel=lp->head->next;
	void*data = pDel->data;
	
	lp->head->next = pDel->next;
	lp->head->next->prev=lp->head;
	
	//free node, subtract count, and return item in the list
	free(pDel);
	lp->count--;
	return data;

}

//big O: O(1)
void *removeLast(LIST *lp)
{
	assert(lp!=NULL);

	//set node to be deleted
	NODE *pDel=lp->head->prev;
	void*data = pDel->data;
	
	lp->head->prev=pDel->prev;
	lp->head->prev->next = lp->head;
	
	free(pDel);
	lp->count--;
	return data;
}

//big O: O(1)
void *getFirst(LIST *lp)
{
	assert(lp!=NULL);
	return (lp->head->next->data);
}

//big O: O(1)
void *getLast(LIST *lp)
{
	assert(lp!=NULL);
	return (lp->head->prev->data);
}

//big O: O(n)
void removeItem(LIST *lp, void *item)
{
	assert(lp!=NULL);
	NODE *pPrev=lp->head->next; 
	bool found;
	while(pPrev!=lp->head)
	{
		if((*lp->compare)(item,pPrev->data)==0)
		{
			found = true;
			break;
		}
	pPrev=pPrev->next;
	}
	//pPrev=pPrev->next;
	if (found==false)
		return;
	pPrev->next->prev=pPrev->prev;
	pPrev->prev->next=pPrev->next;
	free(pPrev);
	lp->count--;
	return;
}

//big O: O(n)
void *findItem(LIST *lp, void *item)
{
	assert(lp!=NULL);
	NODE *pPrev=lp->head->next;
	while(pPrev!=lp->head)
	{
		if((*lp->compare)(item,pPrev->data)==0)
		{
			return pPrev->data;
		}
	pPrev=pPrev->next;
	}
	return NULL;
}

//big O: O(n)
void *getItems(LIST *lp)
{
	assert(lp!=NULL);
	void **New=malloc(sizeof(void*)*lp->count);
	assert(New!=NULL);
	int j=0;
	NODE *pPrev=lp->head->next;
	while(pPrev!=lp->head) {
		New[j++]=pPrev->data;
		pPrev=pPrev->next;
	}
	return New;	
	
}
