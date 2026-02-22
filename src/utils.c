#define _POSIX_C_SOURCE 199309L

#include<pthread.h>
#include <stdio.h>
#include "utils.h"
#include <string.h>

#ifdef _WIN32
#include<windows.h>
HANDLE ports[10];
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

struct countersStruct counters = {0};

void* portReader(void* arg) {
    #ifdef _WIN32

    // HANDLE port;

    // int portWorking = 1;

    // struct timespec current;
    // double Dcurrent;
    // double LastTried = 0;
    // clock_gettime(CLOCK_MONOTONIC,&current); Dcurrent = current.tv_sec + current.tv_nsec*0.000000001;

    // char portName[255] = "\\\\.\\COM";
    // sprintf(portName+strlen(portName),"%d",*((int*)arg));

    // port = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, 0);

    // DCB dcbSerialParam = {0};
    // dcbSerialParam.DCBlength = sizeof(dcbSerialParam);

    // GetCommState(port, &dcbSerialParam);

    // dcbSerialParam.BaudRate = CBR_9600;
    // dcbSerialParam.ByteSize = 8;
    // dcbSerialParam.StopBits = ONESTOPBIT;
    // dcbSerialParam.Parity = NOPARITY;

    // SetCommState(port, &dcbSerialParam);

    // COMMTIMEOUTS timeout = {0};
    // timeout.ReadIntervalTimeout = 60;
    // timeout.ReadTotalTimeoutConstant = 60;
    // timeout.ReadTotalTimeoutMultiplier = 15;
    // timeout.WriteTotalTimeoutConstant = 60;
    // timeout.WriteTotalTimeoutMultiplier = 8;
    // SetCommTimeouts(port, &timeout);

    // ports[*((int*)arg)-1] = port;

    // while(1) {
    //     BYTE buffer;
    //     DWORD dwRead = 0;
    //     if (portWorking) {
    //         if(!ReadFile(port, &buffer, 1, &dwRead, NULL)) {
    //             CloseHandle(port);
    //             portWorking = 0;
    //         } else {
    //             int recived = (int)buffer;
    //             if (recived == 0) counters.CF_B++;
    //             if (recived == 1) counters.CF_R++;
    //             if (recived == 2) counters.WM_G++;
    //             if (recived == 3) counters.M_B++;
    //             if (recived == 4) counters.M_G++;
    //             if (recived == 5) counters.M_Y++;
    //             if (recived == 6) counters.M_R++;
    //             if (recived == 7) counters.M_P++;
    //         }
    //     } else {
    //         //try to reconect every second
    //         if (Dcurrent-LastTried > 1) {

    //             double LastTried = Dcurrent;
    //             clock_gettime(CLOCK_MONOTONIC,&current); Dcurrent = current.tv_sec + current.tv_nsec*0.000000001;

    //             port = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, 0);

    //             DCB dcbSerialParam = {0};
    //             dcbSerialParam.DCBlength = sizeof(dcbSerialParam);

    //             GetCommState(port, &dcbSerialParam);

    //             dcbSerialParam.BaudRate = CBR_9600;
    //             dcbSerialParam.ByteSize = 8;
    //             dcbSerialParam.StopBits = ONESTOPBIT;
    //             dcbSerialParam.Parity = NOPARITY;

    //             SetCommState(port, &dcbSerialParam);

    //             COMMTIMEOUTS timeout = {0}; //no timeout exept a small one for write
    //             timeout.ReadIntervalTimeout = 0;
    //             timeout.ReadTotalTimeoutConstant = 0;
    //             timeout.ReadTotalTimeoutMultiplier = 0;
    //             timeout.WriteTotalTimeoutMultiplier = 0;
    //             timeout.WriteTotalTimeoutConstant = 50;
    //             SetCommTimeouts(port, &timeout);

    //             ports[*((int*)arg)-1] = port;
    //         }
    //     }
    // }
    #endif
}

void writePorts(int toWrite, int isCF_GM) {
    #ifdef _WIN32

    // BYTE buffer = toWrite;
    // DWORD dwWrite = 0;
    // int portIndexes[10] = {-1};
    // int numPorts = 0;
    // if(isCF_GM) {
    //     for (int i = 0; i<10; i++) {
    //         if (ports[i] != INVALID_HANDLE_VALUE) {
    //             portIndexes[numPorts] = i;
    //             numPorts++;
    //         }
    //     }
    //     for (int i = 0; i < numPorts; i++) {
    //         if (i%2 == 0) {buffer = 0; WriteFile(ports[portIndexes[i]] , &buffer, 1, &dwWrite, NULL);}
    //         else {buffer = 1; WriteFile(ports[portIndexes[i]] , &buffer, 1, &dwWrite, NULL);}
    //     }
    // }

    // for (int i = 0; i<10; i++) {
    //     if (ports[i] != INVALID_HANDLE_VALUE) {
    //         WriteFile(ports[i] , &buffer, 1, &dwWrite, NULL);
    //     }
    // }

    #endif
}