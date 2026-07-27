#include "libs.h"
#include "raylib.h"
#include "includes.h"

void    click_handler(player_data *player)
{
    if (IsMouseButtonPressed(0))
    {
        click_mining(player, 1.0f);
    }
}

int main(void)
{
    player_data *player = player_init();

    map_gen(player->actual_zone);
    pick_radius(&player->actual_zone->mine_map, 5, 5, 3);
    player->actual_sta = player->mining_sta;

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    
    InitWindow(screenWidth, screenHeight, "DigMaster");
    ToggleBorderlessWindowed();

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
        
            ClearBackground(LIGHTGRAY);
            
            display_map(player->actual_zone, 1.0f);
            DrawText("In progress", 190, 200, 20, RAYWHITE);

        EndDrawing();

        click_handler(player);
    }

    CloseWindow();
    player_free(player);

    return (0);
}