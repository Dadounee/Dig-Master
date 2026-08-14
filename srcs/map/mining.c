#include "includes.h"
#include "libs.h"

void    click_mining(playerData *player, float scale)
{
    int     tile_size = scale * GetScreenWidth() / TILE_PROPORTION;
    int     offset_x  = (GetScreenWidth() - (tile_size + 1) * player->actual_zone->mine_map.map_len) / 2;
    int     offset_y  = (GetScreenHeight() - (tile_size + 1) * player->actual_zone->mine_map.map_height) / 2;

    int     click_x = (GetMouseX() - offset_x) / (tile_size + 1);
    int     click_y = (GetMouseY() - offset_y) / (tile_size + 1);

    if ((player->inv->inv_size <= player->inv->oreCount) ||
    (GetMouseX() < offset_x || click_x >= player->actual_zone->mine_map.map_len) ||
    (GetMouseY() < offset_y || click_y >= player->actual_zone->mine_map.map_height))
        return ;

    player->display_actualisation = true;
    pick_radius(&player->actual_zone->mine_map, click_x, click_y, player->equipped_weapons.pickaxe->radius + 2);
    if (player->actual_zone->mine_map.map[click_y][click_x].durability > 0)
    {
        player->actual_zone->mine_map.map[click_y][click_x].durability -= player->miningStr;
        if (player->actual_zone->mine_map.map[click_y][click_x].durability <= 0)
        {
            player->actual_zone->mine_map.map[click_y][click_x].durability = 0;
            InventoryAdd(player, click_x, click_y);
        }
        player->actualSta--;
    }
    if (player->actualSta <= 0)
    {
        map_free(&player->actual_zone->mine_map);
        map_gen(player->actual_zone);
        applyOnePlayerStats(player, 1);
    }
}
