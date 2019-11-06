#ifndef THREADMANAGEMENT_H_INCLUDED
#define THREADMANAGEMENT_H_INCLUDED

#include <windows.h>

DWORD WINAPI ThreadFunc();
void startThread();
void stopThread();

#endif // THREADMANAGEMENT_H_INCLUDED
