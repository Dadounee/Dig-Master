#ifndef DISPLAY_FUNCS_H
# define DISPLAY_FUNCS_H

# include "map_structs.h"

void    DisplayMap(zone *infos, float scale, int blocked);
void    DisplayPlayerInv(player_data *player, float scale);
void    DisplayPlayerInfos(player_data *player, float scale);

#endif