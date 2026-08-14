#include "includes.h"
#include "libs.h"

void inventory_init(playerData *player)
{
    player->inv = malloc(sizeof(p_inventory));
    player->inv->inv_size = 5;
    player->inv->oreCount = 0;
    player->inv->counts = NULL;
    player->inv->inv = NULL;
}

void    OreInventoryFree(p_inventory *inv)
{
    free(inv->inv);
    free(inv->counts);
    free(inv);
}

/*

    Adds an element to the player inventory, DOES NOT PERFORM FULLNESS CHECKS (will add evenn if full)

*/
void    InventoryAdd(playerData *player, int minedX, int minedY)
{
    ore *mined = { 0 };
    ore **oreList = get_ores();
    for (int i = 0; i < ORE_NUMBER ; i++)
    {
        if (oreList[i]->id == player->actual_zone->mine_map.map[minedY][minedX].ore.id)
            mined = oreList[i];
    }
    free(oreList);

    if (!player->inv->inv)
    {
        player->inv->inv = malloc(2 * sizeof(ore *));
        player->inv->counts = malloc(2 * sizeof(int *));
        player->inv->inv[0] = mined;
        player->inv->counts[0] = 1;
        player->inv->inv[1] = NULL;
        player->inv->counts[1] = 0;
        player->inv->oreCount++;
        return ;
    }

    int i = { 0 };
    while (player->inv->inv[i] && player->inv->inv[i]->id != player->actual_zone->mine_map.map[minedY][minedX].ore.id)
        i++;
    
    if (player->inv->inv[i])
    {
        player->inv->counts[i]++;
        player->inv->oreCount++;
        return ;
    }
    player->inv->inv = realloc(player->inv->inv, sizeof(ore *) * (i + 2));
    player->inv->counts = realloc(player->inv->counts, sizeof(int *) * (i + 2));
    player->inv->inv[i] = mined;
    player->inv->inv[i + 1] = NULL;
    player->inv->counts[i] = 1;
    player->inv->oreCount++;
}

void    invButtonClick(void *infos)
{
    playerData *player = (playerData *)infos;

    if (player->gameState == INVENTORY)
    {
        player->gameState = MINING;
        changeButtonStateName("returnBackButton", DISABLED);
    }    
    else
    {
        player->gameState = INVENTORY;
        changeButtonStateName("returnBackButton", ACTIVE);
    }
}

void    invButtonDisplay(void *infos, void *infos2, bool isHovered)
{
    (void)infos;
    (void)infos2;
    
    if (!isHovered)
    {
        DrawRectangleRounded((Rectangle) {
            .height=GetScreenHeight() * 0.1,
            .width=GetScreenHeight() * 0.1,
            .x=GetScreenWidth() * 0.91,
            .y=GetScreenHeight() * 0.03125
        },
        0.1f,
        5,
        DARKBLUE
        );
    }
    else
    {
        DrawRectangleRounded((Rectangle) {
            .height=GetScreenHeight() * 0.1,
            .width=GetScreenHeight() * 0.1,
            .x=GetScreenWidth() * 0.91,
            .y=GetScreenHeight() * 0.03125
        },
        0.1f,
        5,
        BLUE
        );
    }
    DrawText("wpnInv\nButton",
    GetScreenWidth() / 1.1f,
    GetScreenHeight() / 32,
    GetScreenHeight() * 0.02,
    BLACK
    );
}

void    inventoryDisplay(void)
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
}

void    returnBtnDisplay(void *infos, void *infos2, bool isHovered)
{
    (void)infos;
    (void)infos2;
    
    if (!isHovered)
    {
        DrawRectangleRounded((Rectangle) {
            .height=GetScreenHeight() * 0.05,
            .width=GetScreenHeight() * 0.05,
            .x=GetScreenWidth() * 0.85,
            .y=GetScreenHeight() * 0.05
        },
        0.1f,
        5,
        RED
        );
    }
    else
    {
        DrawRectangleRounded((Rectangle) {
            .height=GetScreenHeight() * 0.05,
            .width=GetScreenHeight() * 0.05,
            .x=GetScreenWidth() * 0.85,
            .y=GetScreenHeight() * 0.05
        },
        0.1f,
        5,
        (Color) {
            .r=236,
            .g=74,
            .b=76,
            .a=255
        }
        );
    }
    DrawText("rtn\nButton",
        GetScreenWidth() * 0.85,
        GetScreenHeight() * 0.05,
        GetScreenHeight() * 0.01,
        BLACK
    );
}

void    returnBtnClick(void *infos)
{
    playerData *player = (playerData *)infos;

    changeButtonStateName("returnBackButton", DISABLED);
    if (player->gameState == SELLMENU)
        changeButtonStateName("sellInvButton", DISABLED);
    player->gameState = MINING;
}
