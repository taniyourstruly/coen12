
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "pqueue.h"
#include "pack.h"

/*
 * creates a parent node
 * O(1)
 * */
struct node* mknode(int data, struct node* left, struct node* right)
{
	struct node* new = malloc(sizeof(struct node*));	
	assert(new!=NULL);

	new->parent=NULL;
	new->count = data;

	if(left!=NULL&&right!=NULL)
	{
		left->parent=new;
		right->parent=new;
	}
	return new;	
}

/*
 * Find the depth of the specific node with the parent node
 * O(1)
 * */
int depth(struct node* child)
{ 
	if (child->parent==NULL)
	{
		return 0;
	}
	return (depth(child->parent)+1);
}

/*
 * compares the left nodes and right nodes
 * O(1)*/
int nodecmp(struct node* left, struct node* right)
{
	if(left->count<right->count)
		return -1;
	if(left->count>right->count)
		return 1;
	return 0;	
}
/*
 * Call the functions to build the huffman tree */
int main(int argc, char*argv[])
{
	assert(argc==3); 
	int j, k, r, b, d, p, i;
	
	int counts[257];
	struct node*nodes[257];	
	
	//initializing the tree
	for(k=0; k<257;k++)
	{
		counts[k]=0;
	}

	//read from input.txt
	FILE* fp = fopen(argv[1],"r");
	
	if(fp==NULL)
	{
		printf("Error\n");
		return -1;
	}
	while((p=getc(fp)) != EOF)
	{
		counts[p]++;
	}
	fclose(fp);

	PQ *pq = createQueue(nodecmp);//createQueue

	//create leaf nodes for each char
	for (r = 0; r < 256; r++)
	{
		if(counts[r]>0)
		{
			nodes[r] = mknode(counts[r], NULL, NULL);
			addEntry(pq, nodes[r]);
		}
		else
		{
			nodes[r] = NULL;
		}
	}
	nodes[256]=mknode(0, NULL, NULL);
	addEntry(pq, nodes[256]);
	//for (k = 0; k < 257; k++)
	//{
		//addEntry(pq, nodes[k]);
	//}
	
	struct node*n1;
	struct node*n2;
	struct node*np;
	
	//add to the tree
	while(numEntries(pq)>1) //pq has more than one node
	{
		n1 = removeEntry(pq);
		n2 = removeEntry(pq);
		i = n1->count+n2->count;
		np = mknode(i, n1, n2);
		addEntry(pq, np);
	}

	//print out the number of bits
	for(j = 0; j<257; j++)
	{
		if(nodes[j]!=NULL)
		{
			d = depth(nodes[j]);
			b = counts[j]*d;
			(isprint(j)==0) ? printf("%o", j) : printf("'%c'",j);
			printf(": %d x %d bits = %d bits\n", counts[j], d, b);
		} 
	}
	pack(argv[1], argv[2], nodes);
	return 0;
}






