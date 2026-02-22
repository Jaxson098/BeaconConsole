// #include "cJSON.h"
#include <pthread.h>

#ifdef _WIN32
#include <windows.h>
extern HANDLE ports[10];
#endif

struct countersStruct {
	_Atomic int CF_B;
	_Atomic int CF_R;
	_Atomic int WM_G;
	_Atomic int M_B;
	_Atomic int M_G;
	_Atomic int M_Y;
	_Atomic int M_R;
	_Atomic int M_P;
	_Atomic int M_score;
	_Atomic int numOpenPorts; 
	_Atomic int M_colorIndex;
	_Atomic int M_potentialPoints;
	_Atomic int A_points;
};

extern struct countersStruct counters;

extern _Atomic int gamemodeIndex;

extern _Atomic int GM_changedFlag;
extern _Atomic int running;

void* portReader(void* arg);

void writePorts(
	int toWrite, 
	int isCF_GM //if true will ignore toWrite and write 1 to half the ports, and 0 to the other
);