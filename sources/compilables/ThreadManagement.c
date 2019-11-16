/**
 *  This part of the project manage the Threads and the cron
 *  @author Gwendal
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "../headers/ThreadManagement.h"
#include "../headers/Color.h"
#include "../headers/Application.h"

static int status = 0;  // 0 if enable | 1 if enable
static HANDLE thread;

/**
 *  Return the actual timestamp
 */
double getActualTimestamp(){
    time_t timer;
    struct tm y2k = {0};
    double seconds;

    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

    time(&timer);  // get current time; same as: timer = time(NULL)

    seconds = difftime(timer,mktime(&y2k));     //number of seconds since 1 Jan 1970

    return seconds;
}
/**
 *  Actions of the thread
 */
DWORD WINAPI ThreadFunc() {
    double actualTime;
    double nextTime;    //It will be an element of the structure task
     while(1){
        actualTime = getActualTimestamp();
        if(actualTime >= nextTime){ //next time
            /**
            * TODO : Add here the code scrap from the conf file
            */
        }
        Sleep(10000);   //wait for 10 seconds
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
