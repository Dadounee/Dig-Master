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
    }    
    else
    {
        player->gameState = SELLMENU;
        changeButtonStateName("returnBackButton", ACTIVE);
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
    DrawLineEx((Vector2) { .x=GetScreenHeight() * 0.825, .y=GetScreenHeight() * 0.10 }, (Vector2) { .x=GetScreenHeight() * 0.825, .y=GetScreenHeight() * 0.9 }, GetScreenHeight() / 256, BLACK);
    
    char count[16];

    for (int i = 0;; i++)
    {
        if (!player->inv->inv || !player->inv->inv[i])
            break;
        DrawText(player->inv->inv[i]->name, GetScreenWidth() * 0.1 , GetScreenHeight() * (0.14 + i * 0.05), GetScreenHeight() * 0.04, DARKGRAY);
        sprintf(count, "%d", player->inv->counts[i]);
        DrawText(count, GetScreenWidth() * 0.45 - (strlen(count) - 1) * 0.04 * GetScreenHeight(), GetScreenHeight() * (0.14 + i * 0.05), GetScreenHeight() * 0.04, DARKGRAY);
        sprintf(count, "%d", player->inv->inv[i]->value);
        DrawText(count, GetScreenHeight() * 0.84, GetScreenHeight() * (0.14 + i * 0.05), GetScreenHeight() * 0.04, DARKGREEN);
        sprintf(count, "x%d", player->money_multiplier);
        DrawText(count, GetScreenHeight() * 0.84, GetScreenHeight() * (0.14 + i * 0.05), GetScreenHeight() * 0.04, DARKGREEN);
    }

}
