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

extern char gamemode[3];

extern struct countersStruct counters;

extern char open_ports[10][1029];

// extern cJSON *json;

void* updateOpenPorts(void* arg);

void* updateJSON(void* arg);