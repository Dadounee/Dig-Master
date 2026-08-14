#include "includes.h"
#include "libs.h"
#include "raylib.h"

/*
    Displays the actual mining map directly on the screen. Will place the map on the center of the screen with the map scale being the 

        takes the actual player zone --> (zone *actual_zone)
        takes the map scale --> (float scale)

    to place after BeginDrawing(); does not end the writing event buffer
*/
void    DisplayMap(zone *infos, float scale, int blocked)
{
    int     tile_size = scale * GetScreenWidth() / TILE_PROPORTION;
    int     offset_x  = (GetScreenWidth() - tile_size * infos->mine_map.map_len) / 2;
    int     offset_y  = (GetScreenHeight() - tile_size * infos->mine_map.map_height) / 2;
    Color   Darker  = {.r=95, .g=95, .b=95, .a=255}; 

    for (int grid_y = 0; grid_y < infos->mine_map.map_height ; grid_y++)
    {
        for (int grid_x = 0; grid_x < infos->mine_map.map_len ; grid_x++)
        {
            if (infos->mine_map.map[grid_y][grid_x].discovered)
            {
                if (infos->mine_map.map[grid_y][grid_x].s_type == MINERAL)
                {
                    if (infos->mine_map.map[grid_y][grid_x].durability > 0  && !blocked)
                        DrawTexture(
                            infos->mine_map.map[grid_y][grid_x].ore.texture,
                            offset_x + grid_x * tile_size,
                            offset_y + grid_y * tile_size,
                            WHITE
                        );
                    else 
                        DrawTexture(
                            infos->mine_map.map[grid_y][grid_x].ore.texture,
                            offset_x + grid_x * tile_size,
                            offset_y + grid_y * tile_size,
                            Darker
                        );
                }
            }
            else if (!blocked)
                DrawTexture(
                    infos->available_ores()[infos->ore_nb]->texture,
                    offset_x + grid_x * tile_size,
                    offset_y + grid_y * tile_size,
                    WHITE
                );
            else
                DrawTexture(
                    infos->available_ores()[infos->ore_nb]->texture,
                    offset_x + grid_x * tile_size,
                    offset_y + grid_y * tile_size,
                    Darker
                );
        }
    }
}

inline static void    lifebar(Vector2 pos, float height, float length, float scale, float fillness)
{
    Rectangle rec={
        .height = height * scale,
        .width = length * scale,
        .x = pos.x,
        .y = pos.y
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
    }
    else
    {
        // Draw undercover
        DrawRectangleRounded(rec, 0.1f, 5, SKYBLUE);
        DrawText("???", GetScreenHeight() / 30, GetScreenHeight() / 30, GetScreenHeight() / 45, BLACK);
        DrawText("type:", GetScreenHeight() / 30, GetScreenHeight() / 15, GetScreenHeight() / 45, BLACK);
        DrawText("\t\t????????????????????????", GetScreenHeight() / 22.5, GetScreenHeight() / 15 + GetScreenHeight() / 40, GetScreenHeight() / 67.5, BLACK);
    }
}

void    DisplayPlayerInfos(playerData *player, float scale)
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
        player->actualSta / (float)(player->playerStats.baseStaBoost * player->playerStats.multStaBoost)
    );
    sprintf(str, "%d/%d", player->actualSta, player->playerStats.baseStaBoost * player->playerStats.multStaBoost);
    DrawText(str, GetScreenHeight() / 24 + 2, GetScreenHeight() - GetScreenHeight() / 5.5 * scale + 2, GetScreenHeight() / 67.5, BLACK);
    
    DrawText("Strength:", GetScreenHeight() / 15, GetScreenHeight() - GetScreenHeight() / 8 * scale, GetScreenHeight() / 45, BLACK);
    sprintf(str, "%d", player->miningStr);
    DrawText(str, GetScreenHeight() / 15 + GetScreenHeight() / 5, GetScreenHeight() - GetScreenHeight() / 8 * scale, GetScreenHeight() / 45, BLACK);
    
    DrawText("Money:", GetScreenHeight() / 15, GetScreenHeight() - GetScreenHeight() / 8 * scale + GetScreenHeight() / 45, GetScreenHeight() / 45, BLACK);
    sprintf(str, "%lld", player->money);
    DrawText(str, GetScreenHeight() / 15 + GetScreenHeight() / 5, GetScreenHeight() - GetScreenHeight() / 8 * scale + GetScreenHeight() / 45, GetScreenHeight() / 45, BLACK);
}

void    DisplayPlayerInv(playerData *player, float scale)
{
    char    capacity[16];

    DrawRectangleRounded((Rectangle) {
            .height=GetScreenHeight() / 2.5 * scale,
            .width=GetScreenWidth() / 5 * scale,
            .x=GetScreenHeight() / 32,
            .y=GetScreenHeight() / 10.3 + GetScreenHeight() / 5 * scale
        },
        0.1f,
        5,
        SKYBLUE
    );
    DrawText("Inventory:", GetScreenHeight() / 30, GetScreenHeight() / 10.3 + GetScreenHeight() / 5 * scale - GetScreenHeight() / 45, GetScreenHeight() / 45, BLACK);
    sprintf(capacity, "%d/%d", player->inv->oreCount, player->inv->inv_size);
    DrawText(capacity, GetScreenHeight() / 30 + 12 * GetScreenHeight() / 45, GetScreenHeight() / 10.3 + GetScreenHeight() / 5 * scale - GetScreenHeight() / 45, GetScreenHeight() / 45, BLACK);
    if(player->inv->inv)
    {
        char    count[8];

        for (int i = 0; player->inv->inv[i] ; i++)
        {
            DrawTexture(
                player->inv->inv[i]->texture,
                GetScreenHeight() / 15 * scale + (player->inv->inv[i]->texture.width * 1.2) * (i % 4),
                GetScreenHeight() / 3.2 * scale + (player->inv->inv[i]->texture.width * 1.2) * (i / 4),
                WHITE
            );
            DrawText(
                player->inv->inv[i]->name,
                GetScreenHeight() / 15 * scale + (player->inv->inv[i]->texture.width * 1.2) * (i % 4),
                GetScreenHeight() / 3.2 * scale + (player->inv->inv[i]->texture.width * 1.2) * (i / 4),
                GetScreenHeight() / 60,
                BLACK
            );
            sprintf(count, "%d", player->inv->counts[i]);
            DrawText(
                count,
                GetScreenHeight() / 15 * scale + (player->inv->inv[i]->texture.width * 1.2) * (i % 4),
                GetScreenHeight() / 3.2 * scale + (player->inv->inv[i]->texture.width * 1.2) * (i / 4) + GetScreenHeight() / 60,
                GetScreenHeight() / 60,
                BLACK
            );
        }
    }
}
