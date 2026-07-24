#include "libs.h"
#include "raylib.h"
#include "includes.h"

int main(void)
{


    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    
    InitWindow(screenWidth, screenHeight, "DigMaster");
    ToggleBorderlessWindowed();

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    while (!WindowShouldClose())
    {

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            DrawText("In progress", 190, 200, 20, RAYWHITE);

        EndDrawing();

    }

    CloseWindow();

    return 0;
}