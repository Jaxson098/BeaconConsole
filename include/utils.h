#include "cJSON.h"

struct countersStruct {
	_Atomic int CF_B;
	_Atomic int CF_R;
	_Atomic int WM_G;
	_Atomic int M_B;
	_Atomic int M_G;
	_Atomic int M_Y;
	_Atomic int M_R;
	_Atomic int M_P;
};

extern struct countersStruct counters;

extern char gamemode[3];

extern char open_ports[10][255];

void* updateOpenPorts(void* arg);

void* updateJSON(void* arg);

void* serialCom(void* arg);