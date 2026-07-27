#ifndef WEAPONS_STRUCTS_H
# define WEAPONS_STRUCTS_H

typedef struct s_sword
{
    char    *name;

    int     str;
    int     cost;
    float   speed;

    int     *effects;
} sword;

typedef struct s_pickaxe
{
    char *name;

    int mining_str;
    int mining_sta;
    int cost;

    int *effects;
    int radius;
} pickaxe;

typedef struct s_armor
{
    char    *name;

    int     hp;
    int     str;
    int     speed;
    int     mining_str;
    int     mining_sta;

    int     *effects;
    int     slot;
    int     rarity;
} armor;

#endif