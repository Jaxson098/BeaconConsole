// #include "cJSON.h"
#include <pthread.h>

struct countersStruct {
	_Atomic int CF_B;
	_Atomic int CF_R;
	_Atomic int WM_G;
	_Atomic int M_B;
	_Atomic int M_G;
	_Atomic int M_Y;
	_Atomic int M_R;
	_Atomic int M_P;
	_Atomic int MWM_score; //the actual score, idk why its called MWM but im sure i had a reason
	_Atomic int numOpenPorts;
	_Atomic int M_colorIndex;
	_Atomic int M_potentialPoints;
};

extern struct countersStruct counters;

extern char gamemode[3];
extern pthread_mutex_t gamemode_lock;

extern char open_ports[10][255];

extern _Atomic int GM_changedFlag;
extern _Atomic int running;

void* updateOpenPorts(void* arg);

void* updateJSON(void* arg);

void* serialCom(void* arg);