//
// Created by Retr0 on 27/10/2019.
//

#include "../headers/Action.h"

void getActionContent(FILE *file) {
    char *fileContent;
    int size = 0;
    char c = fgetc(file);
    int counter = 0;
    int actionNumber = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    if (size == 0) {
        return;
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
    printf("%d", actionNumber);
    Action *actions = malloc(sizeof(Action) * actionNumber);
    actions = fillActions(file, actions, actionNumber);
    printf("%s", actions[0].name);
    printf("%s", actions[1].name);
    free(fileContent);

}

int getActionNumber(char *string, int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
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

Action *fillActions(FILE *file, Action *actions, int sizeActions) {
    size_t len = 0;
    ssize_t read;
    char c = fgetc(file);
    int action = 0;
    while (c != EOF) {
        int counter = 0;
        if (c == '=') {
            c = fgetc(file);
            if (c != '=') {
                read = getline(&actions[action].name, &len, file);
                read = getline(&actions[action].url, &len, file);
                action++;
                counter++;
            }
        }
        c = fgetc(file);
        if (counter == sizeActions) {
            break;
        }
    }
    return actions;
}
