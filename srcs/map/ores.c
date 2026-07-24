#include "map_structs.h"

ore *dirt(void)
{
    static const ore dirt={
        .name="Dirt",
        .rarity=common,

        .durability=1,
        .value=1
    };
}

ore *grass(void)
{
    static const ore grass={
        .name="Grass",
        .rarity=common,

        .durability=2,
        .value=3
    };

    return (&grass);
}

ore *stone(void)
{
    static const ore stone={
        .name="Stone",
        .rarity=common,

        .durability=3,
        .value=5
    };

    return (&stone);
}

ore *tough_stone(void)
{
    static const ore tough_stone={
        .name="Tough Stone",
        .rarity=common,

        .durability=20,
        .value=15
    };

    return (&tough_stone);
}

ore *deep_stone(void)
{
    static const ore deep_stone={
        .name="Deep Stone",
        .rarity=uncommon,

        .durability=80,
        .value=50
    };

    return (&deep_stone);
}

ore *abyss_stone(void)
{
    static const ore abyss_stone={
        .name="Abyss Stone",
        .rarity=rare,

        .durability=250,
        .value=175
    };

    return (&abyss_stone);
}

ore *coal(void)
{
    static const ore coal={
        .name="Coal",
        .rarity=uncommon,

        .durability=6,
        .value=12
    };

    return (&coal);
}

ore *copper(void)
{
    static const ore copper={
        .name="Copper",
        .rarity=uncommon,

        .durability=10,
        .value=25
    };

    return (&copper);
}

ore *iron(void)
{
    static const ore iron={
        .name="Iron",
        .rarity=uncommon,

        .durability=20,
        .value=50
    };

    return (&iron);
}

ore *silver(void)
{
    static const ore silver={
        .name="Silver",
        .rarity=rare,

        .durability=50,
        .value=200
    };

    return (&silver);
}

ore *amethyst(void)
{
    static const ore amethyst={
        .name="Amethyst",
        .rarity=rare,

        .durability=75,
        .value=250
    };

    return (&amethyst);
}

ore *gold(void)
{
    static const ore gold={
        .name="Gold",
        .rarity=epic,

        .durability=125,
        .value=500
    };

    return (&gold);
}

ore *emerald(void)
{
    static const ore emerald={
        .name="Emerald",
        .rarity=epic,

        .durability=200,
        .value=750
    };

    return (&emerald);
}

ore *saphire(void)
{
    static const ore saphire={
        .name="Saphire",
        .rarity=legendary,

        .durability=350,
        .value=1200
    };

    return (&saphire);
}

ore *ruby(void)
{
    static const ore ruby={
        .name="Ruby",
        .rarity=legendary,

        .durability=425,
        .value=1550
    };

    return (&ruby);
}

ore *diamond(void)
{
    static const ore diamond={
        .name="Diamond",
        .rarity=legendary,

        .durability=600,
        .value=2500
    };

    return (&diamond);
}

ore *uranium(void)
{
    static const ore uranium={
        .name="Uranium",
        .rarity=unobtainable,

        .durability=1000,
        .value=6000
    };

    return (&uranium);
}
