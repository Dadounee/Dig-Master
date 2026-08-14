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
# define BASE_STAMINA 100

    typedef enum s_game_state {
        MINING,
        INVENTORY,
        SELLMENU
    } gameState;

    typedef struct s_p_inv
    {
        int     inv_upgrades;
        int     inv_size;
        ore     **inv;
        int     *counts;
        int     oreCount;

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

    typedef struct s_player_statistics
    {
        unsigned int    exp;
        unsigned int    level;
        unsigned int    dayCount;
        
        unsigned short  baseStaBoost;
        unsigned int    multStaBoost;
        
        unsigned short  baseHpBoost;
        unsigned int    multHpBoost;
        
        unsigned short  baseDefBoost;
        unsigned int    multDefBoost;
        
        unsigned short  baseStrBoost;
        unsigned int    multStrBoost;
        
        unsigned short  baseLuckBoost;
        unsigned int    multLuckBoost;
        
        unsigned short  baseSpeedBoost;
        unsigned int    multSpeedBoost;
        
        unsigned int    moneyMult;
        
    } statistics;

    typedef struct s_playerData
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
        int                 miningStr;
        int                 actualSta;
        int                 luck;

        bool                display_actualisation;
        unsigned char       oldState;
        unsigned char       gameState;
        
        statistics          playerStats;
    } playerData;

#endif