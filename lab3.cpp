#include "lab3.h"
#include <windows.h>
#include <stdio.h>


#define THREADCOUNT 11
HANDLE Threads[THREADCOUNT];
HANDLE semA, semB, semC, semD, semE, semF, semG, semH, semI, semK, semM;
HANDLE mutex;
DWORD ThreadID;

unsigned int lab3_thread_graph_id()
{
    return 3;
}

const char* lab3_unsynchronized_threads()
{
    return "defh";
}

const char* lab3_sequential_threads()
{
    return "bcd";
}


DWORD WINAPI ThreadA(LPVOID name)
{
    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semA, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'a' << std::flush;
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semB, 1, NULL))
            printf("Release Semaphore B error: %d\n", GetLastError());
    }

    return TRUE;
}
DWORD WINAPI ThreadB(LPVOID name)
{
    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semB, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'b' << std::flush;
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semD, 1, NULL))
            printf("Release Semaphore error: %d\n", GetLastError());
    }

    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semB, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'b' << std::flush;
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semC, 1, NULL))
            printf("Release Semaphore error: %d\n", GetLastError());
    }

    return TRUE;
}

DWORD WINAPI ThreadC(LPVOID name)
{
    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semC, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'c' << std::flush;
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semD, 1, NULL))
            printf("Release Semaphore error: %d\n", GetLastError());
    }

    return TRUE;
}

DWORD WINAPI ThreadD(LPVOID name)
{
    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semD, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'd' << std::flush;
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semA, 1, NULL))
            printf("Release Semaphore error: %d\n", GetLastError());
    }

    if (!ReleaseSemaphore(semD, 1, NULL))
            printf("Release Semaphore error: %d\n", GetLastError());
    for (size_t i = 3; i < 6; ++i)
    {
        WaitForSingleObject(semD, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'd' << std::flush;
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semB, 1, NULL))
            printf("Release Semaphore error: %d\n", GetLastError());
    }

    WaitForSingleObject(semD, INFINITE);
    for (size_t i = 6; i < 9; ++i)
    {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'd' << std::flush;
        ReleaseMutex(mutex);
        computation();
    }

    return TRUE;
}

DWORD WINAPI ThreadE(LPVOID name)
{
    WaitForSingleObject(semE, INFINITE);
    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'e' << std::flush;
        ReleaseMutex(mutex);
        computation();
    }


    return TRUE;
}

DWORD WINAPI ThreadF(LPVOID name)
{
    WaitForSingleObject(semF, INFINITE);
    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'f' << std::flush;
        ReleaseMutex(mutex);
        computation();
    }

    for (size_t i = 3; i < 6; ++i)
    {
        WaitForSingleObject(semF, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'f' << std::flush;
        ReleaseMutex(mutex);
        computation();
        if (!ReleaseSemaphore(semH, 1, NULL)){
            printf("ReleaseSemaphore error: %d\n", GetLastError());
        }
    }

    return TRUE;
}

DWORD WINAPI ThreadG(LPVOID name)
{
    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semG, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'g' << std::flush;
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semG, 1, NULL))
            printf("Release Semaphore error: %d\n", GetLastError());
    }

    if (!ReleaseSemaphore(semH, 1, NULL))
            printf("Release Semaphore error: %d\n", GetLastError());

    return TRUE;
}

DWORD WINAPI ThreadH(LPVOID name)
{
    WaitForSingleObject(semH, INFINITE);
    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'h' << std::flush;
        ReleaseMutex(mutex);
        computation();
    }

    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semH, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'h' << std::flush;
        ReleaseMutex(mutex);
        computation();
        if (!ReleaseSemaphore(semF, 1, NULL)){
            printf("ReleaseSemaphore error: %d\n", GetLastError());
        }
    }

    if (!ReleaseSemaphore(semG, 1, NULL)){
            printf("ReleaseSemaphore error: %d\n", GetLastError());
    }

    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semH, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'h' << std::flush;
        ReleaseMutex(mutex);
        computation();
        if (!ReleaseSemaphore(semI, 1, NULL)){
            printf("ReleaseSemaphore error: %d\n", GetLastError());
        }
    }

    return TRUE;
}

DWORD WINAPI ThreadI(LPVOID name)
{
    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semI, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'i' << std::flush;
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semK, 1, NULL))
            printf("Release Semaphore error: %d\n", GetLastError());
    }

    return TRUE;
}

DWORD WINAPI ThreadK(LPVOID name)
{
    for (size_t i = 0; i < 3; ++i) {
        WaitForSingleObject(semK, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'k' << std::flush;
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semH, 1, NULL))
            printf("Release Semaphore error: %d\n", GetLastError());
    }

    if (!ReleaseSemaphore(semK, 1, NULL))
            printf("Release Semaphore error: %d\n", GetLastError());

    for (size_t i = 0; i < 3; ++i) {
        WaitForSingleObject(semK, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'k' << std::flush;
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semM, 1, NULL))
            printf("Release Semaphore error: %d\n", GetLastError());
    }

    return TRUE;
}

DWORD WINAPI ThreadM(LPVOID name)
{
    for (size_t i = 0; i < 3; ++i)
    {
        WaitForSingleObject(semM, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        std::cout << 'm' << std::flush;
        ReleaseMutex(mutex);
        computation();

        if (!ReleaseSemaphore(semK, 1, NULL))
            printf("ReleaseSemaphore error: %d\n", GetLastError());
    }

    return TRUE;
}


int lab3_init()
{
    mutex = CreateMutex(NULL, FALSE, NULL);

    semA = CreateSemaphore(NULL, 1, 1, NULL);
    if (semA == NULL){
        printf("CreateSemaphore A error: %d\n", GetLastError());
        return 1;
    }
    semB = CreateSemaphore(NULL, 0, 1, NULL);
    if (semB == NULL){
        printf("CreateSemaphoreB error: %d\n", GetLastError());
        return 1;
    }
    semC = CreateSemaphore(NULL, 0, 1, NULL);
    if (semC == NULL){
        printf("CreateSemaphore  C error: %d\n", GetLastError());
        return 1;
    }
    semD = CreateSemaphore(NULL, 0, 1, NULL);
    if (semD == NULL){
        printf("CreateSemaphore D error: %d\n", GetLastError());
        return 1;
    }
    semE = CreateSemaphore(NULL, 0, 1, NULL);
    if (semE == NULL){
        printf("CreateSemaphore E error: %d\n", GetLastError());
        return 1;
    }
    semF = CreateSemaphore(NULL, 0, 1, NULL);
    if (semF == NULL){
        printf("CreateSemaphore F error: %d\n", GetLastError());
        return 1;
    }
    semG = CreateSemaphore(NULL, 0, 1, NULL);
    if (semG == NULL){
        printf("CreateSemaphore G error: %d\n", GetLastError());
        return 1;
    }
    semM = CreateSemaphore(NULL, 0, 1, NULL);
    if (semM == NULL){
        printf("CreateSemaphore M error: %d\n", GetLastError());
        return 1;
    }
    semH = CreateSemaphore(NULL, 0, 1, NULL);
    if (semH == NULL){
        printf("CreateSemaphore H error: %d\n", GetLastError());
        return 1;
    }
    semK = CreateSemaphore(NULL, 0, 1, NULL);
    if (semK == NULL){
        printf("CreateSemaphore K error: %d\n", GetLastError());
        return 1;
    }
    semI = CreateSemaphore(NULL, 0, 1, NULL);
    if (semI == NULL){
        printf("CreateSemaphore N error: %d\n", GetLastError());
        return 1;
    }

    Threads[0] = CreateThread(NULL, 0, ThreadA, NULL, 0, &ThreadID);
    Threads[1] = CreateThread(NULL, 0, ThreadB, NULL, 0, &ThreadID);
    Threads[2] = CreateThread(NULL, 0, ThreadC, NULL, 0, &ThreadID);
    Threads[3] = CreateThread(NULL, 0, ThreadD, NULL, 0, &ThreadID);
    Threads[4] = CreateThread(NULL, 0, ThreadE, NULL, 0, &ThreadID);
    Threads[5] = CreateThread(NULL, 0, ThreadF, NULL, 0, &ThreadID);
    Threads[7] = CreateThread(NULL, 0, ThreadG, NULL, 0, &ThreadID);
    Threads[6] = CreateThread(NULL, 0, ThreadH, NULL, 0, &ThreadID);
    Threads[8] = CreateThread(NULL, 0, ThreadI, NULL, 0, &ThreadID);
    Threads[9] = CreateThread(NULL, 0, ThreadK, NULL, 0, &ThreadID);
    Threads[10] = CreateThread(NULL, 0, ThreadM, NULL, 0, &ThreadID);

    WaitForSingleObject(Threads[2], INFINITE);

    if (!ReleaseSemaphore(semD, 1, NULL)){
        printf("ReleaseSemaphore error: %d\n", GetLastError());
    }
    if (!ReleaseSemaphore(semE, 1, NULL)){
        printf("ReleaseSemaphore error: %d\n", GetLastError());
    }
    if (!ReleaseSemaphore(semF, 1, NULL)){
        printf("ReleaseSemaphore error: %d\n", GetLastError());
    }
    if (!ReleaseSemaphore(semH, 1, NULL)){
        printf("ReleaseSemaphore error: %d\n", GetLastError());
    }

    WaitForSingleObject(Threads[3], INFINITE);
    WaitForSingleObject(Threads[4], INFINITE);

    if (!ReleaseSemaphore(semF, 1, NULL)){
        printf("ReleaseSemaphore error: %d\n", GetLastError());
    }

    for (int i = 0; i < THREADCOUNT; i++) {
        WaitForSingleObject(Threads[i], INFINITE);
        CloseHandle(Threads[i]);
    }   
   
 //для  семафоров
    CloseHandle(semA);
    CloseHandle(semB);
    CloseHandle(semC);
    CloseHandle(semD);
    CloseHandle(semE);
    CloseHandle(semF);
    CloseHandle(semG);
    CloseHandle(semH);
    CloseHandle(semI);
    CloseHandle(semK);
    CloseHandle(semM);

    return 0;
}
