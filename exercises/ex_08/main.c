#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50



typedef struct{
    char firstName[MAX];
    char lastName[MAX];
    int age;
    float average_score;
}Student_t;




int main() {
    int n;
    char buff[MAX];
    
    /*fgets(buff, MAX, stdin);
    n=atoi(buff);*/

    scanf("%d", &n);
    Student_t *students = malloc(sizeof(Student_t)*n);
    int indexOfBest=0;
    for (int i = 0; i < n; i++){
        //printf("Enter First name of student: ");
        //fgets(students[i].firstName, MAX, stdin);
        scanf("%s", students[i].firstName);
        //printf("Enter Last name of student: ");
        //fgets(students[i].lastName, MAX, stdin);
        scanf("%s", students[i].lastName);
        
        //printf("Enter age of student: ");
        scanf("%d", &students[i].age);
        //printf("Enter average score of student: ");
        scanf("%f", &students[i].average_score);
        //system("clear");
        if(students[indexOfBest].average_score<students[i].average_score)indexOfBest=i;
    }
    Student_t *best = &students[indexOfBest];
    printf("\n\nStudent with the best score is %s %s; %d years old with score %f\n\n", (*best).firstName, best->lastName, best->age, best->average_score);


    free(students);
    return 0;
}
