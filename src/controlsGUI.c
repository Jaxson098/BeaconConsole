#define _POSIX_C_SOURCE 199309L

#include<raylib.h>
#include<gui.h>
#include<time.h>

struct timespec start;
double Dstart;

int framesCounter = 0;

char timeInput[6] = "01:30";
int timeInputCount = 0;

char underscoreArray[6] = "";

int nameInputCount;

Color blackTrans = { 0, 0, 0, 50 };

_Atomic int running = 0;
_Atomic int isTyping = 0;

int hasRanOnce = 0;

void renderControls() {
    ClearBackground(WHITE);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int textSize = screenWidth/20;

    struct timespec current;

    Vector2 mousePos = GetMousePosition();

    Rectangle timerRect = { (screenWidth/2)-(screenWidth/6), (screenHeight/2)+10, screenWidth/3, (screenHeight/4)-40 };
    Rectangle controlBtnRect = { 20, (screenHeight/2)+10, screenWidth/4, (screenHeight/4)-40 };

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

    //draw borders

    DrawRectangleLinesEx(timerRect,(float)(screenWidth/75),blackTrans);
    DrawRectangleLinesEx(controlBtnRect,(float)(screenWidth/75),blackTrans);

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
            if (!running) {running=1; if(hasRanOnce < 1){hasRanOnce++;} clock_gettime(CLOCK_MONOTONIC,&start); Dstart = start.tv_sec + start.tv_nsec*0.000000001;} else {running=0;}
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

        //stop if reached timeInput

        if (elapsed >= intTimeInputSecs) {
            PlaySound(stopSound);
            running = 0;
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
    } else {
        framesCounter = 0;
        isTyping = 0;
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

//
void renderSaveScore() {

}