#include "ores_funcs.h"
#include "player_structs.h"
#include "libs.h"

static space create_space(zone *actual_zone)
{
    int     i;
    int     rand_i;
    space   sp;

    // if (rand() % 200 + 1 >= 180)
    //     sp.s_type = crate;

    sp.discovered = 0;

    rand_i = rand() % (actual_zone->ores_density()[actual_zone->ore_nb]);
    i = 0;
    while (rand_i >= actual_zone->ores_density()[i + 1] && i < actual_zone->ore_nb)
        i++;
    sp.s_type = MINERAL;
    if (sp.s_type == MINERAL)
    {
        sp.ore = *(actual_zone->available_ores())[i];
        sp.durability = sp.ore.durability;
    }
    if (sp.s_type == CRATE)
        sp.rarity = common;
    return (sp);
}

void map_gen(zone *actual_zone)
{
    int i;
    int j;

    srand(time(NULL));

    actual_zone->is_map = true;
    actual_zone->mine_map.map = (space **) malloc(sizeof(space *) * actual_zone->mine_map.map_height);
    i = 0;
    while (i < actual_zone->mine_map.map_height)
    {
        actual_zone->mine_map.map[i] = (space *) malloc(sizeof(space) * actual_zone->mine_map.map_len);
        j = 0;
        while (j < actual_zone->mine_map.map_len)
        {
            actual_zone->mine_map.map[i][j] = create_space(actual_zone);
            j++;
        }
        i++;
    }
}

void map_free(map *map)
{
    int i = 0;

    while (i < map->map_height)
    {
        free(map->map[i]);
        i++;
    }
    free(map->map);
}