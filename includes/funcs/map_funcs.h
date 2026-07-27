#ifndef ORES_FUNCS
# define ORES_FUNCS

# include "map_structs.h"
# include "player_structs.h"

void    map_free(map *map);
void    map_gen(zone *actual_zone);
void    click_mining(player_data *player, float scale);

#endif