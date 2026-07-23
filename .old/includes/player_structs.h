#ifndef PLAYER_STRUCT_H
# define PLAYER_STRUCT_H

# include "weapons_structs.h"
# include "map_structs.h"

typedef struct s_p_inv
{
    int     inv_upgrades;
    int     inv_size;
    int     used_slots;
    ore     *inv;

} p_inventory;

typedef struct s_w_inv
{
    int     inv_upgrades;
    int     inv_size;
    int     used_slots;
    armor   *inv;

} weapons_inventory;


typedef struct s_weapons
{
    pickaxe     pickaxe;
    sword       sword;

    armor       helmet;
    armor       chestplate;
    armor       leggings;
    armor       boots;

} weapons;


typedef struct s_player_data
{
    zone                *actual_zone;
    weapons             *equipped_weapons;
    p_inventory         *inv;
    weapons_inventory   *weapons_inv;

    bool                *unlocked_zones;
    bool                *unlocked_pickaxes;

    long long           money;
    int                 crates[1];

    int                 hp;
    int                 def;
    int                 str;
    int                 speed;
    int                 mining_str;
    int                 mining_sta;
    int                 luck_mult;
    int                 money_multiplier;

} player_data;

typedef struct s_player_statistics
{
    int     exp;
} statistics;
#endif