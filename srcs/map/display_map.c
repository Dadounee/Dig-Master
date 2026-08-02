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
    int     tile_size = scale * GetScreenWidth() / TILE_PROPORTION;
    int     offset_x  = (GetScreenWidth() - tile_size * infos->mine_map.map_len) / 2;
    int     offset_y  = (GetScreenHeight() - tile_size * infos->mine_map.map_height) / 2;
    Color   Darker  = {.r=127, .g=127, .b=127, .a=255}; 

    for (int grid_y = 0; grid_y < infos->mine_map.map_height ; grid_y++)
    {
        for (int grid_x = 0; grid_x < infos->mine_map.map_len ; grid_x++)
        {
            if (infos->mine_map.map[grid_y][grid_x].discovered)
            {
                if (
                    (infos->mine_map.map[grid_y][grid_x].s_type == MINERAL) ||
                    (infos->mine_map.map[grid_y][grid_x].s_type == EMPTY)
                )
                    DrawTexture(
                        infos->mine_map.map[grid_y][grid_x].ore.texture,
                        offset_x + grid_x * tile_size,
                        offset_y + grid_y * tile_size,
                        WHITE
                    );
                if (infos->mine_map.map[grid_y][grid_x].s_type == EMPTY)
                    DrawTexture(
                        infos->mine_map.map[grid_y][grid_x].ore.texture,
                        offset_x + grid_x * tile_size,
                        offset_y + grid_y * tile_size,
                        Darker
                    );
            }
            else
                DrawRectangle(
                    offset_x + grid_x * tile_size,
                    offset_y + grid_y * tile_size,
                    tile_size,
                    tile_size,
                    BLACK
                );
        }
    }
}

inline static void    lifebar(Vector2 pos, float height, float length, float scale, float fillness)
{
    Rectangle rec={
        .height = height * scale,
        .width = length * scale,
        .x = pos.x,//GetScreenHeight() / 24,
        .y = pos.y//GetScreenHeight() / 7
    };

    DrawRectangleRounded(rec, 0.3f, 5, RED);
    if (fillness > 0)
    {
        if (fillness <= 1.0f)
            rec.width *= fillness;
        DrawRectangleRounded(rec, 0.3f, 5, GREEN);
    }
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
    
    int     tile_size = scale * GetScreenWidth() / TILE_PROPORTION;
    int     offset_x  = (GetScreenWidth() - tile_size * mine_map->map_len) / 2;
    int     offset_y  = (GetScreenHeight() - tile_size * mine_map->map_height) / 2;

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
        if (mine_map->map[cursor_y][cursor_x].s_type == MINERAL)
        {
            char health[20];

            sprintf(health, "%d/%d", mine_map->map[cursor_y][cursor_x].durability, mine_map->map[cursor_y][cursor_x].ore.durability);

            DrawText(mine_map->map[cursor_y][cursor_x].ore.name, GetScreenHeight() / 30, GetScreenHeight() / 30, GetScreenHeight() / 45, BLACK);
            DrawText("type: Mineral", GetScreenHeight() / 30, GetScreenHeight() / 15, GetScreenHeight() / 45, BLACK);
            DrawText("\t\tThey are usefull if you need want to earn\nsome cash", GetScreenHeight() / 22.5, GetScreenHeight() / 15 + GetScreenHeight() / 40, GetScreenHeight() / 67.5, BLACK);
            lifebar((Vector2){.x=GetScreenHeight() / 24, .y=GetScreenHeight() / 7}, GetScreenHeight() / 32, GetScreenWidth() / 5.5, scale, mine_map->map[cursor_y][cursor_x].durability / (float)mine_map->map[cursor_y][cursor_x].ore.durability);
            DrawText(health, GetScreenHeight() / 24 + 2, GetScreenHeight() / 7 + 2, GetScreenHeight() / 67.5, BLACK);
        }

        // Draw vide
        if (mine_map->map[cursor_y][cursor_x].s_type == EMPTY)
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

void    DisplayPlayerInfos(player_data *player, float scale)
{
    char str[16];

    DrawRectangleRounded((Rectangle) {
            .height=GetScreenHeight() / 5 * scale,
            .width=GetScreenWidth() / 5 * scale,
            .x=GetScreenHeight() / 32,
            .y=GetScreenHeight() - GetScreenHeight() / 5 * scale - GetScreenHeight() / 32
        },
        0.1f,
        5,
        SKYBLUE
    );
    DrawText("Stats:", GetScreenHeight() / 30, GetScreenHeight() - GetScreenHeight() / 5 * scale - GetScreenHeight() / 32 - GetScreenHeight() / 45, GetScreenHeight() / 45, BLACK);
    DrawText("Stamina:", GetScreenHeight() / 15, GetScreenHeight() - GetScreenHeight() / 5 * scale - GetScreenHeight() / 64, GetScreenHeight() / 45, BLACK);
    lifebar(
        (Vector2) { 
            .x=GetScreenHeight() / 24,
            .y=GetScreenHeight() - GetScreenHeight() / 5.5 * scale
        },
        GetScreenHeight() / 32, GetScreenWidth() / 5.5, 1.0f,
        player->actual_sta / (float)player->mining_sta
    );
    sprintf(str, "%d/%d", player->actual_sta, player->mining_sta);
    DrawText(str, GetScreenHeight() / 24 + 2, GetScreenHeight() - GetScreenHeight() / 5.5 * scale + 2, GetScreenHeight() / 67.5, BLACK);
    DrawText("Strength:", GetScreenHeight() / 15, GetScreenHeight() - GetScreenHeight() / 8 * scale, GetScreenHeight() / 45, BLACK);
    sprintf(str, "%d", player->mining_str);
    DrawText(str, GetScreenHeight() / 15 + GetScreenHeight() / 5, GetScreenHeight() - GetScreenHeight() / 8 * scale, GetScreenHeight() / 45, BLACK);
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
    pick_radius(&player->actual_zone->mine_map, click_x, click_y, player->equipped_weapons.pickaxe->radius + 2);
    player->actual_zone->mine_map.map[click_y][click_x].durability -= player->mining_str;
    player->actual_sta--;
    if (player->actual_sta <= 0)
    {
        map_free(&player->actual_zone->mine_map);
        map_gen(player->actual_zone);
        player->actual_sta = player->mining_sta;
    }
}
