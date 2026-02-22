#define _POSIX_C_SOURCE 199309L

#include"raylib.h"
#include"gui.h"
#include"controlsGUI.h"
#include"utils.h"
#include<time.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

struct timespec start;
double Dstart;

int framesCounter = 0;
char underscoreArray[6] = "";

char timeInput[6] = "01:30";
int timeInputCount = 0;

_Atomic int running = 0;
int isTyping = 0;

int hasNewScore = 0;
int nameInputCount;

void renderControls() {
    ClearBackground(WHITE);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int textSize = screenWidth/20;
    int textSizeSmall = screenWidth/60;

    struct timespec current;

    Vector2 mousePos = GetMousePosition();

    Rectangle timerRect = { (screenWidth/2)-(screenWidth/6), (screenHeight/2)+10, screenWidth/3, (screenHeight/4)-40 };
    Rectangle controlBtnRect = { 20, (screenHeight/2)+10, screenWidth/4, (screenHeight/4)-40 };
    Rectangle saveBtnRect = { screenWidth - screenWidth/4 - 20, screenHeight/2 + 10, screenWidth/4, screenHeight/4 -40 };
    Rectangle CF_BtnRect = { 20, screenHeight*0.75 -10, screenWidth/6, screenHeight/6 };
    Rectangle WM_BtnRect = { 20+(screenWidth/6-(screenWidth/250)), screenHeight*0.75 -10, screenWidth/6, screenHeight/6 };
    Rectangle M_BtnRect = { 20+(screenWidth/6-(screenWidth/250))*2, screenHeight*0.75 -10, screenWidth/6, screenHeight/6 };
    Rectangle A_BtnRect = { 20+(screenWidth/6-(screenWidth/250))*3, screenHeight*0.75 -10, screenWidth/6, screenHeight/6 };

    Rectangle Scores_BtnRect = { screenWidth - screenWidth/4 - 20, screenHeight*0.75 -10, screenWidth/4, screenHeight/6 };;

    //to scores
    DrawRectangleRec(Scores_BtnRect,LIGHTGRAY);
    DrawRectangleLinesEx(Scores_BtnRect,(float)(screenWidth/100),blackTrans);
    DrawText(
        "Scores",
        Scores_BtnRect.x + (Scores_BtnRect.width/2) - (MeasureText("Scores",textSize)/2),
        Scores_BtnRect.y + (Scores_BtnRect.height/2) - (textSize/2),
        textSize,
        BLACK
    );

    if (CheckCollisionPointRec(mousePos,Scores_BtnRect) && !running) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            DrawRectangleRec(Scores_BtnRect,blackTrans);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            page = 2;
        }
    }

    //gamemode switcher:
    DrawRectangleRec(CF_BtnRect,(gamemodeIndex == 0) ? LIGHTGRAY : GRAY);
    DrawRectangleRec(WM_BtnRect,(gamemodeIndex == 1) ? LIGHTGRAY : GRAY);
    DrawRectangleRec(M_BtnRect,(gamemodeIndex == 2) ? LIGHTGRAY : GRAY);
    DrawRectangleRec(A_BtnRect,(gamemodeIndex == 3) ? LIGHTGRAY : GRAY);

    DrawRectangleLinesEx(CF_BtnRect,(float)(screenWidth/100),blackTrans);
    DrawRectangleLinesEx(CF_BtnRect,(float)(screenWidth/250),BLACK);
    DrawRectangleLinesEx(WM_BtnRect,(float)(screenWidth/100),blackTrans);
    DrawRectangleLinesEx(WM_BtnRect,(float)(screenWidth/250),BLACK);
    DrawRectangleLinesEx(M_BtnRect,(float)(screenWidth/100),blackTrans);
    DrawRectangleLinesEx(M_BtnRect,(float)(screenWidth/250),BLACK);
    DrawRectangleLinesEx(A_BtnRect,(float)(screenWidth/100),blackTrans);
    DrawRectangleLinesEx(A_BtnRect,(float)(screenWidth/250),BLACK);

    DrawText(
        "Capture The Flag",
        CF_BtnRect.x + (CF_BtnRect.width/2) - (MeasureText("Capture The Flag",textSizeSmall)/2),
        CF_BtnRect.y + (CF_BtnRect.height/2) - (textSizeSmall/2),
        textSizeSmall,
        BLACK
    );

    DrawText(
        "Wack-A-Mole",
        WM_BtnRect.x + (WM_BtnRect.width/2) - (MeasureText("Wack-A-Mole",textSizeSmall)/2),
        WM_BtnRect.y + (WM_BtnRect.height/2) - (textSizeSmall/2),
        textSizeSmall,
        BLACK
    );

    DrawText(
        "Memory",
        M_BtnRect.x + (M_BtnRect.width/2) - (MeasureText("Memory",textSizeSmall)/2),
        M_BtnRect.y + (M_BtnRect.height/2) - (textSizeSmall/2),
        textSizeSmall,
        BLACK
    );

    DrawText(
        "Altitude",
        A_BtnRect.x + (A_BtnRect.width/2) - (MeasureText("Altitude",textSizeSmall)/2),
        A_BtnRect.y + (A_BtnRect.height/2) - (textSizeSmall/2),
        textSizeSmall,
        BLACK
    );

    if (CheckCollisionPointRec(mousePos,CF_BtnRect) && gamemodeIndex != 0 && !running) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            DrawRectangleRec(CF_BtnRect,blackTrans);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            gamemodeIndex = 0;
            running = 0;
        }
    }

    if (CheckCollisionPointRec(mousePos,WM_BtnRect) && gamemodeIndex != 1 && !running) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            DrawRectangleRec(WM_BtnRect,blackTrans);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            gamemodeIndex = 1;
            running = 0;
        }
    }

    if (CheckCollisionPointRec(mousePos,M_BtnRect) && gamemodeIndex != 2 && !running) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            DrawRectangleRec(M_BtnRect,blackTrans);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            gamemodeIndex = 2;
            running = 0;
        }
    }

    if (CheckCollisionPointRec(mousePos,A_BtnRect) && gamemodeIndex != 3 && !running) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            DrawRectangleRec(A_BtnRect,blackTrans);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            gamemodeIndex = 3;
            running = 0;
        }
    }

    DrawRectangleRec(timerRect,GRAY);

    //set control buttom to be start or stop based on running

    char controlBtnText[255];
    if (!running) {DrawRectangleRec(controlBtnRect,GREEN); strcpy(controlBtnText,"Start");}
    if (running) {DrawRectangleRec(controlBtnRect,RED);strcpy(controlBtnText,"Stop");}

    DrawText(
        controlBtnText,
        controlBtnRect.x + (controlBtnRect.width/2) - (MeasureText(controlBtnText,textSize)/2),
        controlBtnRect.y + (controlBtnRect.height/2) - (textSize/2),
        textSize,
        BLACK
    );

    DrawRectangleRec(saveBtnRect,GREEN);

    DrawText(
        "Save\nScore",
        saveBtnRect.x + (saveBtnRect.width/2) - (MeasureText("Save\nScore",screenWidth/25)/2),
        saveBtnRect.y + (saveBtnRect.height/2) - (screenWidth/25),
        screenWidth/25,
        BLACK
    );

    //draw borders

    DrawRectangleLinesEx(timerRect,(float)(screenWidth/75),blackTrans);
    DrawRectangleLinesEx(controlBtnRect,(float)(screenWidth/75),blackTrans);
    DrawRectangleLinesEx(saveBtnRect,(float)(screenWidth/75),blackTrans);

    //handle save score btn functionality

    if (!hasNewScore) {
        DrawRectangleRec(saveBtnRect,blackTrans);
    } else {
        if (CheckCollisionPointRec(mousePos,saveBtnRect)) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                DrawRectangleRec(saveBtnRect,blackTrans);
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                page = 1;
                return;
            }
        }
    }

    //control button functionality, change running status

    if (CheckCollisionPointRec(mousePos,controlBtnRect)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            DrawRectangleRec(controlBtnRect,blackTrans);
        }
        //if relesed this frame
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            PlaySound(startSound);
            //clock_gettime(CLOCK_MONOTONIC, &start) gets the time in seconds in nano seconds since boot 
            //(what monotonic means, realtime would be since epoch) and applies it to start struct
            if (!running) {running=1; hasNewScore = 0; clock_gettime(CLOCK_MONOTONIC,&start); Dstart = start.tv_sec + start.tv_nsec*0.000000001;} else {running=0;}
        }
    }

    //timer functionality and stop functionality

    if (running) {
        //clock_gettime(CLOCK_MONOTONIC, &current) gets the time in seconds in nano seconds since boot 
        //(what monotonic means, realtime would be since epoch) and applies it to current struct
        clock_gettime(CLOCK_MONOTONIC,&current);
        double Dcurrent = current.tv_sec + current.tv_nsec*0.000000001;
        double elapsed = Dcurrent-Dstart;

        //converts the timeInput string to seconds, 
        int intTimeInputSecs = ((timeInput[0]-48)*10 + (timeInput[1]-48))*60 + (timeInput[3]-48)*10 + (timeInput[4]-48);

        int timeLeft = intTimeInputSecs - elapsed;

        //convert timeLeft into a string displayTime

        char buffer[3];
        char displayTime[6];

        if (timeLeft/60 < 10) {
            sprintf(buffer,"%d",0);
            strcpy(displayTime,buffer);
            sprintf(buffer,"%d",timeLeft/60);
            strcat(displayTime,buffer);
        } else {
            sprintf(buffer,"%d",timeLeft/60);
            strcpy(displayTime,buffer);
        }
        
        strcat(displayTime,":");

        if (timeLeft%60 < 10) {
            sprintf(buffer,"%d",0);
            strcat(displayTime,buffer);
            sprintf(buffer,"%d",timeLeft%60);
            strcat(displayTime,buffer);
        } else {
            sprintf(buffer,"%d",timeLeft%60);
            strcat(displayTime,buffer);
        }

        //stop if reached unde

        if (elapsed >= intTimeInputSecs) {
            PlaySound(stopSound);
            running = 0;
            hasNewScore = 1;
        } else {
            //otherwise display time, in else beacase dont want to display it for a split second and then stop
            DrawText(
                displayTime,
                timerRect.x + (timerRect.width/2) - (MeasureText(displayTime,textSize)/2),
                timerRect.y + (timerRect.height/2) - (textSize/2),
                textSize,
                BLACK
            );
        } //if your not running and not typing a new input just staticly display the timeInput
    } else {
        DrawText(
            timeInput,
            timerRect.x + (timerRect.width/2) - (MeasureText(timeInput,textSize)/2),
            timerRect.y + (timerRect.height/2) - (textSize/2),
            textSize,
            BLACK
        );
    }

    //handle typing input
    if (CheckCollisionPointRec(mousePos,timerRect) && !running) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            strcpy(timeInput,"00:00");
            isTyping = 1;
            timeInputCount = 0;
        }
        if (isTyping) {
            framesCounter++;

            int startPoint = timerRect.x + (timerRect.width/2) - (MeasureText(timeInput,textSize)/2);

            if((framesCounter/20)%2 == 0 && timeInputCount < 5) {
                DrawText(
                    "_",
                    startPoint + MeasureText(underscoreArray,textSize),
                    timerRect.y + (timerRect.height/2) - (textSize/2) + 10,
                    textSize,
                    BLACK
                );
            }

            int key = GetCharPressed();
            while (key > 0 && timeInputCount <= 4) {
                if ((key >= 48) && (key <= 57)) {

                    if (timeInputCount == 2) {
                        timeInput[timeInputCount+1] = (char)key;
                        timeInputCount = timeInputCount + 2;
                    } else {
                        timeInput[timeInputCount] = (char)key;
                        timeInputCount++;
                    }

                    //handle _ measurement

                    for (int i = 0; i<6; i++) {
                        underscoreArray[i] = (char)0;
                    }
                    for (int i = 0; i<timeInputCount; i++) {
                        underscoreArray[i] = timeInput[i];
                    }
                    if (timeInputCount == 2) {
                        underscoreArray[2] = ':';
                    }
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (timeInputCount > 0) {
                    if (timeInputCount == 3) {
                        timeInput[timeInputCount-2] = '0';
                        timeInputCount = timeInputCount - 2;
                    } else {
                        timeInput[timeInputCount-1] = '0';
                        timeInputCount--;
                    }

                    //handle _ measurment

                    for (int i = 0; i<6; i++) {
                        underscoreArray[i] = (char)0;
                    }
                    for (int i = 0; i<timeInputCount; i++) {
                        underscoreArray[i] = timeInput[i];
                    }
                    if (timeInputCount == 2) {
                        underscoreArray[3] = ':';
                    }
                }
            }
        }
    } else if (isTyping) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        framesCounter = 0;
        isTyping = 0;
        for (int i = 0; i<6; i++) {
            underscoreArray[i] = (char)0;
        }
    }
}

char teamName[255];
char teamName1[255];
char teamName2[255];

int charInputCount = 0;

void renderSaveScore() {
    ClearBackground(WHITE);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int titleTextSize = screenWidth/15;
    int textSize = screenWidth/20;

    Vector2 mousePos = GetMousePosition();

    Rectangle cancelBtnRect = { 0, 0, screenWidth/10, screenHeight/10 };
    Rectangle saveBtnRect = { screenWidth-screenWidth/10, 0, screenWidth/10, screenHeight/10 };
    Rectangle teamNameRect = { screenWidth*0.125, screenHeight/2, screenWidth*0.75, screenHeight/5 };
    Rectangle teamName1Rect = { screenWidth*0.05, screenHeight/2, screenWidth*0.425, screenHeight/5 };
    Rectangle teamName2Rect = { screenWidth*0.525, screenHeight/2, screenWidth*0.425, screenHeight/5 };

    if (gamemodeIndex == 0) {
        DrawRectangleRec(teamName1Rect,RED);
        DrawRectangleRec(teamName2Rect, BLUE);
        DrawRectangleLinesEx(teamName1Rect,(float)(screenWidth/75),blackTrans);
        DrawRectangleLinesEx(teamName2Rect,(float)(screenWidth/75),blackTrans);
        DrawText(
            "Enter Team Names:",
            screenWidth/2 - MeasureText("Enter Team Names:",titleTextSize)/2,
            screenHeight/3 - (titleTextSize/2),
            titleTextSize,
            BLACK
        );
        //name rendering
        DrawText(
            teamName1,
            teamName1Rect.x + screenWidth/75+10,
            teamName1Rect.y + (teamName1Rect.height/2) - (textSize/2),
            textSize,
            BLACK
        );
        DrawText(
            teamName2,
            teamName2Rect.x + screenWidth/75+10,
            teamName2Rect.y + (teamName2Rect.height/2) - (textSize/2),
            textSize,
            BLACK
        );
    } else {
        DrawRectangleRec(teamNameRect,GREEN);
        DrawRectangleLinesEx(teamNameRect,(float)(screenWidth/75),blackTrans);
        DrawText(
            "Enter Team Name:",
            screenWidth/2 - MeasureText("Enter Team Name:",titleTextSize)/2,
            screenHeight/3 - (titleTextSize/2),
            titleTextSize,
            BLACK
        );   
        DrawText(
            teamName,
            teamNameRect.x + screenWidth/75+10,
            teamNameRect.y + (teamNameRect.height/2) - (textSize/2),
            textSize,
            BLACK
        );
    }
    
    DrawRectangleRec(cancelBtnRect,RED);
    DrawText(
        "Cancel",
        cancelBtnRect.x + (cancelBtnRect.width/2) - (MeasureText("Cancel",screenWidth/35)/2),
        cancelBtnRect.y + (cancelBtnRect.height/2) - ((screenWidth/35)/2),
        screenWidth/35,
        BLACK
    );
    DrawRectangleLinesEx(cancelBtnRect,(float)(screenWidth/100),blackTrans);
    if (CheckCollisionPointRec(mousePos,cancelBtnRect)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            DrawRectangleRec(cancelBtnRect,blackTrans);
        }
        //if relesed this frame
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            strcpy(teamName,"");
            strcpy(teamName1,"");
            strcpy(teamName2,"");
            page = 0;
            return;
        }
    }

    DrawRectangleRec(saveBtnRect,GREEN);
    DrawText(
        "Save",
        saveBtnRect.x + (saveBtnRect.width/2) - (MeasureText("Save",screenWidth/35)/2),
        saveBtnRect.y + (saveBtnRect.height/2) - ((screenWidth/35)/2),
        screenWidth/35,
        BLACK
    );
    DrawRectangleLinesEx(saveBtnRect,(float)(screenWidth/100),blackTrans);
    if (CheckCollisionPointRec(mousePos,saveBtnRect)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            DrawRectangleRec(saveBtnRect,blackTrans);
        }
        //if relesed this frame
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (gamemodeIndex == 0) {
                CF_NumOfScores++;
                CF_Scores = realloc(CF_Scores,CF_NumOfScores * sizeof(struct CF_scoresStruct));
                struct CF_scoresStruct CFscore;
                strcpy(CFscore.teamName1,teamName1);
                strcpy(CFscore.teamName2,teamName2);
                CFscore.team1Score=counters.CF_B;
                CFscore.team2Score=counters.CF_R;
                CF_Scores[CF_NumOfScores-1] = CFscore;
                writePorts(0,1);
            }

            if (gamemodeIndex == 1) {
                WM_NumOfScores++;
                WM_Scores = realloc(WM_Scores,WM_NumOfScores * sizeof(struct WM_scoresStruct));
                struct WM_scoresStruct WMscore;
                strcpy(WMscore.teamName,teamName);
                WMscore.teamScore=counters.WM_G;
                WM_Scores[WM_NumOfScores-1] = WMscore;
                writePorts(2,0);
            }
            if (gamemodeIndex == 2) {
                M_NumOfScores++;
                M_Scores = realloc(M_Scores,M_NumOfScores * sizeof(struct M_scoresStruct));
                struct M_scoresStruct Mscore;
                strcpy(Mscore.teamName,teamName);
                Mscore.teamScore=counters.M_score;
                M_Scores[M_NumOfScores-1] = Mscore;
                writePorts(3,0);
            }
            if (gamemodeIndex == 3) {
                A_NumOfScores++;
                A_Scores = realloc(A_Scores,A_NumOfScores * sizeof(struct A_scoresStruct));
                struct A_scoresStruct Ascore;
                strcpy(Ascore.teamName,teamName);
                Ascore.teamScore=counters.A_points;
                A_Scores[A_NumOfScores-1] = Ascore;
                writePorts(4,0);
            }
            strcpy(teamName,"");
            strcpy(teamName1,"");
            strcpy(teamName2,"");
            page = 2;
            return;
        }
    }

    //CF name inputs:
    if (gamemodeIndex == 0) {
        if (CheckCollisionPointRec(mousePos,teamName1Rect)) {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                strcpy(teamName1,"");
                charInputCount = 0;
                isTyping = 1;
            }
            if (isTyping) {
                framesCounter++;

                // int startPoint = teamName1Rect.x + screenWidth;

                if((framesCounter/20)%2 == 0 && MeasureText(teamName1,textSize) < (int)teamName1Rect.width - ((screenWidth/75+10)*2 + MeasureText("_",textSize))) {
                    DrawText(
                        "_",
                        teamName1Rect.x + screenWidth/75 + MeasureText(teamName1,textSize) + screenWidth/80, // + screenWidth/80 prevents touching prev char
                        teamName1Rect.y + (teamName1Rect.height/2) - (textSize/2),
                        textSize,
                        BLACK
                    );
                }

                int key = GetCharPressed();
                while (key > 0 && MeasureText(teamName1,textSize) < (int)teamName1Rect.width - ((screenWidth/75+10)*2 + MeasureText("_",textSize))) {
                    if ((key >= 32) && (key <= 126)) {
                        teamName1[charInputCount] = (char)key;
                        teamName1[charInputCount+1] = '\0'; //null terminator
                        charInputCount++;
                    }
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (charInputCount > 0) {
                        charInputCount--;
                        teamName1[charInputCount] = '\0';
                    }
                }
            }
        } else if (CheckCollisionPointRec(mousePos,teamName2Rect)) {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                strcpy(teamName2,"");
                charInputCount = 0;
                isTyping = 1;
            }
            if (isTyping) {
                framesCounter++;

                if((framesCounter/20)%2 == 0 && MeasureText(teamName2,textSize) < (int)teamName2Rect.width - ((screenWidth/75+10)*2 + MeasureText("_",textSize))) {
                    // printf("_\n");
                    DrawText(
                        "_",
                        teamName2Rect.x + screenWidth/75 + MeasureText(teamName2,textSize) + screenWidth/80, // + screenWidth/80 prevents touching prev char
                        teamName2Rect.y + (teamName2Rect.height/2) - (textSize/2),
                        textSize,
                        BLACK
                    );
                }

                int key = GetCharPressed();
                while (key > 0 && MeasureText(teamName2,textSize) < (int)teamName2Rect.width - ((screenWidth/75+10)*2 + MeasureText("_",textSize))) {
                    if ((key >= 32) && (key <= 126)) {
                        teamName2[charInputCount] = (char)key;
                        teamName2[charInputCount+1] = '\0'; //null terminator
                        charInputCount++;
                    }
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (charInputCount > 0) {
                        charInputCount--;
                        teamName2[charInputCount] = '\0';
                    }
                }
            }
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            framesCounter = 0;
            isTyping = 0;
        }
    } else { //other name input
        if (CheckCollisionPointRec(mousePos,teamNameRect)) {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                strcpy(teamName,"");
                charInputCount = 0;
                isTyping = 1;
            }
            if (isTyping) {
                framesCounter++;

                // int startPoint = teamName1Rect.x + screenWidth;

                if((framesCounter/20)%2 == 0 && MeasureText(teamName,textSize) < (int)teamNameRect.width - ((screenWidth/75+10)*2 + MeasureText("_",textSize))) {
                    DrawText(
                        "_",
                        teamNameRect.x + screenWidth/75 + MeasureText(teamName,textSize) + screenWidth/80, // + screenWidth/80 prevents touching prev char
                        teamNameRect.y + (teamNameRect.height/2) - (textSize/2),
                        textSize,
                        BLACK
                    );
                }

                int key = GetCharPressed();
                while (key > 0 && MeasureText(teamName,textSize) < (int)teamNameRect.width - ((screenWidth/75+10)*2 + MeasureText("_",textSize))) {
                    if ((key >= 32) && (key <= 126)) {
                        teamName[charInputCount] = (char)key;
                        teamName[charInputCount+1] = '\0'; //null terminator
                        charInputCount++;
                    }
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (charInputCount > 0) {
                        charInputCount--;
                        teamName[charInputCount] = '\0';
                    }
                }
            }
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            framesCounter = 0;
            isTyping = 0;
        }
    }
}