#include "includes.h"
#include "libs.h"
#include "raylib.h"

/*
    Displays the actual mining map directly on the screen. Will place the map on the center of the screen with the map scale being the 

        takes the actual player zone --> (zone *actual_zone)
        takes the map scale --> (float scale)

    to place after BeginDrawing(); does not end the writing event buffer
*/
void    display_map(zone *infos, float scale)
{
    int     tile_size = (scale * GetScreenHeight()) / (1.75 * infos->mine_map.map_height);
    int     offset_x  = (GetScreenWidth() - (tile_size + 1) * infos->mine_map.map_len) / 2;
    int     offset_y  = (GetScreenHeight() - (tile_size + 1) * infos->mine_map.map_height) / 2;

    Color   covered ={
        .r=0,
        .g=0,
        .b=0,
        .a=255
    };
    Color   discovered ={
        .r=0,
        .g=0,
        .b=255,
        .a=127
    };
    int     font_size = 20;

    for (int grid_y = 0; grid_y < infos->mine_map.map_height ; grid_y++)
    {
        for (int grid_x = 0; grid_x < infos->mine_map.map_len ; grid_x++)
        {
            if (infos->mine_map.map[grid_y][grid_x].discovered)
            {
                DrawRectangle(
                    offset_x + grid_x * tile_size + grid_x,
                    offset_y + grid_y * tile_size + grid_y,
                    tile_size,
                    tile_size,
                    discovered
                );
                if (infos->mine_map.map[grid_y][grid_x].s_type == mineral)
                    DrawText(
                        infos->mine_map.map[grid_y][grid_x].ore.name,
                        offset_x + grid_x * tile_size + grid_x,
                        offset_y + grid_y * tile_size + grid_y,
                        font_size,
                        covered
                    );
            }
            else
                DrawRectangle(
                    offset_x + grid_x * tile_size + grid_x,
                    offset_y + grid_y * tile_size + grid_y,
                    tile_size,
                    tile_size,
                    covered
                );
        }
    }
}

void    click_mining(player_data *player, float scale)
{
    int     tile_size = (scale * GetScreenHeight()) / (1.75 * player->actual_zone->mine_map.map_height);
    int     offset_x  = (GetScreenWidth() - (tile_size + 1) * player->actual_zone->mine_map.map_len) / 2;
    int     offset_y  = (GetScreenHeight() - (tile_size + 1) * player->actual_zone->mine_map.map_height) / 2;

    int     click_x = (GetMouseX() - offset_x) / (tile_size + 1);
    int     click_y = (GetMouseY() - offset_y) / (tile_size + 1);

    if (click_x < 0 || click_x >= player->actual_zone->mine_map.map_len)
        return ;
    if (click_y < 0 || click_y >= player->actual_zone->mine_map.map_height)
        return ;
    
    player->actual_zone->mine_map.map[click_y][click_x].discovered = 1;
    player->actual_zone->mine_map.map[click_y][click_x].durability -= player->mining_str;
    player->actual_sta--;
    if (player->actual_sta <= 0)
    {
        map_free(&player->actual_zone->mine_map);
        map_gen(player->actual_zone);
        player->actual_sta = player->mining_sta;
    }
}
