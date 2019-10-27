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

    printf("%d", actionNumber);
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
