/**
 *  This part of the project manage the Threads and the cron
 *  @author Gwendal
 */
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "../headers/ThreadManagement.h"
#include "../headers/Color.h"
#include "../headers/Application.h"

static int status = 0;  // 0 if enable | 1 if enable
static HANDLE thread;

/**
 *  Actions of the thread
 */
DWORD WINAPI ThreadFunc() {
     while(1){
       /**
        * TODO : Add here the code scrap from the conf file
        */
     }

  return 0;
}
/**
 * Start the thread
 */
void startThread(){
    if(status == 0){
        thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
        if (thread) {
            status = 1;
            color(LIGHT_GREEN, BLACK);
            printf("\n\t\t\t\t\tCron is now activate\n\n");
            color(WHITE, BLACK);
        }
    } else {
        color(RED, BLACK);
        printf("\n\t\t\t\t\tCron Scrapping already Activate\n\n");
        color(WHITE, BLACK);
    }
}
/**
 * Stop the thread
 */
void stopThread(){
    if(status == 1){
        if (thread) {
            TerminateThread(thread, 0);
            CloseHandle(thread);
            status = 0;
            color(LIGHT_GREEN, BLACK);
            printf("\n\t\t\t\t\tCron is now desactivate\n\n");
            color(WHITE, BLACK);
        }
    } else {
        color(RED, BLACK);
        printf("\n\t\t\t\t\tCron Scrapping already Desactivate\n\n");
        color(WHITE, BLACK);
    }
}
