#include "weapons_structs.h"
#include "malloc.h"

pickaxe *p_fists(void)
{
    static pickaxe pick = {
        .name = "Fists",
        .cost = 0,
        .mining_str = 1,
        .mining_sta = 5,
        .effects = 0,
        .radius = 1
    };

    return (&pick);
}

pickaxe *p_stick(void)
{
    static pickaxe pick = {
        .name = "Stick",
        .cost = 20,
        .mining_str = 2,
        .mining_sta = 6,
        .effects = 0,
        .radius = 1
    };

    return (&pick);
}

pickaxe *p_wooden_pickaxe(void)
{
    static pickaxe pick = {
        .name = "Wooden Pickaxe",
        .cost = 150,
        .mining_str = 3,
        .mining_sta = 10,
        .effects = 0,
        .radius = 2
    };

    return (&pick);
}

pickaxe *p_wooden_hammer(void)
{
    static pickaxe pick = {
        .name = "Wooden Hammer",
        .cost = 650,
        .mining_str = 8,
        .mining_sta = 10,
        .effects = 0,
        .radius = 1
    };

    return (&pick);
}

pickaxe *p_stone_pickaxe(void)
{
    static pickaxe pick = {
        .name = "Stone Pickaxe",
        .cost = 1500,
        .mining_str = 15,
        .mining_sta = 12,
        .effects = 0,
        .radius = 2
    };

    return (&pick);
}

pickaxe *p_iron_pickaxe(void)
{
    static pickaxe pick = {
        .name = "Iron Pickaxe",
        .cost = 5000,
        .mining_str = 25,
        .mining_sta = 16,
        .effects = 0,
        .radius = 2
    };

    return (&pick);
}

pickaxe *p_golden_pickaxe(void)
{
    static pickaxe pick = {
        .name = "Golden Pickaxe",
        .cost = 20000,
        .mining_str = 60,
        .mining_sta = 20,
        .effects = 0,
        .radius = 2
    };

    return (&pick);
}

pickaxe *p_diamond_pickaxe(void)
{
    static pickaxe pick = {
        .name = "Diamond Pickaxe",
        .cost = 100000,
        .mining_str = 100,
        .mining_sta = 18,
        .effects = 0,
        .radius = 3
    };

    return (&pick);
}

pickaxe *p_electric_pickaxe(void)
{
    static pickaxe pick = {
        .name = "Electric Pickaxe",
        .cost = 250000,
        .mining_str = 180,
        .mining_sta = 18,
        .effects = 0,
        .radius = 4
    };

    return (&pick);
}

pickaxe *p_abyss_pickaxe(void)
{
    static pickaxe pick = {
        .name = "Abyss Pickaxe",
        .cost = 1000000,
        .mining_str = 310,
        .mining_sta = 24,
        .effects = 0,
        .radius = 3
    };

    return (&pick);
}

pickaxe **get_pickaxes(void)
{
    pickaxe **picks = malloc(10 * sizeof(pickaxe *));

    picks[0] = p_fists();
    picks[1] = p_stick();
    picks[2] = p_wooden_pickaxe();
    picks[3] = p_wooden_hammer();
    picks[4] = p_stone_pickaxe();
    picks[5] = p_iron_pickaxe();
    picks[6] = p_golden_pickaxe();
    picks[7] = p_diamond_pickaxe();
    picks[8] = p_electric_pickaxe();
    picks[9] = p_abyss_pickaxe();

    return (picks);

}
