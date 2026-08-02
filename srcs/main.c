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

    InitWindow(1920, 1080, "DigMaster");
    const int screenWidth = GetScreenWidth();

    ToggleBorderlessWindowed();
    load_ores_textures(screenWidth, 1.0f);
    
    map_gen(player->actual_zone);
    player->actual_sta = player->mining_sta;
     
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    while (!WindowShouldClose())
    {
        click_handler(player);

        BeginDrawing();
        
            ClearBackground(LIGHTGRAY);
            DrawFPS(0, 0);
            if (player->display_actualisation)
            {
                DisplayMap(player->actual_zone, 1.0f, player->inv->inv_size <= player->inv->oreCount);
                tile_info(&player->actual_zone->mine_map, 1.0f);
            }
            DisplayPlayerInfos(player, 1.0f);
            DisplayPlayerInv(player, 1.0f);
        
        EndDrawing();
    }

    CloseWindow();
    player_free(player);

    return (0);
}
