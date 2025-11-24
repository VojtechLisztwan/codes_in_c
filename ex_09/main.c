#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct{
    int id;
    char *login;
    char *name;
    char *surname;
}User_t;

typedef struct{
    int id;
    char *task_name;
    int points;
}Task_t;


User_t *userNew(int id, char *login, char *name, char *surname){
    User_t *tmp = malloc(sizeof(User_t));
    tmp->id = id;
    tmp->login = strdup(login);
    tmp->name = strdup(name);
    tmp->surname = strdup(surname);
    return tmp;
}

void userDestroy(User_t **user){
    free((*user)->login);
    free((*user)->name);
    free((*user)->surname);
    free(*user);
    *user = NULL;
}

User_t *userParse(char *line){
    int id = atoi(strtok(line, ";"));
    char *login = strtok(NULL, ";");
    char *name = strtok(NULL, ";");
    char *surname = strtok(NULL, "\n");
    return userNew(id, login, name, surname);
}

Task_t *taskNew(int id, char *task_name, int points){
    Task_t *tmp = malloc(sizeof(Task_t));
    tmp->id = id;
    tmp->task_name = strdup(task_name);
    tmp->points = points;
    return tmp;
}

void taskDestroy(Task_t **task){
    free((*task)->task_name);
    free(*task);
    *task = NULL;
}

Task_t *taskParse(char *line){

    int id = atoi(strtok(line, ";"));
    char *task_name = strtok(NULL, ";");
    int points = atoi(strtok(line, ";"));
    return taskNew(id, task_name, points);
}

void removeNewLine(char *line){
    int len = strlen(line);
    if(line[len-1]=='\n'){
        line[len-1] = '\0';
    }
}

int main() {
    User_t *users[10];
    int users_no = 0;
    Task_t *tasks[10];
    int tasks_no = 0;
    char users_filename[] = "users.txt";
    char tasks_filename[] = "points.txt";
    char buff[80];


    FILE *temp = fopen(users_filename, "rt");
    while(fgets(buff, 80, temp)){
        removeNewLine(buff);
        users[users_no++] = userParse(buff);
    }
    printf("%d users nacteno\n", users_no);
    fclose(temp);
    
    temp = fopen(tasks_filename, "rt");
    while(fgets(buff, 80, temp)){
        removeNewLine(buff);
       tasks[tasks_no++] = taskParse(buff);
    }
    printf("%d task nacteno\n", tasks_no);
    fclose(temp);




    
    
    for (int i = 0; i < users_no; i++){
        userDestroy(&users[i]);
    }
    for (int i = 0; i < tasks_no; i++){
        taskDestroy(&tasks[i]);
    }


    return 0;
}
