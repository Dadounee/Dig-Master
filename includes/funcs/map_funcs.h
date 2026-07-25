#ifndef ORES_FUNCS
# define ORES_FUNCS

# include "map_structs.h"

void    map_free(map *map);
void    map_gen(zone *actual_zone);
void    click_mining(zone *infos, float scale);

#endif