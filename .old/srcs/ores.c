#include "../includes/includes.h"


/*
ore create_ore(char *name, int rarity, int durability, int value, char *color)

creates an ore with the given parameters, will return it
*/
ore create_ore(char *name, int rarity, int durability, int value, char *color)
{
    ore ore;
    ore.name = (char *)malloc(strlen(name) * sizeof(char));
    ore.name = name;
    ore.color = (char *)malloc(strlen(color) * sizeof(char));
    ore.color = color;
    ore.rarity = rarity;
    ore.durability = durability;
    ore.value = value;
    return (ore);
}

void    free_ore(ore *mineral)
{
    if (mineral != NULL)
    {
        free(mineral->name);
        free(mineral->color);
    }
}

ore dirt(void)
{
    return (create_ore("dirt", common, 1, 1, TC_YEL));
}

ore grass(void)
{
    return (create_ore("grass", common, 2, 3, TC_GRN));
}

ore stone(void)
{
    return (create_ore("stone", common, 3, 5, TC_GRY));
}

ore tough_stone(void)
{
    return (create_ore("tough_stone", common, 20, 15, TC_GRY));
}

ore deep_stone(void)
{
    return (create_ore("deep_stone", uncommon, 80, 50, TC_GRY));
}

ore abyss_stone(void)
{
    return (create_ore("abyss_stone", rare, 250, 175, TC_GRY));
}

ore coal(void)
{
    return (create_ore("coal", uncommon, 6, 12, TC_BLK));
}

ore copper(void)
{
    return (create_ore("copper", uncommon, 10, 25, TC_YEL));
}

ore iron(void)
{
    return (create_ore("iron", uncommon, 20, 50, TC_WHT));
}

ore silver(void)
{
    return (create_ore("silver", rare, 50, 200, TC_WHT));
}

ore amethyst(void)
{
    return (create_ore("amethyst", rare, 75, 250, TC_MAG));
} 

ore gold(void)
{
    return (create_ore("gold", epic, 125, 500, TC_BYL));
}

ore emerald(void)
{
    return (create_ore("emerald", epic, 200, 750, TC_GRN));
}

ore saphire(void)
{
    return (create_ore("saphire", legendary, 350, 1200, TC_BLU));
}

ore ruby(void)
{
    return (create_ore("ruby", legendary, 425, 1550, TC_RED));
}

ore diamond(void)
{
    return (create_ore("diamond", legendary, 600, 2500, TC_BBL));
}

ore uranium(void)
{
    return (create_ore("uranium", unobtainable, 1000, 6000, TC_BGR));
}
