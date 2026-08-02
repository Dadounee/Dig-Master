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

inline static void    ore_lifebar(float scale, float remaining_hp)
{
    Rectangle rec={
        .height = GetScreenHeight() / 32 * scale,
        .width = GetScreenWidth() / 5.5 * scale,
        .x = GetScreenHeight() / 24,
        .y = GetScreenHeight() / 7
    };

    DrawRectangleRounded(rec, 0.3f, 5, RED);
    rec.width *= remaining_hp;
    DrawRectangleRounded(rec, 0.3f, 5, GREEN);
    rec.width = GetScreenWidth() / 5.5 * scale;
    DrawRectangleRoundedLines(rec, 0.3f, 5, BLACK);
}

/*
    Will display the hovered tile info

        Works whatever the tile state is
        needs a map and a scale to function (map *minemap, float scale)

    NEEDS: sometimes its too slow, it needs to be reformed, 
     la fonction est trop volumineuse et merite d'etre redivisee

*/
void    tile_info(map *mine_map, float scale)
{
    
    int     tile_size = (scale * GetScreenHeight()) / (1.75 * mine_map->map_height);
    int     offset_x  = (GetScreenWidth() - (tile_size + 1) * mine_map->map_len) / 2;
    int     offset_y  = (GetScreenHeight() - (tile_size + 1) * mine_map->map_height) / 2;

    int     cursor_x = (GetMouseX() - offset_x) / (tile_size + 1);
    int     cursor_y = (GetMouseY() - offset_y) / (tile_size + 1);

    Rectangle rec={
        .height = GetScreenHeight() / 5 * scale,
        .width = GetScreenWidth() / 5 * scale,
        .x = GetScreenHeight() / 32,
        .y = GetScreenHeight() / 32
    };

    if (GetMouseX() < offset_x || cursor_x >= mine_map->map_len)
        return ;
    if (GetMouseY() < offset_y || cursor_y >= mine_map->map_height)
        return ;

    // Debut du draw des infos
    if (mine_map->map[cursor_y][cursor_x].discovered)
    {
        DrawRectangleRounded(rec, 0.1f, 5, SKYBLUE);

        // Draw minerais
        if (mine_map->map[cursor_y][cursor_x].s_type == mineral)
        {
            char health[20];

            sprintf(health, "%d/%d", mine_map->map[cursor_y][cursor_x].durability, mine_map->map[cursor_y][cursor_x].ore.durability);

            DrawText(mine_map->map[cursor_y][cursor_x].ore.name, GetScreenHeight() / 30, GetScreenHeight() / 30, GetScreenHeight() / 45, BLACK);
            DrawText("type: Mineral", GetScreenHeight() / 30, GetScreenHeight() / 15, GetScreenHeight() / 45, BLACK);
            DrawText("\t\tThey are usefull if you need want to earn\nsome cash", GetScreenHeight() / 22.5, GetScreenHeight() / 15 + GetScreenHeight() / 40, GetScreenHeight() / 67.5, BLACK);
            ore_lifebar(scale, mine_map->map[cursor_y][cursor_x].durability / (float)mine_map->map[cursor_y][cursor_x].ore.durability);
            DrawText(health, GetScreenHeight() / 24 + 2, GetScreenHeight() / 7 + 2, GetScreenHeight() / 67.5, BLACK);
        }

        // Draw vide
        if (mine_map->map[cursor_y][cursor_x].s_type == empty)
        {
            DrawText("Emptyness", GetScreenHeight() / 30, GetScreenHeight() / 30, GetScreenHeight() / 45, BLACK);
            DrawText("type: None", GetScreenHeight() / 30, GetScreenHeight() / 15, GetScreenHeight() / 45, BLACK);
            DrawText("\t\tWhat do you wanna know about this, it's\nliterally empty", GetScreenHeight() / 22.5, GetScreenHeight() / 15 + GetScreenHeight() / 40, GetScreenHeight() / 67.5, BLACK);
        }
    }
    else
    {
        // Draw undercover
        DrawRectangleRounded(rec, 0.1f, 5, GRAY);
        DrawText("???", GetScreenHeight() / 30, GetScreenHeight() / 30, GetScreenHeight() / 45, BLACK);
        DrawText("type:", GetScreenHeight() / 30, GetScreenHeight() / 15, GetScreenHeight() / 45, BLACK);
        DrawText("\t\t????????????????????????", GetScreenHeight() / 22.5, GetScreenHeight() / 15 + GetScreenHeight() / 40, GetScreenHeight() / 67.5, BLACK);
    }
}

void    click_mining(player_data *player, float scale)
{
    int     tile_size = (scale * GetScreenHeight()) / (1.75 * player->actual_zone->mine_map.map_height);
    int     offset_x  = (GetScreenWidth() - (tile_size + 1) * player->actual_zone->mine_map.map_len) / 2;
    int     offset_y  = (GetScreenHeight() - (tile_size + 1) * player->actual_zone->mine_map.map_height) / 2;

    int     click_x = (GetMouseX() - offset_x) / (tile_size + 1);
    int     click_y = (GetMouseY() - offset_y) / (tile_size + 1);

    if (GetMouseX() < offset_x || click_x >= player->actual_zone->mine_map.map_len)
        return ;
    if (GetMouseY() < offset_y || click_y >= player->actual_zone->mine_map.map_height)
        return ;

    player->display_actualisation = true;
    pick_radius(&player->actual_zone->mine_map, click_x, click_y, player->equipped_weapons.pickaxe->radius);
    player->actual_zone->mine_map.map[click_y][click_x].durability -= player->mining_str;
    player->actual_sta--;
    if (player->actual_sta <= 0)
    {
        map_free(&player->actual_zone->mine_map);
        map_gen(player->actual_zone);
        player->actual_sta = player->mining_sta + 20;
    }
}
