//
// Created by Louis Dumont on 27/10/2019.
//

#include "../headers/Action.h"

Action *getActionContent(FILE *file) {
    char *fileContent;
    int size = 0;
    char c = fgetc(file);
    int counter = 0;
    int actionNumber = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    if (size == 0) {
        printf("error while loading configuration file ");
        return NULL;
    }
    fseek(file, 0, SEEK_SET);
    fileContent = malloc(sizeof(char) * size);
    while (c != EOF) {
        c = fgetc(file);
        fileContent[counter] = c;
        counter++;

    }
    actionNumber = getActionNumber(fileContent, size);
    fseek(file, 0, SEEK_SET);
    Action *actions = malloc(sizeof(Action) * actionNumber);
    actions = fillActions(file, actions, actionNumber);
    free(fileContent);
    return actions;

}

/**
 * This function return the total number of actions in the file to malloc our Action array
 * @param char* string
 * @param int size
 * @return int
 */
int getActionNumber(char *string, int size) {
    int result = 0;
    int i = 0;
    for (i = 0; i < size; i++) {
        if (i == 0) {
            if (string[i] == '=' && string[i + 1] != '=') {
                result++;
            }
        } else if (string[i] == '=' && string[i + 1] != '=' && string[i - 1] != '=') {
            result++;
        }
    }
    return result;
}

/**
 * This function is used to fill our Action array
 * @param FILE file
 * @param Action actions
 * @param int sizeActions
 * @return Action*
 */
Action *fillActions(FILE *file, Action *actions, int sizeActions) {
    char c = fgetc(file);
    int currentAction = 0;
    while (c != EOF) {
        if (c == '=') {
            int counter = 0;
            c = fgetc(file);
            if (c != '=') {
                c = fgetc(file);
                while (c != '>') {
                    c = fgetc(file);
                }
                counter++;
                int startAction = ftell(file);
                int paramsSize = getParamSize(file);
                fseek(file, startAction, SEEK_SET);
                c = fgetc(file);
                // this is the part for the name
                if (counter == 1) {
                    actions[currentAction].name = malloc((paramsSize + 1) * sizeof(char));
                    fillActionName(actions[currentAction].name, c, file);
                    counter++;
                }
                actions[currentAction].name[paramsSize] = '\0';
                while (c != '>') {
                    c = fgetc(file);
                }
                startAction = ftell(file);
                paramsSize = getParamSize(file);
                c = fgetc(file);
                // this is the part for the url
                if (counter == 2) {
                    fseek(file, startAction, SEEK_SET);
                    actions[currentAction].url = malloc((paramsSize + 1) * sizeof(char));
                    fillActionUrl(actions[currentAction].url, c, file);
                    actions[currentAction].url[paramsSize] = '\0';
                    counter++;
                }
                if (counter == 3) {
                    while (c != '+') {
                        c = fgetc(file);
                    }
                    while (c != '{') {
                        c = fgetc(file);
                    }
                    int nbOption = 0;
                    int startOption = ftell(file);
                    while (c != '=' && c != EOF) {
                        if (c == '{') {
                            nbOption++;
                        }
                        c = fgetc(file);
                    }
                    c = fgetc(file);
                    actions[currentAction].options = malloc(sizeof(Option) * nbOption);
                    int currentOption = 0;
                    fseek(file, startOption, SEEK_SET);
                    while (currentOption < nbOption) {
                        while (c != '{') {
                            c = fgetc(file);
                        }
                        int nameSize = getNameSize(file);
                        fseek(file, startOption, SEEK_SET);
                        c = fgetc(file);
                        actions[currentAction].options[currentOption].name = malloc((1 + nameSize) * sizeof(char));
                        int i = 0;
                        //printf("\n----------------------------------------------------\n");
                        while (c != ' ') {
                            actions[currentAction].options[currentOption].name[i] = c;
                            //printf("%c", c);
                            i++;
                            c = fgetc(file);
                        }
                        actions[currentAction].options[currentOption].name[nameSize] = '\0';
                        fseek(file, startOption, SEEK_SET);
                        while (c != '>') {
                            c = fgetc(file);
                        }
                        int paramSize = getParamSize(file);
                        fseek(file, startOption, SEEK_SET);
                        c = fgetc(file);
                        while (c != '>') {
                            c = fgetc(file);
                        }
                        actions[currentAction].options[currentOption].value = malloc((1 + paramSize) * sizeof(char));
                        i = 0;
                        while (c != '}') {
                            if (c != ' ' && c != '>') {
                                actions[currentAction].options[currentOption].value[i] = c;
                                i++;
                            }
                            c = fgetc(file);
                        }
                        actions[currentAction].options[currentOption].value[paramSize] = '\0';
                        currentOption++;
                        if (currentOption < nbOption) {
                            while (c != '{') {
                                c = fgetc(file);
                            }
                            startOption = ftell(file);
                        }
                    }
                    fseek(file, startOption, SEEK_SET);
                }
                currentAction++;
            }
        }
        c = fgetc(file);
    }
    return actions;
}

/**
 * This functions is used to get correct param size to malloc effectively
 * @param FILE file
 * @return int
 */
int getParamSize(FILE *file) {
    char c = fgetc(file);
    int result = 0;
    while (c != '}') {
        if (c != ' ') {
            result++;
        }
        c = fgetc(file);
    }
    return result;

}


/**
 * This functions is used to get correct param's name size to malloc effectively
 * @param FILE file
 * @return int
 */
int getNameSize(FILE *file) {
    char c = fgetc(file);
    int result = 0;
    while (c != '-') {
        if (c != ' ') {
            result++;
        }
        c = fgetc(file);
    }
    fgetc(file);
    return result;
}

void fillActionName(char *actionName, char c, FILE *file) {
    int i = 0;
    while (c != '}') {
        if (c != ' ') {
            actionName[i] = c;
            i++;
        }
        c = fgetc(file);
    }
}

void fillActionUrl(char *actionUrl, char c, FILE *file) {
    int i = 0;
    c = fgetc(file);
    while (c != '}') {
        if (c != ' ') {
            actionUrl[i] = c;
            i++;
        }
        c = fgetc(file);
    }
    actionUrl[i+1] = '\0';
}
