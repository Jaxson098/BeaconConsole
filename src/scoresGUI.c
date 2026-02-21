#include"raylib.h"
#include"gui.h"
#include"controlsGUI.h"
#include<stdio.h>
#include<stdlib.h>

int CF_scrollOffset = 0;
int WM_scrollOffset = 0;
int M_scrollOffset = 0;
int A_scrollOffset = 0;

void renderScores() {
    ClearBackground(WHITE);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int textSize = screenWidth/20;

    Vector2 mousePos = GetMousePosition();

    Rectangle toCtrlsRect = { (int)(screenWidth*0.005), (int)(screenHeight*0.005), (int)(screenWidth*0.04), (int)(screenHeight*0.04) };
    Rectangle CFrect = { (int)(screenWidth*0.05), (int)(screenHeight*0.05), (int)(screenWidth*0.425), (int)(screenHeight*0.425) };
    Rectangle WMrect = { (int)(screenWidth*0.525), (int)(screenHeight*0.05), (int)(screenWidth*0.425), (int)(screenHeight*0.425) };
    Rectangle Mrect = { (int)(screenWidth*0.05), (int)(screenHeight*0.525), (int)(screenWidth*0.425), (int)(screenHeight*0.425) };
    Rectangle Arect = { (int)(screenWidth*0.525), (int)(screenHeight*0.525), (int)(screenWidth*0.425), (int)(screenHeight*0.425) };

    DrawRectangleLinesEx(CFrect,screenWidth/250,BLACK);
    DrawRectangleLinesEx(WMrect,screenWidth/250,BLACK);
    DrawRectangleLinesEx(Mrect,screenWidth/250,BLACK);
    DrawRectangleLinesEx(Arect,screenWidth/250,BLACK);

    //titles
    DrawText(
        "Capture The Flag",
        CFrect.x + (CFrect.width/2) - (MeasureText("Capture The Flag",screenWidth/50)/2),
        CFrect.y - (screenWidth/45),
        screenWidth/50,
        BLACK
    );
    DrawText(
        "Wack-A-Mole",
        WMrect.x + (WMrect.width/2) - (MeasureText("Wack-A-Mole",screenWidth/50)/2),
        WMrect.y - (screenWidth/45),
        screenWidth/50,
        BLACK
    );
    DrawText(
        "Memory",
        Mrect.x + (Mrect.width/2) - (MeasureText("Memory",screenWidth/50)/2),
        Mrect.y - (screenWidth/45),
        screenWidth/50,
        BLACK
    );
    DrawText(
        "Altitude",
        Arect.x + (Arect.width/2) - (MeasureText("Altitude",screenWidth/50)/2),
        Arect.y - (screenWidth/45),
        screenWidth/50,
        BLACK
    );

    //return to ctrls btn
    DrawRectangleRec(toCtrlsRect,RED);
    DrawText(
        "Done",
        toCtrlsRect.x + (toCtrlsRect.width/2) - (MeasureText("Done",screenWidth/75)/2),
        toCtrlsRect.y + (toCtrlsRect.height/2) - ((screenWidth/75)/2),
        screenWidth/75,
        BLACK
    );
    DrawRectangleLinesEx(toCtrlsRect,(float)(screenWidth/250),blackTrans);
    if (CheckCollisionPointRec(mousePos,toCtrlsRect)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            DrawRectangleRec(toCtrlsRect,blackTrans);
        }
        //if relesed this frame
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            page = 0;
            return;
        }
    }

    int rowHeight = screenHeight*0.025;
    int border = (screenWidth/250.0);
    int wheel = (int)GetMouseWheelMove();

    if(CheckCollisionPointRec(mousePos,CFrect)) CF_scrollOffset -= wheel * rowHeight;
    if(CheckCollisionPointRec(mousePos,WMrect)) WM_scrollOffset -= wheel * rowHeight;
    if(CheckCollisionPointRec(mousePos,Mrect)) M_scrollOffset -= wheel * rowHeight;
    if(CheckCollisionPointRec(mousePos,Arect)) A_scrollOffset -= wheel * rowHeight;

    //draw CF rows
    BeginScissorMode(
        (int)CFrect.x + border,
        (int)CFrect.y + border,
        (int)CFrect.width - border*2,
        (int)CFrect.height - border*2
    );
    for (int i = 0; i<CF_NumOfScores; i++) {

        int columnWidth = CFrect.width/4;

        if (CF_scrollOffset > CF_NumOfScores*rowHeight - (CFrect.height)) CF_scrollOffset = CF_NumOfScores*rowHeight - (CFrect.height);
        if (CF_scrollOffset < 0) CF_scrollOffset = 0;

        int y = (int)CFrect.y + border + i * rowHeight - CF_scrollOffset;

        if (y + rowHeight < (int)CFrect.y || y > (int)CFrect.y + (int)CFrect.height) continue;

        // Alternate row colors
        Color rowColor = (i % 2 == 0) ? LIGHTGRAY : WHITE;
        DrawRectangle((int)CFrect.x, y, (int)CFrect.width, rowHeight, rowColor);

        // Draw columns
        for (int c = 0; c < 4; c++) {
            int x = (int)CFrect.x + c * columnWidth;
            Rectangle box = {x, y, columnWidth, rowHeight};
            DrawRectangleLinesEx(box,screenWidth/1000, BLACK);

            char text[255];

            if (c == 0) sprintf(text,"%s",CF_Scores[i].teamName1);
            if (c == 1) sprintf(text,"%d",CF_Scores[i].team1Score);
            if (c == 2) sprintf(text,"%s",CF_Scores[i].teamName2);
            if (c == 3) sprintf(text,"%d",CF_Scores[i].team2Score);

            DrawText(text, x+5+border, y, screenWidth/75, BLACK);
        }
    }
    EndScissorMode();

    //draw WM rows
    BeginScissorMode(
        (int)WMrect.x + border,
        (int)WMrect.y + border,
        (int)WMrect.width - border*2,
        (int)WMrect.height - border*2
    );
    for (int i = 0; i<WM_NumOfScores; i++) {

        int columnWidth = WMrect.width/2;

        if (WM_scrollOffset > WM_NumOfScores*rowHeight - (WMrect.height)) WM_scrollOffset = WM_NumOfScores*rowHeight - (WMrect.height);
        if (WM_scrollOffset < 0) WM_scrollOffset = 0;

        int y = (int)WMrect.y + border + i * rowHeight - WM_scrollOffset;

        if (y + rowHeight < (int)WMrect.y || y > (int)WMrect.y + (int)WMrect.height) continue;

        // Alternate row colors
        Color rowColor = (i % 2 == 0) ? LIGHTGRAY : WHITE;
        DrawRectangle((int)WMrect.x, y, (int)WMrect.width, rowHeight, rowColor);

        // Draw columns
        for (int c = 0; c < 2; c++) {
            int x = (int)WMrect.x + c * columnWidth;
            Rectangle box = {x, y, columnWidth, rowHeight};
            DrawRectangleLinesEx(box,screenWidth/1000, BLACK);

            char text[255];

            if (c == 0) sprintf(text,"%s",WM_Scores[i].teamName);
            if (c == 1) sprintf(text,"%d",WM_Scores[i].teamScore);

            DrawText(text, x+5+border, y, screenWidth/75, BLACK);
        }
    }
    EndScissorMode();

    //draw M rows
    BeginScissorMode(
        (int)Mrect.x + border,
        (int)Mrect.y + border,
        (int)Mrect.width - border*2,
        (int)Mrect.height - border*2
    );
    for (int i = 0; i<M_NumOfScores; i++) {

        int columnWidth = Mrect.width/2;

        if (M_scrollOffset > M_NumOfScores*rowHeight - (Mrect.height)) M_scrollOffset = M_NumOfScores*rowHeight - (Mrect.height);
        if (M_scrollOffset < 0) M_scrollOffset = 0;

        int y = (int)Mrect.y + border + i * rowHeight - M_scrollOffset;

        if (y + rowHeight < (int)Mrect.y || y > (int)Mrect.y + (int)Mrect.height) continue;

        // Alternate row colors
        Color rowColor = (i % 2 == 0) ? LIGHTGRAY : WHITE;
        DrawRectangle((int)Mrect.x, y, (int)Mrect.width, rowHeight, rowColor);

        // Draw columns
        for (int c = 0; c < 2; c++) {
            int x = (int)Mrect.x + c * columnWidth;
            Rectangle box = {x, y, columnWidth, rowHeight};
            DrawRectangleLinesEx(box,screenWidth/1000, BLACK);

            char text[255];

            if (c == 0) sprintf(text,"%s",M_Scores[i].teamName);
            if (c == 1) sprintf(text,"%d",M_Scores[i].teamScore);

            DrawText(text, x+5+border, y, screenWidth/75, BLACK);
        }
    }
    EndScissorMode();

    //draw A rows
    BeginScissorMode(
        (int)Arect.x + border,
        (int)Arect.y + border,
        (int)Arect.width - border*2,
        (int)Arect.height - border*2
    );
    for (int i = 0; i<A_NumOfScores; i++) {

        int columnWidth = Arect.width/2;

        if (A_scrollOffset > A_NumOfScores*rowHeight - (Arect.height)) A_scrollOffset = A_NumOfScores*rowHeight - (Arect.height);
        if (A_scrollOffset < 0) A_scrollOffset = 0;

        int y = (int)Arect.y + border + i * rowHeight - A_scrollOffset;

        if (y + rowHeight < (int)Arect.y || y > (int)Arect.y + (int)Arect.height) continue;

        // Alternate row colors
        Color rowColor = (i % 2 == 0) ? LIGHTGRAY : WHITE;
        DrawRectangle((int)Arect.x, y, (int)Arect.width, rowHeight, rowColor);

        // Draw columns
        for (int c = 0; c < 2; c++) {
            int x = (int)Arect.x + c * columnWidth;
            Rectangle box = {x, y, columnWidth, rowHeight};
            DrawRectangleLinesEx(box,screenWidth/1000, BLACK);

            char text[255];

            if (c == 0) sprintf(text,"%s",A_Scores[i].teamName);
            if (c == 1) sprintf(text,"%d",A_Scores[i].teamScore);

            DrawText(text, x+5+border, y, screenWidth/75, BLACK);
        }
    }
    EndScissorMode();
}