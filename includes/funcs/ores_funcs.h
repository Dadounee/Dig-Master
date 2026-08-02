#ifndef ORES_FUNCS
# define ORES_FUNCS

# include "map_structs.h"

ore *dirt(void);
ore *coal(void);
ore *iron(void);
ore *gold(void);
ore *ruby(void);
ore *grass(void);
ore *stone(void);
ore *empty(void);
ore *copper(void);
ore *silver(void);
ore *emerald(void);
ore *saphire(void);
ore *diamond(void);
ore *uranium(void);
ore *amethyst(void);
ore *deep_stone(void);
ore *tough_stone(void);
ore *abyss_stone(void);

ore **get_ores(void);

void    load_ores_textures(int screenWidth, float scale);

void    map_free(map *map);
void    map_gen(zone *actual_zone);

void    tile_info(map *mine_map, float scale);
#endif