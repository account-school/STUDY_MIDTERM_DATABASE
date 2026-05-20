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


Person* personConstructor(int age_s, char* nam, int num_inter, char*** interest, int merp) {
    Person* personPtr = malloc(sizeof(Person));
    personPtr->age_seasons = age_s;
    personPtr->name = nam;
    personPtr->numInterests = num_inter;
    personPtr->interests = (char**)malloc(num_inter * sizeof(char*));
    for (int n = 0; n <num_inter; n++) {
        (personPtr->interests)[n] = *(interest[n]);
    }
    personPtr->merp_score = merp;
    return personPtr;
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
    if (fprintf(fp,"%d;%s;%d;[",ptr->age_seasons,ptr->name,ptr->numInterests) <= 0) {
        printError(fp);
        return;
    }

    for (int n = 0; n < ptr->numInterests; n++) {
        fprintf(fp,"%s,",((ptr->interests)[n]));
    }
    fputs("];",fp);
    fprintf(fp,"%d\n",ptr->merp_score); 

}


Person* reconstructPerson(char* name) {
    // to finish tmrw.

    return NULL;
    
    

}
int main () {
    char* interest1 = "cars";
    char* interest2 = "Computer Science";
    char* interest3 = "horror movies";
    char** interests[3] = {&interest1, &interest2, &interest3};
    Person* david = personConstructor(80,"David",3,interests,4);
    recordPersonData(david);
    return 0;
}