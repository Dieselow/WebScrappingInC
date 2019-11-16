//
// Created by Retr0 on 16/11/2019.
//

#ifndef WEBSCRAPPINGINC_TASK_H
#define WEBSCRAPPINGINC_TASK_H
#include "FileParser.h"
#include "Action.h"
void getTaskContent(FILE *file);
int getTaskNumber(char *string,int size);
Task *fillTasks(FILE *file, Task *tasks);
void fillTaskName(char *taskName, char c, FILE *file);
void fillTaskAction(Task *tasks, Action *actions, int size);
#endif //WEBSCRAPPINGINC_TASK_H
