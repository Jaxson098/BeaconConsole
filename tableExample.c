#include "raylib.h"
#include<stdio.h>

#define ROW_HEIGHT 30
#define NUM_ROWS 100
#define NUM_COLUMNS 3
#define COLUMN_WIDTH 150

int main(void)
{
    InitWindow(800, 600, "Scrollable Table - raylib");

    Rectangle tableArea = { 100, 100, 500, 300 };  // visible region
    float scrollOffset = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Scroll with mouse wheel
        Vector2 mousePos = GetMousePosition();

        float wheel;
        if(CheckCollisionPointRec(mousePos,tableArea)) {
            wheel = GetMouseWheelMove();
        } else {
            wheel = 0;
        }

        printf("wheel: %f\n",wheel);
        

        scrollOffset -= wheel * 20;

        printf("scrollOffset: %f\n",scrollOffset);

        // Total table height
        float contentHeight = NUM_ROWS * ROW_HEIGHT;

        // Clamp scrolling
        if (scrollOffset < 0) scrollOffset = 0;
        if (scrollOffset > contentHeight - tableArea.height)
            scrollOffset = contentHeight - tableArea.height;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw table border
        DrawRectangleLinesEx(tableArea, 2, BLACK);

        // Clip drawing to table area
        BeginScissorMode(
            (int)tableArea.x,
            (int)tableArea.y,
            (int)tableArea.width,
            (int)tableArea.height
        );

        // Draw rows
        for (int i = 0; i < NUM_ROWS; i++)
        {
            float y = tableArea.y + i * ROW_HEIGHT - scrollOffset;

            // Skip rows outside viewport (optional optimization)
            if (y + ROW_HEIGHT < tableArea.y ||
                y > tableArea.y + tableArea.height)
                continue;

            // Alternate row colors
            Color rowColor = (i % 2 == 0) ? LIGHTGRAY : WHITE;
            DrawRectangle(tableArea.x, y, tableArea.width, ROW_HEIGHT, rowColor);

            // Draw columns
            for (int c = 0; c < NUM_COLUMNS; c++)
            {
                float x = tableArea.x + c * COLUMN_WIDTH;
                DrawRectangleLines(x, y, COLUMN_WIDTH, ROW_HEIGHT, GRAY);

                char text[64];
                sprintf(text, "Row %d Col %d", i, c);
                DrawText(text, x + 5, y + 8, 14, BLACK);
            }
        }

        EndScissorMode();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
