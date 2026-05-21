#ifndef __DATABASE_H
#define __DATABASE_H

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>


typedef struct Person {
    int age_seasons;
    char* name;
    int numInterests;
    char** interests;
    int merp_score;
} Person;


Person* personConstructor(int age_s, char* nam, int num_inter, char** interest, int merp);
void printPerson(Person* ptr);
int printError(FILE* fp);
void recordPersonData(Person* ptr);
Person* reconstructPerson(char* name);

#endif