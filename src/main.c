#define VERSION "0.2.0-alpha"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include<stdlib.h>

#include "utils.h"
#include "gui.h"
#include"controlsGUI.h"
#include"scoresGUI.h"
#include"startSound.h"
#include"stopSound.h"

#include "raylib.h"

//todo
//re write utils.c to use WINapi (see https://www.delftstack.com/howto/cpp/cpp-serial-communication/)
//a bunch of threads constantly read from ports 3-13
//main thread ctrls sending gm and writing in general via a for loop on an arr of ports
//setup csv saving for scores

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

int main() {

    #ifdef _WIN32
    pthread_t thread_portReader;

    for (int i = 0; i<10; i++) {
        pthread_create(&thread_portReader,NULL,portReader,(void*)(intptr_t)i);
    }
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

        DrawText(VERSION,15,GetScreenHeight()-35,20,BLACK);

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