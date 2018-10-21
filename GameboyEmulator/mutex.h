#pragma once

#ifdef _WIN32

#include <windows.h>

#define MUTEX HANDLE

#define CREATE_MUTEX() CreateMutex(NULL, FALSE, NULL)
#define DISPOSE_MUTEX(mutex) CloseHandle(mutex)

#define TAKE_MUTEX(mutex) WaitForSingleObject(mutex, INFINITE)
#define RELEASE_MUTEX(mutex) ReleaseMutex(mutex)

#endif