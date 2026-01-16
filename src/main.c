#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#include "utils.h"
#include "gui.h"
#include"controlsGUI.h"
#include "raylib.h"

//on startup initialize all serial ports connected and put them in an object with their fd and path
//create a worker thread for each port
//create a monitoring thread to watch for disconected by comparing to the ports obj, and open new thread with a new fd
//have an atomic str be the msg needed to write updated by main()
//inside worker threads check if the str is equal to last written if not write the atomic string and change the local last written var
//on space click write whatever the json has as the game mode
//reset all vars to 0 and record
//another thread constantly writes counters to json on change
//on end write stop to all ports

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
//2 = scores for CF / brackets
//3 = scores for WM
//4 = scores for M
//5 = scores for A

int main() {
    // pthread_t thread_updateOpenPorts;

    // pthread_create(&thread_updateOpenPorts,NULL,updateOpenPorts,NULL);

    // pthread_t readers[10];
    // int ids[10];

    // for (int i = 0; i<10; i++) {
    //     ids[i] = i;
    //     pthread_create(&readers[i],NULL,serialCom,&ids[i]);
    // }

    InitWindow(1600,900,"Beacon Console");
    SetTargetFPS(60);

    InitAudioDevice();

    startSound = LoadSound("./assets/start.mp3");
    stopSound = LoadSound("./assets/stop.mp3");

    while (!WindowShouldClose()) {

        //start rendering
        BeginDrawing();

        if (page == 0) {
            renderCF();
            renderControls();
        } else if (page == 1) {
            renderSaveScore();
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