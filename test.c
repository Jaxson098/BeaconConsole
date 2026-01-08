#include "raylib.h"

int main() {
    InitWindow(800, 600, "Sound Test");
    InitAudioDevice();           // Initialize audio

    Sound sound = LoadSound("start.mp3");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        // Example: Play sound when space is pressed
        if (IsKeyPressed(KEY_SPACE)) {
            PlaySound(sound);   // <-- This works outside BeginDrawing/EndDrawing
        }

        // Drawing block
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Press SPACE to play sound", 200, 300, 20, BLACK);
        EndDrawing();
    }

    UnloadSound(sound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
