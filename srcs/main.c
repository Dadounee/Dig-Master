#include "libs.h"
#include "raylib.h"
#include "includes.h"

void    buttonCreation(playerData *player)
{
    clearButtons();

    createButton("inventoryButton", invButtonClick, invButtonDisplay, (Rectangle) { .height=GetScreenHeight() * 0.1, .width=GetScreenHeight() * 0.1, .x=GetScreenWidth() * 0.91, .y=GetScreenHeight() * 0.03125}, player, NULL, NULL, true);
    createButton("sellButton", sellButtonClick, sellButtonDisplay, (Rectangle) { .height=GetScreenHeight() * 0.1, .width=GetScreenHeight() * 0.1, .x=GetScreenWidth() * 0.91, .y=GetScreenHeight() * 0.1625}, player, NULL, NULL, true);
    createButton("returnBackButton", returnBtnClick, returnBtnDisplay, (Rectangle) { .height=GetScreenHeight() * 0.05, .width=GetScreenHeight() * 0.05, .x=GetScreenWidth() * 0.85, .y=GetScreenHeight() * 0.05}, player, NULL, NULL, true);
    createButton("sellInvButton", sellInvClick, sellInvDisplay, (Rectangle) { .height=GetScreenHeight() * 0.1, .width=GetScreenHeight() * 0.2, .x=GetScreenWidth() * 0.75, .y=GetScreenHeight() * 0.825}, player, NULL, NULL, true);
    // createButton("sleepButton", sellInvClick, sellInvDisplay, (Rectangle) { .height=GetScreenHeight() * 0.1, .width=GetScreenHeight() * 0.2, .x=GetScreenWidth() * 0.85, .y=GetScreenHeight() * 0.85}, player, NULL, NULL, true);
    
    changeButtonStateName("returnBackButton", DISABLED);
    changeButtonStateName("sellInvButton", DISABLED);
}

void    eventHandler(playerData *player)
{
    if (IsMouseButtonPressed(0))
    {
        click_mining(player, 1.0f);
        executeClicks(GetMousePosition());
    }
}

void    displayHandler(playerData *player)
{
    BeginDrawing();

        ClearBackground(GRAY);
        DisplayPlayerInfos(player, 1.0f);
        DisplayPlayerInv(player, 1.0f);
        if (player->gameState == MINING && player->display_actualisation)
        {
            DisplayMap(player->actual_zone, 1.0f, player->inv->inv_size <= player->inv->oreCount);
            tile_info(&player->actual_zone->mine_map, 1.0f);
        }
        if (player->gameState == INVENTORY)
        {
            inventoryDisplay();
        }
        if (player->gameState == SELLMENU)
        {
            sellMenuDisplay(player);
        }
        displayButtons(GetMousePosition());
        DrawFPS(0, 0);
        
    EndDrawing();
}

int main(void)
{
    playerData *player = player_init();

    InitWindow(1920, 1080, "DigMaster");
    const int screenWidth = GetScreenWidth();

    ToggleBorderlessWindowed();
    load_ores_textures(screenWidth, 1.0f);
    buttonCreation(player);
    
    map_gen(player->actual_zone);

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
