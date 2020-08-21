

/*
Read words from a text file and count the number of words.
*/

#include <stdio.h>

#define MAX_WORD_LENGTH 30

int main(int argc, char *argv[])
{
	if (argc==1)
	{
		return 0;
	}
	FILE *fp = fopen(argv[1], "r");
	//checks if file is empty	
	if (fp==NULL) 
	{
		return 0;
	}

	char temp[MAX_WORD_LENGTH];
	int c = 0;
	
	//already checks if there is a ' ' , '\n' or '\t'
	while (fscanf(fp,"%s",temp)>0) 
	{
		c++;
	}
	printf("%d total words \n", c);
	fclose(fp);
	return 1;
}

