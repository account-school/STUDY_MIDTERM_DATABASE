#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include "database.h"



Person* personConstructor(int age_s, char* nam, int num_inter, char** interest, int merp) {
    Person* personPtr = malloc(sizeof(Person));
    personPtr->age_seasons = age_s;
    personPtr->name = nam;
    personPtr->numInterests = num_inter;
    personPtr->interests = (char**)malloc(num_inter * sizeof(char*));
    for (int n = 0; n <num_inter; n++) {
        (personPtr->interests)[n] = interest[n];
    }
    personPtr->merp_score = merp;
    return personPtr;
}


void printPerson(Person* ptr) {
    printf("Age in Seasons: %d\n Name: %s\n Number of Interests: %d\n Interest list::\n[\n",ptr->age_seasons,ptr->name,ptr->numInterests);
    for (int n = 0; n < ptr->numInterests; n++) {
        printf("%s, \n",ptr->interests[n]);
    }
    printf("]\nMerp score: %d\n",ptr->merp_score);
}




int printError(FILE* fp) {
    if (ferror(fp)) {
        fprintf(stderr,"Error #%d:  %s\n",errno,strerror(errno));
        return errno;
    }
    return 0;
}

void recordPersonData(Person* ptr) {
    char* filename = (char*)calloc(200,sizeof(char));
    strcpy(filename,ptr->name);
    strcat(filename,".txt");
    //printf("%s",filename);
    FILE* fp = fopen(filename,"w+");

    if (printError(fp)) {
        return;
    }

    //implicit else

    //implict error detection and print
    if (fprintf(fp,"%d %s %d ",ptr->age_seasons,ptr->name,ptr->numInterests) <= 0) {
        printError(fp);
        return;
    }

    for (int n = 0; n < ptr->numInterests; n++) {
        fprintf(fp,"%s ",((ptr->interests)[n]));
    }
    fputs("",fp);
    fprintf(fp,"%d\n",ptr->merp_score); 
    fclose(fp);

}


Person* reconstructPerson(char* name) {
    // to finish tmrw.

    char* filename = calloc(200,sizeof(char));
    strcat(filename,name);
    strcat(filename,".txt");
    FILE* fp = fopen(filename,"r");
    
    if (ferror(fp)) {
        fprintf(stderr,"Error %d: %s",errno,strerror(errno));
        return NULL;
    }
    //rewind(fp);

    fseek(fp,0,SEEK_SET);

    int ag, numInt;
    char* useless = calloc(200,sizeof(char));
    
    rewind(fp);

    fscanf(fp,"%d %s %d",&ag, useless, &numInt);
    
    //printf("%d %s %d ",ag, name, numInt);
    
    char** interests = (char**)calloc(numInt,sizeof(char*));
    char *word;
    for (int n = 0; n < numInt; n++) {
        word = (char*)calloc(200,sizeof(char));
        fscanf(fp,"%s", word);
        interests[n] = word;
        //printf("%s ",interests[n]);
        
    }
    int merp;
    fscanf(fp,"%d",&merp);

    //printf("%d\n",merp);
    fclose(fp);

    Person* newPerson = personConstructor(ag,name,numInt,interests,merp);
    return newPerson;
    
    

}
