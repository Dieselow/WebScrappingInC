#ifndef THREADMANAGEMENT_H_INCLUDED
#define THREADMANAGEMENT_H_INCLUDED

#include <windows.h>
#include "FileParser.h"

double getActualTimestamp();
DWORD WINAPI ThreadFunc();
void startThread();
void stopThread();
int initTasks();
double calcNextTimeStamp(Task t);
void intitTasksTimestamp();

#endif // THREADMANAGEMENT_H_INCLUDED
