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
#include "../headers/Task.h"
#include "../headers/Application.h"
#include "../headers/CurlApp.h"

static int status = 0;  // 0 if enable | 1 if enable
static int init = 0;
static HANDLE thread;
static Task* tasks;
static int taskNumber;

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
    int i = 0;
    int y = 0;
    while(1){
        actualTime = getActualTimestamp();
        for(i = 0; i < taskNumber; i++){
            if(actualTime >= tasks[i].extTimeStamp){ //next time
                //printf("%d", tasks[i].actionNumber);
                for(y = 0; y < tasks[i].actionNumber; y++){ //For each action scrap the site
                    //printf("%s\n", tasks[i].actions[y].url);
                    scrap(tasks[i].actions[y].url);

                }
                //printf("\n%s - ", tasks[i].actions[0].url);
                tasks[i].extTimeStamp = calcNextTimeStamp(tasks[i]);
            }
        }

        Sleep(1000);   //wait for 1 seconds
     }

  return 0;
}
/**
 * Start the thread
 */
void startThread(){
    if(status == 0){
        if(initTasks() == 1){
            thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
            if (thread) {
                status = 1;
                color(LIGHT_GREEN, BLACK);
                printf("\n\t\t\t\t\tCron is now activate\n\n");
                color(WHITE, BLACK);
            }
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
/**
 *  Init the tasks
 */
int initTasks(){
    if(init == 0){
        FILE* file = fopen("C:\\Users\\Gwend\\Documents\\Cours\\ESGI\\C\\WebScrappingInC\\ressources\\configuration\\conf.sconf","r");
        if(file==NULL){
            printf("error while loading configuration");
            return 0;
        }

        tasks = getTaskContent(file);
/*
        //printf("%s\n", tasks[0].actionName);
        printf("%s\n", tasks[0].actions[0].url);
        printf("%d\n", tasks[0].actionNumber);
        system("pause");
*/
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        fseek(file, 0, SEEK_SET);
        char* fileContent;
        char c = 'a';
        int counter = 0;
        fileContent = malloc(sizeof(char) * size);
        while (c != EOF) {
            c = fgetc(file);
            fileContent[counter] = c;
            counter++;
        }

        taskNumber = getTaskNumber(fileContent, size);
        fclose(file);

        intitTasksTimestamp();

        init = 1;
    }

    return 1;
}
/**
 *  Calculation of the next time stamp for the task in argument
 */
double calcNextTimeStamp(Task t){
    double timestamp  = getActualTimestamp();
    if(t.hours != NULL){
        timestamp += ((t.hours*60)*60);
    }
    if(t.minutes != NULL){
        timestamp += (t.minutes*60);
    }
    if(t.seconds != NULL){
        timestamp += t.seconds;
    }
    return timestamp;
}
/**
 *  Initialize the timestamp for all the tasks
 */
void intitTasksTimestamp(){
    int i = 0;
    for(i = 0; i < taskNumber; i++){
        tasks[i].extTimeStamp = calcNextTimeStamp(tasks[i]);
    }
}
