#include "data.h"

struct school
{
    int len;
    int count;
    STUDENT**class;
    
};

struct student
{
    int id;
    int age;
};

SCHOOL*createDataSet(int MAX)
{
    SCHOOL*sa = malloc(sizeof(SCHOOL));
    assert(sa!=NULL);
    
    sa->len = MAX;
    sa->count = 0;
    
    sa->class=malloc(sizeof(STUDENT)*MAX);
    assert(sa->class!=NULL);
    
    return sa;
    
}

void destroyDataSet(SCHOOL *sa)
{
    //printf("start destroyDataSet\n");
    assert(sa!=NULL);
    int i;
    for (i = 0; i < sa->count; i++)
    {
        free(sa->class[i]);
    }
    free(sa->class);
    free(sa);
    //printf("end destroyDataSet\n");
    return;
}

int searchAge(SCHOOL*sa, int age, bool*found)
{
    assert(sa!=NULL);
    
    int mid, lo=0, hi=(sa->count-1);
    *found=true;
    //printf("Searching for age: %d\n", age);
	//student with age will be searched
    while (lo<=hi)
    {
        mid = (lo+hi)/2;
        //int x = (searchID(sa->class[mid]->id,id));
        int x = sa->class[mid]->age;
        if (x>age)
            hi = mid-1;
        //age is in lower half
        if (x<age)
            lo = mid+1;
        //if age is in the middle
        if (x==age)
        {
            return mid;
            
        }
    }
    *found=false;
    return lo;
}

void insertion(SCHOOL *sa, int id, int age)
{
    //printf("start insertion\n");
    assert(sa!=NULL && sa->count < sa->len);
    bool found;
    int i;
    int y = (searchAge(sa, age, &found));
    //printf("what is y? %d\n", y);
    if (sa->len<sa->count)
        return;
    //printf("inserting new age\n");
    for (i = sa->count; i>y ;i--)
    {
        sa->class[i]=malloc(sizeof(STUDENT));
        sa->class[i]->age=sa->class[i-1]->age;
        sa->class[i]->id=sa->class[i-1]->id;
    }
    //printf("after inserting new age\n");
    sa->class[y]=malloc(sizeof(STUDENT));
    sa->class[y]->age=age;
    sa->class[y]->id=id;
    //printf("set new age\n");
    printf("Inserting Student ID: %d, Age: %d\n", sa->class[y]->id, sa->class[y]->age);
    (sa->count)++;
    //printf("end insertion\n");
}

void deletion(SCHOOL *sa, int age)
{
    //printf("start deletion\n");
    assert(sa!=NULL);
    //x is the position returned in search
    bool found = false;
    int i, j, y, end, c;
    y = (searchAge(sa, age, &found));
    int min = 0, max = 0;
    
    if (found)
    {
        for (min = y-1; min >= 0; min--)
        {
            if (sa->class[min]->age == age)
            {
                printf("Deleted Student ID: %d, Age: %d\n", sa->class[min]->id, sa->class[min]->age);
                free(sa->class[min]);
            }
            else
                break;
        }
        for (max = y+1; max < sa->count; max++)
        {
            if(sa->class[max]->age==age)
            {
                printf("Deleted Student ID: %d, Age: %d\n", sa->class[max]->id, sa->class[max]->age);
                free(sa->class[max]);
            }
            else
                break;
        }
        j = max - min;
        for (i = min; i < sa->count; i++)
        {
            sa->class[i] = sa->class[i+j];
        }
        sa->count=sa->count-j;
    }
    
    if (found==false)
    {
        printf("Students who are %d years old are not found\n", age);
        return;
    }
}

void maxAgeGap(SCHOOL *sa)
{
    //printf("start maxAgeGap\n");
    assert(sa!=NULL);
    int mid, lo=0, hi=(sa->count-1);
    //printf("end maxAgeGap\n");
    printf("max age gap: %d\n", ((sa->class[hi]->age)-(sa->class[lo]->age)));
    
}
