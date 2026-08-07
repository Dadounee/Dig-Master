#ifndef PLAYER_FUNCS_h
# define PLAYER_FUNCS_h

# include "player_structs.h"

/*
    INVENTORY INIT RELATED STUFF
*/

void        OreInventoryFree(p_inventory *inv);
void        inventory_init(player_data *player);
void        inventories_free(player_data *player);
void        armor_inventory_init(player_data *player);
void        InventoryAdd(player_data *player, int minedX, int minedY);

/*
    WEAPON INIT RELATED STUFF
*/

void first_weapons(player_data *player);

/*
    PLAYER INIT RELATED STUFF
*/

player_data *player_init(void);
void        player_free(player_data *player);
void        changeState(player_data *player);


/*
    WEAPONS INV MANIP RELATED STUFF
*/

void        add_armor(weapons_inventory *w_inv, armor *armor);
void        add_armor_stats(player_data *player, armor *ar);
void        rem_armor_stats(player_data *player, armor *ar);
void        equip_pickaxe(player_data *player, pickaxe *pick);

/*
    UI FUNCS
*/
void    inventoryDisplay(void);

#endif