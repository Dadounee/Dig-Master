#include "includes.h"
#include "libs.h"

void SellInventory(player_data *player)
{
    int i = 0;
    int count = 0;

    while (count < player->inv->oreCount)
    {
        player->money += player->money_multiplier * player->inv->inv[i]->value * player->inv->counts[i];
        count += player->inv->counts[i];
        i++;
    }
    free(player->inv->inv);
    free(player->inv->counts);
    player->inv->inv = NULL;
    player->inv->counts = NULL;
    player->inv->oreCount = 0;
}


/*
    button things
*/


void    sellButtonClick(void *infos)
{
    player_data *player = (player_data *)infos;

    if (player->gameState == SELLMENU)
    {
        player->gameState = MINING;
        changeButtonStateName("returnBackButton", DISABLED);
        changeButtonStateName("sellInvButton", DISABLED);
    }    
    else
    {
        player->gameState = SELLMENU;
        changeButtonStateName("returnBackButton", ACTIVE);
        if (player->inv->oreCount == 0)
            changeButtonStateName("sellInvButton", DEACTIVATED);
        else
            changeButtonStateName("sellInvButton", ACTIVE);
    }
}

void    sellButtonDisplay(void *infos, void *infos2, bool isHovered)
{
    (void)infos;
    (void)infos2;
    
    if (!isHovered)
    {
        DrawRectangleRounded((Rectangle) {
            .height=GetScreenHeight() * 0.1,
            .width=GetScreenHeight() * 0.1,
            .x=GetScreenWidth() * 0.91,
            .y=GetScreenHeight() * 0.1625
        },
        0.1f,
        5,
        DARKGREEN
        );
    }
    else
    {
        DrawRectangleRounded((Rectangle) {
            .height=GetScreenHeight() * 0.1,
            .width=GetScreenHeight() * 0.1,
            .x=GetScreenWidth() * 0.91,
            .y=GetScreenHeight() * 0.1625
        },
        0.1f,
        5,
        GREEN
        );
    }
    DrawText("sellMenu\nButton",
    GetScreenWidth() * 0.91,
    GetScreenHeight() * 0.1625,
    GetScreenHeight() * 0.02,
    BLACK
    );
}

/*
    display things
*/

void    sellMenuDisplay(player_data *player)
{
    DrawRectangleRec((Rectangle) {
        .height=GetScreenHeight(),
        .width=GetScreenWidth(),
        .x=0,
        .y=0
        },
        (Color) {
            .r=0,
            .g=0,
            .b=0,
            .a=195
        }
    );
    DrawRectangleRounded((Rectangle) {
        .height=GetScreenHeight() * 0.90,
        .width=GetScreenWidth() * 0.85,
        .x=GetScreenHeight() * 0.05,
        .y=GetScreenHeight() * 0.05
    },
    0.05f,
    10,
    GRAY
    );
    DrawLineEx((Vector2) { .x=GetScreenHeight() * 0.77, .y=GetScreenHeight() * 0.10 }, (Vector2) { .x=GetScreenHeight() * 0.77, .y=GetScreenHeight() * 0.9 }, GetScreenHeight() / 256, BLACK);
    DrawLineEx((Vector2) { .x=GetScreenHeight() * 0.92, .y=GetScreenHeight() * 0.10 }, (Vector2) { .x=GetScreenHeight() * 0.92, .y=GetScreenHeight() * 0.9 }, GetScreenHeight() / 256, BLACK);
    DrawLineEx((Vector2) { .x=GetScreenHeight() * 1.10, .y=GetScreenHeight() * 0.10 }, (Vector2) { .x=GetScreenHeight() * 1.10, .y=GetScreenHeight() * 0.9 }, GetScreenHeight() / 256, BLACK);
    
    char count[16];

    DrawText("ORE", GetScreenWidth() * 0.1 , GetScreenHeight() * 0.06, GetScreenHeight() * 0.04, DARKGRAY);
    DrawText("COUNT", GetScreenWidth() * 0.425 , GetScreenHeight() * 0.06, GetScreenHeight() * 0.04, DARKGRAY);
    DrawText("VALUE", GetScreenWidth() * 0.525 , GetScreenHeight() * 0.06, GetScreenHeight() * 0.04, DARKGRAY);
    DrawText("TOTAL", GetScreenWidth() * 0.625 , GetScreenHeight() * 0.06, GetScreenHeight() * 0.04, DARKGRAY);
    for (int i = 0;; i++)
    {
        if (!player->inv->inv || !player->inv->inv[i])
            break;
        DrawText(player->inv->inv[i]->name, GetScreenWidth() * 0.1 , GetScreenHeight() * (0.14 + i * 0.04), GetScreenHeight() * 0.04, DARKGRAY);
        sprintf(count, "%d", player->inv->counts[i]);
        DrawText(count, GetScreenHeight() * (0.88 - (strlen(count) - 1) * 0.04), GetScreenHeight() * (0.14 + i * 0.04), GetScreenHeight() * 0.04, DARKGRAY);
        sprintf(count, "%d", player->inv->inv[i]->value);
        DrawText(count, GetScreenHeight() * 1.06, GetScreenHeight() * (0.14 + i * 0.04), GetScreenHeight() * 0.04, DARKGREEN);
        sprintf(count, "=%d", player->money_multiplier * player->inv->inv[i]->value * player->inv->counts[i]);
        DrawText(count, GetScreenHeight() * 1.14, GetScreenHeight() * (0.14 + i * 0.04), GetScreenHeight() * 0.04, GREEN);
    }
    sprintf(count, "x%d", player->money_multiplier);
    DrawText(count, GetScreenHeight() * 1.06, GetScreenHeight() * 0.9, GetScreenHeight() * 0.04, DARKGRAY);

}

void    sellInvClick(void *infos)
{
    player_data *player = (player_data *)infos;

    SellInventory(player);
    changeButtonStateName("sellInvButton", DEACTIVATED);
}

void    sellInvDisplay(void *infos, void *infos2, bool isHovered)
{
    (void)infos;
    (void)infos2;
    
    if (!isHovered)
    {
        DrawRectangleRounded((Rectangle) {
            .height=GetScreenHeight() * 0.1,
            .width=GetScreenHeight() * 0.2,
            .x=GetScreenWidth() * 0.75,
            .y=GetScreenHeight() * 0.825
        },
        0.1f,
        5,
        BLUE
        );
    }
    else
    {
        DrawRectangleRounded((Rectangle) {
            .height=GetScreenHeight() * 0.1,
            .width=GetScreenHeight() * 0.2,
            .x=GetScreenWidth() * 0.75,
            .y=GetScreenHeight() * 0.825
        },
        0.1f,
        5,
        SKYBLUE
        );
    }
    DrawText("Sell ores",
    GetScreenWidth() * 0.75,
    GetScreenHeight() * 0.825,
    GetScreenHeight() * 0.02,
    BLACK
    );
}
