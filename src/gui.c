#define _POSIX_C_SOURCE 199309L

#include "raylib.h"
#include "utils.h"
#include "gui.h"

#include<stdio.h>
#include<string.h>
// #include<stdlib.h>
#include<time.h>

char colors[5][255] = {"Blue","Green","Yellow","Red","Purple"};

Color blackTrans = { 0, 0, 0, 50 };

void renderCF() {
    ClearBackground(WHITE);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int textSize =  screenWidth/25;

    Rectangle blueRect = { 20, 20, (screenWidth/2)-30, (screenHeight/2)-30 };
    Rectangle redRect = { (screenWidth/2)+10, 20, (screenWidth/2)-30, (screenHeight/2)-30 };

    DrawRectangleRec(blueRect,BLUE);
    DrawRectangleRec(redRect,RED);

    DrawRectangleLinesEx(blueRect,(float)(screenWidth/75),blackTrans);
    DrawRectangleLinesEx(redRect,(screenWidth/75),blackTrans);

    char buffer[8];
    
    char redScore[255];
    strcpy(redScore,"Red Team Score: ");
    sprintf(buffer,"%d",counters.CF_R);
    strcat(redScore,buffer);

    char blueScore[255];
    strcpy(blueScore,"Blue Team Score: ");
    sprintf(buffer,"%d",counters.CF_B);
    strcat(blueScore,buffer);


    //xpos = box x pos + half width - half text width
    DrawText(
        blueScore,
        blueRect.x + (blueRect.width/2) - (MeasureText(blueScore,textSize)/2),
        blueRect.y + (blueRect.height/2) - (textSize/2),
        textSize,
        BLACK
    );

    DrawText(
        redScore,
        redRect.x + (redRect.width/2) - (MeasureText(redScore,textSize)/2),
        redRect.y + (redRect.height/2) - (textSize/2),
        textSize,
        BLACK
    );
    

}

void renderWM() {
    ClearBackground(WHITE);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int textSize = screenWidth/25;

    Rectangle greenRect = { 20, 20, screenWidth-40, (screenHeight/2)-30 };

    DrawRectangleRec(greenRect,GREEN);

    DrawRectangleLinesEx(greenRect,(float)(screenWidth/75),blackTrans);

    char buffer[8];
    
    char score[255];
    strcpy(score,"Score: ");
    sprintf(buffer,"%d",counters.WM_G);
    strcat(score,buffer);

    DrawText(
        score,
        greenRect.x + (greenRect.width/2) - (MeasureText(score,textSize)/2),
        greenRect.y + (greenRect.height/2) - (textSize/2),
        textSize,
        BLACK
    );
}

void renderM() {
    ClearBackground(WHITE);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int textSize = screenWidth/25;

    Rectangle scoreRect = { 20, 20, (screenWidth/2)-30, (screenHeight/2)-30 };
    Rectangle colorRect = { (screenWidth/2)+10, 20, (screenWidth/2)-30, (screenHeight/2)-30 };

    DrawRectangleRec(scoreRect,GRAY);

    if (counters.M_colorIndex == 0) {DrawRectangleRec(colorRect,BLUE);}
    if (counters.M_colorIndex == 1) {DrawRectangleRec(colorRect,GREEN);}
    if (counters.M_colorIndex == 2) {DrawRectangleRec(colorRect,YELLOW);}
    if (counters.M_colorIndex == 3) {DrawRectangleRec(colorRect,RED);}
    if (counters.M_colorIndex == 4) {DrawRectangleRec(colorRect,PURPLE);}

    DrawRectangleLinesEx(scoreRect,(float)(screenWidth/75),blackTrans);
    DrawRectangleLinesEx(colorRect,(float)(screenWidth/75),blackTrans);

    char buffer[8];
    
    char score[255];
    strcpy(score,"Potential Points: ");
    sprintf(buffer,"%d",counters.M_potentialPoints);
    strcat(score,buffer);
    strcat(score,"\nScore: ");
    sprintf(buffer,"%d",counters.M_score);
    strcat(score,buffer);

    char color[255];
    strcpy(color,"Color: ");
    strcat(color,colors[counters.M_colorIndex]);

    DrawText(
        score,
        scoreRect.x + (scoreRect.width/2) - (MeasureText(score,textSize)/2),
        scoreRect.y + (scoreRect.height/2) - (textSize/2),
        textSize,
        BLACK
    );

    DrawText(
        color,
        colorRect.x + (colorRect.width/2) - (MeasureText(color,textSize)/2),
        colorRect.y + (colorRect.height/2) - (textSize/2),
        textSize,
        BLACK
    );
}

//altitude gm
void renderA() {
}

