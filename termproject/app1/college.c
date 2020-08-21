#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "data.h"

#define MAX 3000

int prevID = 0;

/*
 *  Function:    main
 *
 *  Description: Driver function for the test application.
 */
int main()
{
    SCHOOL*class = createDataSet(MAX);
    srand(time(NULL));
    int number = 0;
    
    while(number<1000)
    {
        int num = (rand() %2)+1;
        int age = (rand() %13)+18;
        //printf("random age: %d\n", age);
        prevID += num;
        //printf("random id: %d\n", prevID);
        insertion(class, prevID, age);
        number++;
    }
    
    maxAgeGap(class);
    
    int r = (rand() %13)+18;
    deletion(class, r);
    
    

	return 0;
}
