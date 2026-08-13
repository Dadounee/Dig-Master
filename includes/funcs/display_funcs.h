#ifndef DISPLAY_FUNCS_H
# define DISPLAY_FUNCS_H

# include "map_structs.h"


    // ui display funcs
    void    DisplayMap(zone *infos, float scale, int blocked);
    void    DisplayPlayerInv(player_data *player, float scale);
    void    DisplayPlayerInfos(player_data *player, float scale);
    void    sellMenuDisplay(player_data *player);
    void    inventoryDisplay(void);

    // button creation related functions here
    void    invButtonClick(void *infos);
    void    invButtonDisplay(void *infos, void *infos2, bool isHovered);
    void    returnBtnClick(void *infos);
    void    returnBtnDisplay(void *infos, void *infos2, bool isHovered);
    void    sellButtonClick(void *infos);
    void    sellButtonDisplay(void *infos, void *infos2, bool isHovered);
    void    sellInvClick(void *infos);
    void    sellInvDisplay(void *infos, void *infos2, bool isHovered);

#endif