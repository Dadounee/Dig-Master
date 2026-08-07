#include "includes.h"
#include "libs.h"

void inventory_init(player_data *player)
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
void    InventoryAdd(player_data *player, int minedX, int minedY)
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

    // typedef void    clickAction(void *infos);
    // typedef void    displayFunction(void *infos, void *infos2, bool isHovered);

void    invButtonClick(void *infos)
{
    player_data *player = (player_data *)infos;

    player->gameState = INVENTORY;
}

void    invButtonDisplay(void *infos, void *infos2, bool isHovered)
{
    (void)infos;
    (void)infos2;
    
    if (!isHovered)
    {
        DrawRectangleRounded((Rectangle) {
            .height=GetScreenHeight() / 5,
            .width=GetScreenWidth() / 5,
            .x=GetScreenHeight() / 32,
            .y=GetScreenHeight() - GetScreenHeight() / 5 - GetScreenHeight() / 32
        },
        0.1f,
        5,
        DARKBLUE
    );
    }
    else
    {
        DrawRectangleRounded((Rectangle) {
            .height=GetScreenHeight() / 5,
            .width=GetScreenWidth() / 5,
            .x=GetScreenHeight() / 32,
            .y=GetScreenHeight() - GetScreenHeight() / 5 - GetScreenHeight() / 32
        },
        0.1f,
        5,
        BLUE
    );
    }
}

void    inventoryDisplay(void)
{

}