#ifndef PLAYER_STRUCT_H
# define PLAYER_STRUCT_H

# include "weapons_structs.h"
# include "map_structs.h"

# define BASE_HP 100
# define BASE_DEF 5
# define BASE_STR 2
# define BASE_SPEED 1
# define BASE_LUCK 1
# define BASE_MONEY 0
# define BASE_MULT 1

typedef struct s_p_inv
{
    int     inv_upgrades;
    int     inv_size;
    ore     **inv;
    int     *counts;

} p_inventory;

typedef struct s_w_inv
{
    int     inv_upgrades;
    int     inv_size;
    int     count;
    armor   **inv;

} weapons_inventory;


typedef struct s_weapons
{
    pickaxe     *pickaxe;
    sword       *sword;

    armor       *helmet;
    armor       *chestplate;
    armor       *leggings;
    armor       *boots;

} weapons;


typedef struct s_player_data
{
    zone                *actual_zone;
    weapons             equipped_weapons;
    p_inventory         *inv;
    weapons_inventory   *weapons_inv;

    bool                unlocked_zones[6];
    bool                unlocked_pickaxes[10];

    long long           money;
    int                 crates[1];

    int                 hp;
    int                 def;
    int                 str;
    int                 speed;
    int                 mining_str;
    int                 mining_sta;
    int                 actual_sta;
    int                 luck_mult;
    int                 money_multiplier;

} player_data;

typedef struct s_player_statistics
{
    int     exp;
} statistics;

#endif