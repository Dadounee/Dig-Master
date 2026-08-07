#include "libs.h"
#include "raylib.h"
#include "includes.h"

void    buttonCreation(player_data *player)
{
    clearButtons();

    createButton("inventoryButton", invButtonClick, invButtonDisplay, (Rectangle){ .height=GetScreenHeight() / 5, .width=GetScreenWidth() / 5, .x=GetScreenHeight() / 32, .y=GetScreenHeight() - GetScreenHeight() / 5 - GetScreenHeight() / 32 }, player, NULL, NULL, true);
}

void    eventHandler(player_data *player)
{
    if (IsMouseButtonPressed(0))
    {
        click_mining(player, 1.0f);
        executeClicks(GetMousePosition());
    }
    if (player->gameState != player->oldState)
        changeState(player);
}

void    displayHandler(player_data *player)
{
    BeginDrawing();

        ClearBackground(GRAY);
        if (player->gameState == MINING && player->display_actualisation)
        {
            DisplayMap(player->actual_zone, 1.0f, player->inv->inv_size <= player->inv->oreCount);
            tile_info(&player->actual_zone->mine_map, 1.0f);
        }
        DisplayPlayerInfos(player, 1.0f);
        DisplayPlayerInv(player, 1.0f);
        displayButtons(GetMousePosition());
        DrawFPS(0, 0);
        
    EndDrawing();
}

int main(void)
{
    player_data *player = player_init();

    InitWindow(1920, 1080, "DigMaster");
    const int screenWidth = GetScreenWidth();

    ToggleBorderlessWindowed();
    load_ores_textures(screenWidth, 1.0f);
    buttonCreation(player);
    
    map_gen(player->actual_zone);
    player->actual_sta = player->mining_sta;
    changeButtonStateName("inventoryButton", DISABLED);
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    while (!WindowShouldClose())
    {
        eventHandler(player);
        displayHandler(player);
    }

    player_free(player);
    clearButtons();
    CloseWindow();

    return (0);
}
