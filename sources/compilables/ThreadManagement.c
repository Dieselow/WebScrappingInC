/**
 *  This part of the project manage the Threads and the cron
 *  @author Gwendal
 */
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "../headers/ThreadManagement.h"

static int status = 0;  // 0 if enable | 1 if enable
static HANDLE thread;

/**
 *  Actions of the thread
 */
DWORD WINAPI ThreadFunc() {
  // Do stuff.  This will be the first function called on the new thread.
  // When this function returns, the thread goes away.  See MSDN for more details.



  return 0;
}
/**
 * Start the thread
 */
void startThread(){
    if(status == 0){
        thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
        if (thread) {
            // Optionally do stuff, such as wait on the thread.
            status = 1;
        }
    } else {
        printf("Cron Scrapping already Activate\n\n");
    }
}
/**
 * Stop the thread
 */
void stopThread(){
    if(status == 1){
        if (thread) {
            TerminateThread(thread, 0); // Dangerous source of errors!
            CloseHandle(thread);
            status = 0;
        }
    } else {
        printf("Cron Scrapping already Desactivate\n\n");
    }
}
