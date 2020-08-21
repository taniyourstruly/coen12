#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "pqueue.h"

#define L(x) 2*x + 1
#define P(x) (x-1)/2
#define R(x) 2*x + 2 

typedef struct pqueue{
	int count;
	int length;
	void **data;
	int (*compare)();
}PQ;

/*creates the priority queue
 * Big O: O(1)
 */

PQ *createQueue(int(*compare)())
{
	PQ*pq;
	pq=malloc(sizeof(PQ));
	assert(pq!=NULL);
	
	pq->length=10;
	pq->compare = compare;
	pq->count=0;

	pq->data=malloc(sizeof(void*)*pq->length);
	assert(pq->data != NULL);

	return (pq);
}
/*Destroy the priority
 * Big O: O(n)
 */
void destroyQueue(PQ *pq)
{
	assert(pq!=NULL);

	int i;
	for (i = 0; i <pq->count; i++)
		free(pq->data[i]);

	free(pq->data);
	free(pq);
}

/* Count the number of entries
 * O(1)
 * */
int numEntries(PQ*pq)
{
	assert(pq!=NULL);
	return pq->count;
}

/* Add entry to the priority queue
 * O(logn)
 * */
void addEntry(PQ *pq, void *entry)
{
	assert(pq!=NULL||entry!=NULL);
	//if priority queue is full, allocate
	
	if(pq->count==pq->length)
	{
		pq->data=realloc(pq->data, sizeof(void*)*(2*(pq->length)));
		assert(pq!=NULL);

		pq->length=2*pq->length;
	}	

	//place new element at the end of binary heap
	pq->data[pq->count] = entry;
	int i = pq->count;
	
	pq->count++;
	
	void*temp;

	while(P(i)>=0){

		if ((*pq->compare)(pq->data[P(i)],pq->data[i])==1)
		{	
			temp = pq->data[P(i)];
			pq->data[P(i)]=pq->data[i];
			pq->data[i] = temp;
			i = P(i);
		}
		else
			break;
	}
} 

/*
 * Remove smallest entry from the priority queue
 * O(logn) */
void *removeEntry(PQ *pq)
{
	assert(pq!=NULL);
	if(pq->count==0)
		return NULL;
	if(pq->count==1)
	{
		pq->count--;
		return pq->data[0];
	}
	void*first=pq->data[0];
	pq->data[0] = pq->data[pq->count-1];
	int i=0;
	
	while(L(i) < pq->count)
	{
		
		if(L(i)>=pq->count)
			break;
		
        	if(R(i) < pq->count){
            
           		if((*pq->compare)(pq->data[L(i)] , pq->data[R(i)]) == 1){
                
                		if((*pq->compare)(pq->data[R(i)], pq->data[i]) == -1){
                   		//swap right with parent
                    
                   			void *temp = pq->data[i];
					pq->data[i] = pq->data[R(i)];
                    			pq->data[R(i)] = temp;
                    
                    			i = R(i);
                    
                		}
                		else
                    			break;
            		}
            
            		else if((*pq->compare)(pq->data[L(i)] , pq->data[i]) == - 1){
                		
				void *temp = pq->data[i];
                		pq->data[i] = pq->data[L(i)];
                		pq->data[L(i)] = temp;
                
               			i = L(i);
            		}
            		else
                		break;
        	}
        
        
        	else if((*pq->compare)(pq->data[L(i)] , pq->data[i]) == - 1){
            	
			void *temp = pq->data[i];
            		pq->data[i] = pq->data[L(i)];
            		pq->data[L(i)] = temp;
            
            		i = L(i);
        	}
        	else
            		break;
    }
	pq->count--;
	return first;
}
