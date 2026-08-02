#ifndef MAP_STRUCT_H
# define MAP_STRUCT_H

# include <stdbool.h>
# include "raylib.h"

# define TILE_PROPORTION 30
# define ORE_NUMBER 18

typedef enum e_type
{
    MINERAL,
    MONSTER,
    CRATE
} space_type;

typedef enum e_rarity
{
    common,
    uncommon,
    rare,
    epic,
    legendary,
    unobtainable
} rarity;

typedef struct s_ore
{
    int     id;
    char    *name;

    int     rarity;
    int     durability;
    int     value;

    char        *fileName;
    Image       image; // not that i need to detect if player has a gc
    Texture2D   texture;
} ore;

typedef struct s_space
{
    space_type  s_type;
    bool        discovered;

    ore         ore;
    int         durability;

    int         monster;
    int         level;

    int         rarity;
} space;

typedef struct s_maps
{
    int     map_len;
    int     map_height;

    space   **map;

} map;

typedef struct s_zone
{
    char    *name;
    
    ore     **(*available_ores)(void);
    int     *(*ores_density)(void);
    int     ennemies_density;

    int     price;
    int     ore_nb;

    map     mine_map;
    bool    is_map;
} zone;


#endif