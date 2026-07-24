#ifndef MAP_STRUCT_H
# define MAP_STRUCT_H

# include <stdbool.h>

typedef enum e_type
{
    empty,
    mineral,
    monster,
    crate
} space_type;

typedef enum e_rarity
{
    common,
    uncommon,
    rare,
    epic,
    legendary,
    unobtainable
} ore_rarity;

typedef struct s_ore
{
    char    *name;

    int     rarity;
    int     durability;
    int     value;
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
    ore     *mined;

} map;

typedef struct s_zone
{
    char    *name;
    
    ore     (**available_ores)(void);
    int     (*ores_density)(void);
    int     void_density;
    int     ennemies_density;

    int     price;
    int     ore_nb;

    map     mine_map;
    bool    is_map;
} zone;

typedef struct s_map_params
{
    int ore_nb;
    int len;
    int height;
    int void_density;
    int price;
} map_params;

#endif