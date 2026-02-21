#include"raylib.h"

void renderControls();
void renderSaveScore();

extern Sound stopSound;
extern Sound startSound;

extern int page;

struct CF_scoresStruct {
	char teamName1[255];
    char teamName2[255];
    int team1Score;
    int team2Score;
};

extern struct CF_scoresStruct* CF_Scores;
extern int CF_NumOfScores;

struct WM_scoresStruct {
	char teamName[255];
    int teamScore;
};

extern struct WM_scoresStruct* WM_Scores;
extern int WM_NumOfScores;

struct M_scoresStruct {
	char teamName[255];
    int teamScore;
};

extern struct M_scoresStruct* M_Scores;
extern int M_NumOfScores;

struct A_scoresStruct {
	char teamName[255];
    int teamScore;
};

extern struct A_scoresStruct* A_Scores;
extern int A_NumOfScores;
