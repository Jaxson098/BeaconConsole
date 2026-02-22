#define _POSIX_C_SOURCE 199309L

#include<pthread.h>
#include<stdio.h>
#include"utils.h"
#include<string.h>
#include <unistd.h>
#ifdef _WIN32
#include<windows.h>
HANDLE ports[256] = {INVALID_HANDLE_VALUE};
#endif

//recive codes
//0 = CF_B++
//1 = CF_R++
//2 = WM_G++
//3 = M_B++
//4 = M_G++
//5 = M_Y++
//6 = M_R++
//7 = M_P++

pthread_mutex_t portRWmutex = PTHREAD_MUTEX_INITIALIZER;

struct countersStruct counters = {0};
// int numberOfPorts = 0;
// int portNums[256]={0};

void setupPorts() {
    #ifdef _WIN32
    for (int i = 0; i < 256; i++) ports[i] = INVALID_HANDLE_VALUE;
    pthread_t thread;
    for (int i = 0; i < 256; i++) {
        char portName[16];
        char target[255];
        sprintf(portName, "COM%d", i+1);
        if (QueryDosDevice(portName, target, sizeof(target)) != 0) {
            pthread_create(&thread, NULL, portReader, (void*)(intptr_t)(i));
            pthread_detach(thread);
        }
    }
    #endif
}

void* portReader(void* arg) {
    #ifdef _WIN32

    HANDLE port;

    int portWorking = 1;

    struct timespec current;
    double Dcurrent; 
    double LastTried = 0;
    clock_gettime(CLOCK_MONOTONIC,&current); Dcurrent = current.tv_sec + current.tv_nsec*0.000000001;

    char portName[255] = "\\\\.\\COM";
    sprintf(portName+strlen(portName),"%d",(int)(intptr_t)arg+1);

    printf("created %s\n",portName);

    port = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, 0);

    DCB dcbSerialParam = {0};
    dcbSerialParam.DCBlength = sizeof(dcbSerialParam);

    GetCommState(port, &dcbSerialParam);

    dcbSerialParam.BaudRate = CBR_9600;
    dcbSerialParam.ByteSize = 8;
    dcbSerialParam.StopBits = ONESTOPBIT;
    dcbSerialParam.Parity = NOPARITY;

    SetCommState(port, &dcbSerialParam);

    COMMTIMEOUTS timeout = {0};
    timeout.ReadIntervalTimeout = 0;
    timeout.ReadTotalTimeoutConstant = 0;
    timeout.ReadTotalTimeoutMultiplier = 0;
    timeout.WriteTotalTimeoutConstant = 1;
    timeout.WriteTotalTimeoutMultiplier = 0;
    SetCommTimeouts(port, &timeout);

    ports[(int)(intptr_t)arg] = port;

    while(1) {
        Sleep(10);
        BYTE buffer;
        DWORD dwRead = 0;
        pthread_mutex_lock(&portRWmutex);
        if (portWorking && running) {
            if(!ReadFile(port, &buffer, 1, &dwRead, NULL)) {
                CloseHandle(port);
                portWorking = 0;
            } else if (dwRead>0) {
                int recived = buffer - '0';
                if (recived == 0) counters.CF_B++;
                if (recived == 1) counters.CF_R++;
                if (recived == 2) counters.WM_G++;
                if (recived == 3) counters.M_B++;
                if (recived == 4) counters.M_G++;
                if (recived == 5) counters.M_Y++;
                if (recived == 6) counters.M_R++;
                if (recived == 7) counters.M_P++;
            }
        } else if (!portWorking) {
            //try to reconect every second
            clock_gettime(CLOCK_MONOTONIC,&current); Dcurrent = current.tv_sec + current.tv_nsec*0.000000001;
            if (Dcurrent-LastTried > 1) {

                LastTried = Dcurrent;

                port = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, 0);

                DCB dcbSerialParam = {0};
                dcbSerialParam.DCBlength = sizeof(dcbSerialParam);

                GetCommState(port, &dcbSerialParam);

                dcbSerialParam.BaudRate = CBR_9600;
                dcbSerialParam.ByteSize = 8;
                dcbSerialParam.StopBits = ONESTOPBIT;
                dcbSerialParam.Parity = NOPARITY;

                SetCommState(port, &dcbSerialParam);

                COMMTIMEOUTS timeout = {0}; //no timeout exept a small one for write
                timeout.ReadIntervalTimeout = 0;
                timeout.ReadTotalTimeoutConstant = 0;
                timeout.ReadTotalTimeoutMultiplier = 0;
                timeout.WriteTotalTimeoutMultiplier = 0;
                timeout.WriteTotalTimeoutConstant = 1;
                SetCommTimeouts(port, &timeout);

                ports[(int)(intptr_t)arg] = port;

                if (port != INVALID_HANDLE_VALUE) {
                    portWorking = 1;
                }
            }
        }
        pthread_mutex_unlock(&portRWmutex);
    }
    #endif
}

void writePorts(int toWrite, int isCF_GM) {
    #ifdef _WIN32

    printf("got write\n");

    BYTE buffer;
    DWORD dwWrite = 0;
    int portIndexes[256] = {};
    int numPorts = 0;

    pthread_mutex_lock(&portRWmutex);

    for (int i = 0; i<256; i++) {
        if (ports[i] != INVALID_HANDLE_VALUE) {
            portIndexes[numPorts] = i;
            numPorts++;
        }
    }

    if(isCF_GM) {
        for (int i = 0; i<numPorts; i++) {
            if (i%2 == 0) { buffer = '0'; WriteFile(ports[portIndexes[i]] , &buffer, 1, &dwWrite, NULL);}
            else { buffer = '1'; WriteFile(ports[portIndexes[i]] , &buffer, 1, &dwWrite, NULL);}
            PurgeComm(ports[portIndexes[i]], PURGE_RXCLEAR);
        }
    } else {
        buffer = toWrite + '0';
        for (int i = 0; i<numPorts; i++) {
            if (ports[portIndexes[i]] != INVALID_HANDLE_VALUE) {
                WriteFile(ports[portIndexes[i]] , &buffer, 1, &dwWrite, NULL);
                PurgeComm(ports[portIndexes[i]], PURGE_RXCLEAR);
            }
        }
    }
    pthread_mutex_unlock(&portRWmutex);
    #endif
}

void* writePortsThread(void* arg) {
    #ifdef _WIN32 
    int* params = (int*)arg;
    writePorts(params[0], params[1]);
    free(arg);
    return NULL;
    #endif
}