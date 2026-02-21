#define VERSION "0.1.0-alpha"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include<stdlib.h>

#include "utils.h"
#include "gui.h"
#include"controlsGUI.h"
#include"scoresGUI.h"
#include "raylib.h"
#include"startSound.h"
#include"stopSound.h"

//todo
//re write utils.c to use WINapi (see https://www.delftstack.com/howto/cpp/cpp-serial-communication/)
//a bunch of threads constantly read from ports 3-13
//main thread ctrls sending gm and writing in general via a for loop on an arr of ports
//setup csv saving for scores

char gamemode[3] = "CF";
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

        // pthread_t thread_updateOpenPorts;

    // pthread_create(&thread_updateOpenPorts,NULL,updateOpenPorts,NULL);

    // pthread_t readers[10];
    // int ids[10];

    // for (int i = 0; i<10; i++) {
    //     ids[i] = i;
    //     pthread_create(&readers[i],NULL,serialCom,&ids[i]);
    // }
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

        // current = time(NULL);
        // char time[255];
        // sprintf(time,"%.f",difftime(current,start));
        // DrawText(time,200,200,30,BLACK);

        //stop rendering and replace last frame
        EndDrawing();
    }

    UnloadSound(startSound);
    UnloadSound(stopSound);
    CloseAudioDevice();

    CloseWindow();
    
    // while(1) {
    //     char command[4];
    //     fgets(command,4,stdin);

    //     if (strcmp(command,"CF\n") == 0) {
    //         printf("changed to CF");
    //         pthread_mutex_lock(&gamemode_lock);
    //         strcpy(gamemode,"CF");
    //         pthread_mutex_unlock(&gamemode_lock);
    //         if (GM_changedFlag == 0) {GM_changedFlag = 1;} else {GM_changedFlag = 0;}
    //     }
    //     else if (strcmp(command,"WM\n") == 0) {
    //         printf("changed to WM");
    //         pthread_mutex_lock(&gamemode_lock);
    //         strcpy(gamemode,"WM");
    //         pthread_mutex_unlock(&gamemode_lock);
    //         if (GM_changedFlag == 0) {GM_changedFlag = 1;} else {GM_changedFlag = 0;}
    //     }
    //     else if (strcmp(command,"M\n") == 0) {
    //         printf("changed to M");
    //         pthread_mutex_lock(&gamemode_lock);
    //         strcpy(gamemode,"M");
    //         pthread_mutex_unlock(&gamemode_lock);
    //         if (GM_changedFlag == 0) {GM_changedFlag = 1;} else {GM_changedFlag = 0;}
    //     }
    // }
    return 0;
}