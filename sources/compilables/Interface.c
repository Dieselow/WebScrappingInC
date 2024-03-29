/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Interface.c
 * Author: Mikadows
 *
 * Created on 14 octobre 2019, 20:21
 */

/*
 _    _      _           _____
| |  | |    | |         /  __ \
| |  | | ___| |__    ___| /  \/_ __ __ _ _ __  _ __   ___ _ __
| |/\| |/ _ \ '_ \  / __| |   | '__/ _` | '_ \| '_ \ / _ \ '__|
\  /\  /  __/ |_) | \__ \ \__/\ | | (_| | |_) | |_) |  __/ |
 \/  \/ \___|_.__/  |___/\____/_|  \__,_| .__/| .__/ \___|_|
                                        | |   | |
                                        |_|   |_|
 *
 *
$$$$$$$$\           $$\   $$\
$$  _____|          \__|  $$ |
$$ |      $$\   $$\ $$\ $$$$$$\
$$$$$\    \$$\ $$  |$$ |\_$$  _|
$$  __|    \$$$$  / $$ |  $$ |
$$ |       $$  $$<  $$ |  $$ |$$\
$$$$$$$$\ $$  /\$$\ $$ |  \$$$$  |
\________|\__/  \__|\__|   \____/



 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "../headers/Application.h"
#include "../headers/Color.h"
#include "../headers/Interface.h"
#include "../headers/CurlApp.h"
#include "../headers/ThreadManagement.h"

/**
 * Display the complete main menu
 */
void mainMenu(){
    int i = 0;
    char c = NULL;
    system("chcp 65001");   //Permet l'affichage des caratères spéciaux/ASCII étendue.
    system("cls");
    printTitle();
    printMenu(i);
    while(c != 27){     // code for ESC KEY
        c= getch();
        switch(c) {
            case 72:    // code for arrow up
                i--;
                //printf("UP\n");
                break;
            case 80:    // code for arrow down
                i++;
                //printf("DOWN\n");
                break;
            case '\r':    // code for enter
                printSubMenu(i);
                //printf("ENTER\n");
                break;
        }
        if(i > 2){
            i = 0;
        } else if(i < 0){
            i = 2;
        }
        printMenu(i);
    }
    system("cls");
    printExit();

}
/**
 * Print the main title
 */
void printTitle(){
    printf("\n\t\t\t _    _      _           _____                        \n"
            "\t\t\t| |  | |    | |         /  __ \\                                \n"
            "\t\t\t| |  | | ___| |__    ___| /  \\/_ __ __ _ _ __  _ __   ___ _ __   \n"
            "\t\t\t| |/\\| |/ _ \\ '_ \\  / __| |   | '__/ _` | '_ \\| '_ \\ / _ \\ '__|  \n"
            "\t\t\t\\  /\\  /  __/ |_) | \\__ \\ \\__/\\ | | (_| | |_) | |_) |  __/ |     \n"
            "\t\t\t \\/  \\/ \\___|_.__/  |___/\\____/_|  \\__,_| .__/| .__/ \\___|_|      \n"
            "\t\t\t                                        | |   | |                \n"
            "\t\t\t                                        |_|   |_|                \n");
}
/**
 * Print the exit message
 */
void printExit(){
    color(RED, BLACK);
    printf("\n\t\t\t\t\t$$$$$$$$\\           $$\\   $$\\     \n"
           "\t\t\t\t\t$$  _____|          \\__|  $$ |    \n"
           "\t\t\t\t\t$$ |      $$\\   $$\\ $$\\ $$$$$$\\   \n"
           "\t\t\t\t\t$$$$$\\    \\$$\\ $$  |$$ |\\_$$  _|  \n"
           "\t\t\t\t\t$$  __|    \\$$$$  / $$ |  $$ |    \n"
           "\t\t\t\t\t$$ |       $$  $$<  $$ |  $$ |$$\\ \n"
           "\t\t\t\t\t$$$$$$$$\\ $$  /\\$$\\ $$ |  \\$$$$  |\n"
           "\t\t\t\t\t\\________|\\__/  \\__|\\__|   \\____/ \n\n\n\t\t\t\t    ");
}
/**
 * Move the arrow in function of the user choice
 */
void printMenu(int i){
    system("cls");
    printTitle();
    switch(i){
        case 0:
            color(LIGHT_GREEN, BLACK);
            printf("\n\t\t\t\t\t ==> ");
            color(WHITE, BLACK);
            printf("• Quick Scrap\n"
                   "\t\t\t\t\t     • Start Cron Scrapping\n"
                   "\t\t\t\t\t     • Onglet 3\n");
            color(GREY, BLACK);
            printf("\n\n\t\t\t   (ESC to exit, naviagte with up and down arrow)\n");
            color(WHITE, BLACK);
            break;
        case 1:
            printf("\n\t\t\t\t\t     • Quick Scrap\n"
                   "\t\t\t\t\t");
            color(LIGHT_GREEN, BLACK);
            printf(" ==> ");
            color(WHITE, BLACK);
            printf("• Start Cron Scrapping\n"
                   "\t\t\t\t\t     • Onglet 3\n");
            color(GREY, BLACK);
            printf("\n\n\t\t\t   (ESC to exit, naviagte with up and down arrow)\n");
            color(WHITE, BLACK);
            break;
        case 2:
            printf("\n\t\t\t\t\t     • Quick Scrap\n"
                   "\t\t\t\t\t     • Start Cron Scrapping\n"
                   "\t\t\t\t\t");
            color(LIGHT_GREEN, BLACK);
            printf(" ==> ");
            color(WHITE, BLACK);
            printf("• Onglet 3\n");
            color(GREY, BLACK);
            printf("\n\n\t\t\t   (ESC to exit, naviagte with up and down arrow)\n");
            color(WHITE, BLACK);
            break;
        default:
            printf("ERROR BAD CALL MAIN MENU");
            break;
    }
}
/**
 * Call functions selected by the user
 */
void printSubMenu(int i){
        switch(i){
        case 0:
            system("cls");
            printTitle();
            printf("\n\t\t\t\t\t-------  Quick Scrap -------\n");
            char url[500];
            printf("\n\t\t\t\t\tEnter your url : ");
            scanf("%s", url);
            fflush(stdin);      //Drop the \n in the buffer
            scrap(url);
            system("pause");
            break;
        case 1:
            subMenuStartThread();
            break;
        case 2:
            printf("\n\t\t\t\t\t-------  Onglet 3 -------\n");

            break;
        default:
            printf("ERROR BAD CALL MAIN MENU");
            break;

    }
}
/**
 * Print the sub menu for the thread
 */
void printSubMenuThread(int i){
    system("cls");
    printTitle();
    switch(i){
        case 0:
            printf("\n\t\t\t\t\t-------  Cron Scrapping -------\n");
            color(LIGHT_GREEN, BLACK);
            printf("\n\t\t\t\t\t ==> ");
            color(WHITE, BLACK);
            printf("• Enable cron scrapping\n"
                   "\t\t\t\t\t     • Disable cron scrapping\n");
            color(GREY, BLACK);
            printf("\n\n\t\t\t   (ESC to back, naviagte with up and down arrow)\n");
            color(WHITE, BLACK);
            break;
        case 1:
            printf("\n\t\t\t\t\t-------  Cron Scrapping -------\n");
            printf("\n\t\t\t\t\t     • Enable cron scrapping\n"
                   "\t\t\t\t\t");
            color(LIGHT_GREEN, BLACK);
            printf(" ==> ");
            color(WHITE, BLACK);
            printf("• Disable cron scrapping\n");
            color(GREY, BLACK);
            printf("\n\n\t\t\t   (ESC to back, naviagte with up and down arrow)\n");
            color(WHITE, BLACK);
            break;
        default:
            printf("ERROR BAD CALL MAIN MENU");
            break;
    }
}
/**
 * Call the functions of the selected action
 */
void actionSelected(int i){
        switch(i){
        case 0:
            startThread();
            break;
        case 1:
            stopThread();
            break;
        default:
            printf("ERROR BAD CALL SUB MENU");
            break;
    }
}
/**
 * Selector for the menu
 */
void subMenuStartThread(){
    int i = 0;
    char c = NULL;
    printSubMenuThread(i);
    while(c != 27){     // code for ESC KEY
        c= getch();
        switch(c) {
            case 72:    // code for arrow up
                i--;
                //printf("UP\n");
                break;
            case 80:    // code for arrow down
                i++;
                //printf("DOWN\n");
                break;
            case '\r':    // code for enter
                actionSelected(i);
                system("pause");
                //printf("ENTER\n");
                break;
        }
        if(i > 1){
            i = 0;
        } else if(i < 0){
            i = 1;
        }
        printSubMenuThread(i);
    }
    system("cls");
}
