//
// Created by Louis Dumont on 16/11/2019.
//

#include "../headers/Task.h"
#include "../headers/Action.h"
#include <ctype.h>

void getTaskContent(FILE *file) {
    char *fileContent;
    int size = 0;
    char c = fgetc(file);
    int counter = 0;
    int taskNumber = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    if (size == 0) {
        printf("error while loading configuration file ");
        return;
    }
    fseek(file, 0, SEEK_SET);
    fileContent = malloc(sizeof(char) * size);
    while (c != EOF) {
        c = fgetc(file);
        fileContent[counter] = c;
        counter++;

    }
    taskNumber = getTaskNumber(fileContent, size);
    int actionNumber = getActionNumber(file, size);
    fseek(file, 0, SEEK_SET);
    Action *actions = malloc(sizeof(Action) * actionNumber);
    actions = fillActions(file,actions,actionNumber);
    Task *tasks = malloc(sizeof(Task) * taskNumber);
    fseek(file, 0, SEEK_SET);
    tasks = fillTasks(file, tasks);
    fillTaskAction(tasks,actions,taskNumber);
    printf("%s",tasks[0].actions[0].name);
}


/**
 * This function return the total number of tasks in the file to malloc our Action array
 * @param char* string
 * @param int size
 * @return int
 */
int getTaskNumber(char *string, int size) {
    int result = 0;
    int i = 0;
    for (i = 0; i < size; i++) {
        if (i == 0) {
            if (string[i] == '=' && string[i + 1] == '=') {
                result++;
            }
        } else if (string[i] == '=' && string[i + 1] == '=') {
            result++;
        }
    }
    return result;
}

/**
 * This function is used to fill our Tasks array
 *
 * @param file
 * @param tasks
 * @return Task
 */
Task *fillTasks(FILE *file, Task *tasks) {
    char c = fgetc(file);
    int currentAction = 0;
    while (c != EOF) {
        if (c == '=') {
            int counter = 0;
            c = fgetc(file);
            if (c == '=') {
                c = fgetc(file);
                while (c != '>') {
                    c = fgetc(file);
                }
                int startTask = ftell(file);
                int paramsSize = getParamSize(file);
                fseek(file, startTask, SEEK_SET);
                c = fgetc(file);
                // this is the part for the name
                tasks[currentAction].name = malloc((paramsSize + 1) * sizeof(char));
                fillTaskName(tasks[currentAction].name, c, file);
                tasks[currentAction].name[paramsSize] = '\0';
                while (c != '+') {
                    char line[256];
                    fgets(line, sizeof(line), file);
                    char *temp = line;
                    if (strstr(line, "second")) {
                        while (*temp) {
                            if (isdigit(*temp)) {
                                tasks[currentAction].seconds = (int) strtol(temp, &temp, 10);
                            } else {
                                temp++;
                            }
                        }
                    }
                    if (strstr(line, "minute")) {
                        while (*temp) {
                            if (isdigit(*temp)) {
                                tasks[currentAction].minutes = (int) strtol(temp, &temp, 10);
                            } else {
                                temp++;
                            }
                        }
                    }
                    if (strstr(line, "hour")) {
                        while (*temp) {
                            if (isdigit(*temp)) {
                                tasks[currentAction].hours = (int) strtol(temp, &temp, 10);
                            } else {
                                temp++;
                            }
                        }
                    }
                    c = fgetc(file);
                }

                currentAction++;
            }
        }
        c = fgetc(file);
    }
    return tasks;
}

void fillTaskName(char *taskName, char c, FILE *file) {
    int i = 0;
    while (c != '}') {
        if (c != ' ') {
            taskName[i] = c;
            i++;
        }
        c = fgetc(file);
    }
}

void fillTaskAction(Task *tasks, Action *actions, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (strcmp(actions[i].name, tasks[j].name) == 0) {
                tasks[j].actions->name = actions[i].name;
                tasks[j].actions->url = actions[i].url;
                tasks[j].actions->options = actions[i].options;
            }
        }
    }
}