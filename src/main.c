#define VERSION "0.3.25-alpha"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

#include "utils.h"
#include "gui.h"
#include"controlsGUI.h"
#include"scoresGUI.h"
#include"startSound.h"
#include"stopSound.h"

#include "raylib.h"

//todo
//add err msg telling people to reload ports

_Atomic int gamemodeIndex = 0;
//0 = CF
//1 = WM
//2 = M
// 3 = A

Sound startSound;
Sound stopSound;

int page = 0; 
//0 = game menu
//1 = saving score
//2 = scores

int CF_NumOfScores = 0;
int WM_NumOfScores = 0;
int M_NumOfScores = 0;
int A_NumOfScores = 0;

struct CF_scoresStruct* CF_Scores;
struct WM_scoresStruct* WM_Scores;
struct M_scoresStruct* M_Scores;
struct A_scoresStruct* A_Scores;

_Atomic int isBooting = 1;

int main() {

    #ifdef _WIN32
        setupPorts();
    #endif

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600,900,"Beacon Console");
    SetTargetFPS(60);

    InitAudioDevice();

    Wave startWav = LoadWaveFromMemory(".mp3",__assets_start_mp3,__assets_start_mp3_len);
    startSound = LoadSoundFromWave(startWav);

    Wave stopWav = LoadWaveFromMemory(".mp3",__assets_stop_mp3,__assets_stop_mp3_len);
    stopSound = LoadSoundFromWave(stopWav);

    while (!WindowShouldClose()) {

        //start rendering
        BeginDrawing();

        ClearBackground(WHITE);

        DrawText(VERSION,10,GetScreenHeight()-(GetScreenWidth()/175)/2 -10,GetScreenWidth()/175,BLACK);

        if (page == 0) {
            if (gamemodeIndex == 0) renderCF();
            if (gamemodeIndex == 1) renderWM();
            if (gamemodeIndex == 2) renderM();
            // if (gamemodeIndex == 3) renderA();
            renderControls();
        } else if (page == 1) {
            renderSaveScore();
        } else if (page == 2) {
            renderScores();
        }

        EndDrawing();
    }

    UnloadSound(startSound);
    UnloadSound(stopSound);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}