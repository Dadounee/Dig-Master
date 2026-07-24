#include "ores_funcs.h"
#include "player_structs.h"
#include "libs.h"

space create_space(zone *actual_zone)
{
    int     i;
    int     rand_i;
    space   sp;

    // if (rand() % 200 + 1 >= 180)
    //     sp.s_type = crate;

    sp.discovered = 0;

    rand_i = rand() % (1000 + actual_zone->void_density);
    i = 0;
    while (rand_i >= actual_zone->ores_density()[i + 1] && i < actual_zone->ore_nb)
        i++;
    if (i == actual_zone->ore_nb)
        sp.s_type = empty;
    else
        sp.s_type = mineral;

    if (sp.s_type == mineral)
    {
        sp.ore = *(actual_zone->available_ores())[i];
        sp.durability = sp.ore.durability;
    }

    // if (sp.s_type == crate)
    // {
    //     sp.rarity = common;
    // }
    return (sp);
}

void map_gen(zone *actual_zone)
{
    int i;
    int j;

    srand(time(NULL));

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

// int mine_pos(player_data *player, int height, int lenght){}
/*{
    height--;
    lenght--;
    player->equipped_weapons->pickaxe.radius(&player->actual_zone->mine_map, height, lenght);
    
    if (player->actual_zone->mine_map.map[height][lenght].s_type == mineral)
    {
        if (player->actual_zone->mine_map.map[height][lenght].durability <= 0)
            printf("%sThere's nothing interesting here anymore...%s\n", TC_WHT, TC_NRM);
        else
        {
            player->actual_zone->mine_map.map[height][lenght].durability -= player->mining_str;
            printf(
                "You mined %s\nremaining durability: %d/%d\n",
                player->actual_zone->mine_map.map[height][lenght].ore.name,
                player->actual_zone->mine_map.map[height][lenght].durability,
                player->actual_zone->mine_map.map[height][lenght].ore.durability
            );
            if (player->actual_zone->mine_map.map[height][lenght].durability <= 0)
            {
                printf("you've succesfully excavated this ore\n");
                player->mining_sta--;
                return (1);

            }
            player->mining_sta--;
        }    
    }
    else if (player->actual_zone->mine_map.map[height][lenght].s_type == crate)
    {
        if (player->actual_zone->mine_map.map[height][lenght].rarity == -1)
            printf("%sThere's nothing interesting here anymore...%s\n", TC_WHT, TC_NRM);
        else
        {
            printf("%sYou got an %s crate!%s\n", TC_WHT, get_rarity(player->actual_zone->mine_map.map[height][lenght].rarity),TC_NRM);
            player->crates[player->actual_zone->mine_map.map[height][lenght].rarity]++;
            player->actual_zone->mine_map.map[height][lenght].rarity = -1;
			player->mining_sta -= power(2*player->actual_zone->mine_map.map[height][lenght].rarity, 2);
        }
    }
    else
        player->mining_sta--;
    return (0);
}*/

void map_free(map *map)
{
    int i = 0;

    while (i < map->map_height)
    {
        free(map->map[i]);
        i++;
    }
}