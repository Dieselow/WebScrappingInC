//
// Created by Retr0 on 27/10/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileParser.h"
#ifndef WEBSCRAPPINGINC_ACTION_H
#define WEBSCRAPPINGINC_ACTION_H
#endif //WEBSCRAPPINGINC_ACTION_H
void getActionContent(FILE * file);
int getActionNumber(char * string,int size);

int getParamSize(FILE *file);
Action *fillActions(FILE *file, Action *actions, int sizeActions);