/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>

int loadConfFile(FILE** f){
    int ret = 0; 
    if(fopen("conf.sconf", "r") == NULL){
                ret=0;
    }else{
        *f = fopen("conf.sconf", "r");
        ret = 1;
    }
    return ret;
}

void getConfFileContent(){
    FILE *f = NULL;
    char buffer[1000];
    int i = 0;
    int y = 0;
    
    if(loadConfFile(&f)){
        char c;
        while(c != EOF){
            c = fgetc(f);
            buffer[i] = c;
            i++;
            y++;
        }
        
        char *tab = malloc(sizeof(char)*y);
    
        for(i=0; i<y; i++){
            tab[i] = buffer[i];
            printf("%c", tab[i]);
        }
        system("pause");
        system("cls");
        
        getComments(tab, y);

        system("pause");
        system("cls");
        
        free(tab);
        closeConfFile(&f);
    }

}

int closeConfFile(FILE **f){
    int ret=0;
    
    if(fclose(*f) == 0){
        ret = 1;
    }
    return(ret);
}

void getComments(char* content, int size){
    int i = 0;
    
    for(i=0; i<size; i++){
        if(content[i] == '#'){
            do{
                printf("%c", content[i]);
                i++;
            }while(content[i] != '\n');
            printf("\n");
        }
        /*if(content[i] == '{'){
            do{
                printf("%c", content[i]);
                i++;
            }while(content[i-1] != '}');
            printf("\n");
        }*/
    }
}