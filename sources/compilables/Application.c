/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../headers/Application.h"
#include "../headers/Interface.h"

/**
 * Start the main menu of the software
 */
void start(){
    mainMenu();
}

/**
 * Change the color of the font and the background of
 * @param t     parameter to change the font color
 * @param f     parameter to change the background color
 */
void color(int t,int f){
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,f*16+t);
}
