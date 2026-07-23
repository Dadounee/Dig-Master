#include "../includes/includes.h"

void radius_0(map *map, int x, int y)
{
    map->map[x][y].discovered = 1;
}

void radius_1(map *map, int x, int y)
{
    map->map[x][y].discovered = 1;

    map->map[max(x-1, 0)][y].discovered = 1;
    map->map[min(x+1, map->map_height-1)][y].discovered = 1;
    
    map->map[x][max(y-1, 0)].discovered = 1;
    map->map[x][min(y+1, map->map_len-1)].discovered = 1;
}

void radius_2(map *map, int x, int y)
{
    int max_x = min(x + 1, map->map_height-1);
    int max_y = min(y + 1, map->map_len-1);
    int dis_x = max(x-1, 0);
    int dis_y;

    while (dis_x <= max_x)
    {
        dis_y = max(y-1, 0);
        while (dis_y <= max_y)
        {
            map->map[max(dis_x, 0)][max(dis_y, 0)].discovered = 1;
            dis_y++;
        }
        dis_x++;
    }
}

void radius_3(map *map, int x, int y)
{
    int max_x = min(x + 1, map->map_height-1);
    int max_y = min(y + 1, map->map_len-1);
    int dis_x = max(x-1, 0);
    int dis_y;

    map->map[max(x - 2, 0)][y].discovered = 1;
    map->map[min(x + 2, map->map_height-1)][y].discovered = 1;
    map->map[x][max(y - 2, 0)].discovered = 1;
    map->map[x][min(y + 2, map->map_len-1)].discovered = 1;
    
    while (dis_x <= max_x)
    {
        dis_y = max(y-1, 0);
        while (dis_y <= max_y)
        {
            map->map[max(dis_x, 0)][max(dis_y, 0)].discovered = 1;
            dis_y++;
        }
        dis_x++;
    } 
}
