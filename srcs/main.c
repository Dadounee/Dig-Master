#include "libs.h"
#include "raylib.h"
#include "includes.h"

void    click_handler(zone *zone)
{
    if (IsMouseButtonPressed(0))
    {
        click_mining(zone, 1.0f);
    }
}

int main(void)
{
    zone *test = z_abyss();
    map_gen(test);


    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    
    InitWindow(screenWidth, screenHeight, "DigMaster");
    ToggleBorderlessWindowed();

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
        
            ClearBackground(LIGHTGRAY);
            
            display_map(test, 1.0f);
            DrawText("In progress", 190, 200, 20, RAYWHITE);

        EndDrawing();

        click_handler(test);
    }

    CloseWindow();
    map_free(&test->mine_map);

    return (0);
}