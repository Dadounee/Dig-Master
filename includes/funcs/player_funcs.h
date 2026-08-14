#ifndef PLAYER_FUNCS_h
# define PLAYER_FUNCS_h

# include "player_structs.h"

/*
    INVENTORY INIT RELATED STUFF
*/

void        OreInventoryFree(p_inventory *inv);
void        inventory_init(playerData *player);
void        inventories_free(playerData *player);
void        armor_inventory_init(playerData *player);
void        InventoryAdd(playerData *player, int minedX, int minedY);

/*
    WEAPON INIT RELATED STUFF
*/

void first_weapons(playerData *player);

/*
    PLAYER INIT RELATED STUFF
*/

playerData *player_init(void);
void        player_free(playerData *player);


/*
    WEAPONS INV MANIP RELATED STUFF
*/

void        add_armor(weapons_inventory *w_inv, armor *armor);
void        add_armor_stats(playerData *player, armor *ar);
void        rem_armor_stats(playerData *player, armor *ar);
void        equip_pickaxe(playerData *player, pickaxe *pick);

/*
    STAT SECTION FUNCS
*/
void    initPlayerStats(playerData *player);
void    applyPlayerStats(playerData *player);
void    applyOnePlayerStats(playerData *player, unsigned char stat);

#endif