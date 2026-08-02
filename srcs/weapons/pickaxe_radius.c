#include "includes.h"

void    pick_radius(map *map, int x, int y, int remaining_depth)
{
    if (remaining_depth <= 0)
        return ;

    map->map[y][x].discovered = 1;
    
    if (y + 1 < map->map_height)
        pick_radius(map, x, y + 1, remaining_depth - 1);
    if (y - 1 >= 0)
        pick_radius(map, x, y - 1, remaining_depth - 1);

    if (x + 1 < map->map_len)
        pick_radius(map, x + 1, y, remaining_depth - 1);
    if (x - 1 >= 0)
        pick_radius(map, x - 1, y, remaining_depth - 1);

}
