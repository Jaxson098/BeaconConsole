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
	_Atomic int M_score;
	_Atomic int M_colorIndex;
	_Atomic int M_potentialPoints;
	_Atomic int A_points;
};
extern struct countersStruct counters;

extern _Atomic int gamemodeIndex;

extern _Atomic int GM_changedFlag;
extern _Atomic int running;
extern _Atomic int isBooting;
// extern int numberOfPorts;

void* portReader(void* arg);

void writePorts(
	int toWrite, 
	int isCF_GM //if true will ignore toWrite and write 1 to half the ports, and 0 to the other
);

void setupPorts();
void* writePortsThread(void* arg);