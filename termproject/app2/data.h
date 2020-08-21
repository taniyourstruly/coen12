//
//  data2.h
//
//
//  Created by Tania Pham on 3/12/19.
//

#ifndef data_h
#define data_h

#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct student STUDENT;
typedef struct school SCHOOL;

SCHOOL*createDataSet(int max);
void destroyDataSet(SCHOOL*sa);
int searchAge(SCHOOL*sa, int age, bool*found);
void insertion(SCHOOL*sa, int id, int age);
void deletion(SCHOOL*sa, int age);
int maxAgeGap(SCHOOL*sa);

#endif /* data_h */
