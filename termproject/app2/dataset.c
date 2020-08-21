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
    
    sa->class=malloc(sizeof(STUDENT*)*MAX);
    assert(sa->class!=NULL);
    
    return sa;
}

void destroyDataSet(SCHOOL *sa)
{
    assert(sa!=NULL);
    int i;
    for (i = 0; i < sa->count; i++)
    {
        free(sa->class[i]);
    }
    free(sa);
    return;
}

int searchID(SCHOOL*sa, int id, bool*found)
{
    assert(sa!=NULL);
    
    int mid, lo=0, hi=(sa->count-1);
    *found=true;
    while (lo<=hi)
    {
        mid = (lo+hi)/2;
        //id is in upper half
        int x = sa->class[mid]->id;
        if (x>id)
            hi = mid-1;
        //id is in lower half
        if (x<id)
            lo = mid+1;
        //if id is in the middle
        if (x==id)
        {
            return mid;
            
        }
    }
    *found=false;
    return lo;
}

void insertion(SCHOOL *sa, int id, int age)
{
    assert(sa!=NULL && sa->count < sa->len);
    bool found;
    int i;
    //y is the position returned in search
    int y = (searchID(sa, id, &found));
    if (sa->len<sa->count)
        return;
    for (int i = sa->count; i>y ;i--)
    {
        sa->class[i]->age=sa->class[i-1]->age;
        sa->class[i]->id=sa->class[i-1]->id;
    }
    //insert student
    sa->class[y]=malloc(sizeof(int));
    sa->class[y]->age=age;
    sa->class[y]->id=id;
    printf("Student ID: %d, Age: %d\n", sa->class[y]->id, sa->class[y]->age); //print out each student when you add them
    (sa->count)++;
}


void deletion(SCHOOL *sa, int id)
{
    assert(sa!=NULL);
    //y is the position returned in search
    bool found;
    int y = (searchID(sa, id, &found));
    
    printf("Deleted Student ID: %d, Age: %d\n", sa->class[y]->id, sa->class[y]->age);
    
    if (found)
    {
        printf("Student found!\n");
        //moved the removed to the next index
        for (int j = y; j < (sa->count)-1; j++)
            sa->class[j]->id=sa->class[j+1]->id;
        (sa->count)--;
        printf("ID deleted.\n");
    }
    if (found == false)
    {
        printf("Student could not be found!\n");
        return;
    }
    //if only one student
    if ((sa->count) == 1)
    {
        (sa->count)--;
        return;
    }
    
    
    
    
}



