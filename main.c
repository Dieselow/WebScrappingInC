//
// Created by Retr0 on 27/10/2019.
//
#include <stdlib.h>
#include <stdio.h>
#include "sources/headers/FileParser.h"
#include "sources/headers/Action.h"
int main(int argc,char ** argv){
    FILE* file = fopen("/home/friday/Cprojects/WebScrappingInC/ressources/configuration/conf.sconf","r");
    if(file==NULL){
        printf("error while loading configuration");
        return 0;
    }
    getActionContent(file);
    fclose(file);
    return 0;
}
