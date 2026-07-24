#include "map_structs.h"

ore *dirt(void)
{
    static ore dirt={
        .name="Dirt",
        .rarity=common,

        .durability=1,
        .value=1
    };

    return (&dirt);
}

ore *grass(void)
{
    static ore grass={
        .name="Grass",
        .rarity=common,

        .durability=2,
        .value=3
    };

    return (&grass);
}

ore *stone(void)
{
    static ore stone={
        .name="Stone",
        .rarity=common,

        .durability=3,
        .value=5
    };

    return (&stone);
}

ore *tough_stone(void)
{
    static ore tough_stone={
        .name="Tough Stone",
        .rarity=common,

        .durability=20,
        .value=15
    };

    return (&tough_stone);
}

ore *deep_stone(void)
{
    static ore deep_stone={
        .name="Deep Stone",
        .rarity=uncommon,

        .durability=80,
        .value=50
    };

    return (&deep_stone);
}

ore *abyss_stone(void)
{
    static ore abyss_stone={
        .name="Abyss Stone",
        .rarity=rare,

        .durability=250,
        .value=175
    };

    return (&abyss_stone);
}

ore *coal(void)
{
    static ore coal={
        .name="Coal",
        .rarity=uncommon,

        .durability=6,
        .value=12
    };

    return (&coal);
}

ore *copper(void)
{
    static ore copper={
        .name="Copper",
        .rarity=uncommon,

        .durability=10,
        .value=25
    };

    return (&copper);
}

ore *iron(void)
{
    static ore iron={
        .name="Iron",
        .rarity=uncommon,

        .durability=20,
        .value=50
    };

    return (&iron);
}

ore *silver(void)
{
    static ore silver={
        .name="Silver",
        .rarity=rare,

        .durability=50,
        .value=200
    };

    return (&silver);
}

ore *amethyst(void)
{
    static ore amethyst={
        .name="Amethyst",
        .rarity=rare,

        .durability=75,
        .value=250
    };

    return (&amethyst);
}

ore *gold(void)
{
    static ore gold={
        .name="Gold",
        .rarity=epic,

        .durability=125,
        .value=500
    };

    return (&gold);
}

ore *emerald(void)
{
    static ore emerald={
        .name="Emerald",
        .rarity=epic,

        .durability=200,
        .value=750
    };

    return (&emerald);
}

ore *saphire(void)
{
    static ore saphire={
        .name="Saphire",
        .rarity=legendary,

        .durability=350,
        .value=1200
    };

    return (&saphire);
}

ore *ruby(void)
{
    static ore ruby={
        .name="Ruby",
        .rarity=legendary,

        .durability=425,
        .value=1550
    };

    return (&ruby);
}

ore *diamond(void)
{
    static ore diamond={
        .name="Diamond",
        .rarity=legendary,

        .durability=600,
        .value=2500
    };

    return (&diamond);
}

ore *uranium(void)
{
    static ore uranium={
        .name="Uranium",
        .rarity=unobtainable,

        .durability=1000,
        .value=6000
    };

    return (&uranium);
}
