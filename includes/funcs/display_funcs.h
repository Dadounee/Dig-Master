#ifndef DISPLAY_FUNCS_H
# define DISPLAY_FUNCS_H

# include "map_structs.h"


    // ui display funcs
    void    DisplayMap(zone *infos, float scale, int blocked);
    void    DisplayPlayerInv(playerData *player, float scale);
    void    DisplayPlayerInfos(playerData *player, float scale);
    void    sellMenuDisplay(playerData *player);
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