#include "map_structs.h"
#include "malloc.h"
#include <unistd.h>

ore *dirt(void)
{
    static ore dirt={
        .name="Dirt",
        .rarity=common,

        .durability=1,
        .value=1,

        .fileName = "assets/ores/dirt.png"
    };

    return (&dirt);
}

ore *grass(void)
{
    static ore grass={
        .name="Grass",
        .rarity=common,

        .durability=2,
        .value=3,

        .fileName = "assets/ores/grass.png"
    };

    return (&grass);
}

ore *stone(void)
{
    static ore stone={
        .name="Stone",
        .rarity=common,

        .durability=3,
        .value=5,

        .fileName = "assets/ores/stone.png"
    };

    return (&stone);
}

ore *tough_stone(void)
{
    static ore tough_stone={
        .name="Tough Stone",
        .rarity=common,

        .durability=20,
        .value=15,

        .fileName = "assets/ores/stone.png"
    };

    return (&tough_stone);
}

ore *deep_stone(void)
{
    static ore deep_stone={
        .name="Deep Stone",
        .rarity=uncommon,

        .durability=80,
        .value=50,

        .fileName = "assets/ores/stone.png"
    };

    return (&deep_stone);
}

ore *abyss_stone(void)
{
    static ore abyss_stone={
        .name="Abyss Stone",
        .rarity=rare,

        .durability=250,
        .value=175,

        .fileName = "assets/ores/stone.png"
    };

    return (&abyss_stone);
}

ore *coal(void)
{
    static ore coal={
        .name="Coal",
        .rarity=uncommon,

        .durability=6,
        .value=12,

        .fileName = "assets/ores/coal.png"
    };

    return (&coal);
}

ore *copper(void)
{
    static ore copper={
        .name="Copper",
        .rarity=uncommon,

        .durability=10,
        .value=25,

        .fileName = "assets/ores/copper.png"
    };

    return (&copper);
}

ore *iron(void)
{
    static ore iron={
        .name="Iron",
        .rarity=uncommon,

        .durability=20,
        .value=50,

        .fileName = "assets/ores/dirt.png"
    };

    return (&iron);
}

ore *silver(void)
{
    static ore silver={
        .name="Silver",
        .rarity=rare,

        .durability=50,
        .value=200,

        .fileName = "assets/ores/dirt.png"
    };

    return (&silver);
}

ore *amethyst(void)
{
    static ore amethyst={
        .name="Amethyst",
        .rarity=rare,

        .durability=75,
        .value=250,

        .fileName = "assets/ores/dirt.png"
    };

    return (&amethyst);
}

ore *gold(void)
{
    static ore gold={
        .name="Gold",
        .rarity=epic,

        .durability=125,
        .value=500,

        .fileName = "assets/ores/dirt.png"
    };

    return (&gold);
}

ore *emerald(void)
{
    static ore emerald={
        .name="Emerald",
        .rarity=epic,

        .durability=200,
        .value=750,

        .fileName = "assets/ores/dirt.png"
    };

    return (&emerald);
}

ore *saphire(void)
{
    static ore saphire={
        .name="Saphire",
        .rarity=legendary,

        .durability=350,
        .value=1200,

        .fileName = "assets/ores/dirt.png"
    };

    return (&saphire);
}

ore *ruby(void)
{
    static ore ruby={
        .name="Ruby",
        .rarity=legendary,

        .durability=425,
        .value=1550,

        .fileName = "assets/ores/dirt.png"
    };

    return (&ruby);
}

ore *diamond(void)
{
    static ore diamond={
        .name="Diamond",
        .rarity=legendary,

        .durability=600,
        .value=2500,

        .fileName = "assets/ores/dirt.png"
    };

    return (&diamond);
}

ore *uranium(void)
{
    static ore uranium={
        .name="Uranium",
        .rarity=unobtainable,

        .durability=1000,
        .value=6000,

        .fileName = "assets/ores/dirt.png"
    };

    return (&uranium);
}

ore *empty(void)
{
    static ore uranium={
        .name="Empty",
        .rarity=unobtainable,

        .durability=0,
        .value=0,

        .fileName = "assets/ores/empty.png"
    };

    return (&uranium);
}

/*
    there are currently 17 ores

        this will be usefull to load textures ( ;( memory leaks )

    will just return an array filled with pointers to all 17 ores

*/
ore **get_ores(void)
{
    ore **all_ores;

    all_ores = malloc(sizeof(zone *) * 18);
    all_ores[0] = dirt();
    all_ores[1] = coal();
    all_ores[2] = iron();
    all_ores[3] = gold();
    all_ores[4] = ruby();
    all_ores[5] = grass();
    all_ores[6] = stone();
    all_ores[7] = copper();
    all_ores[8] = silver();
    all_ores[9] = emerald();
    all_ores[10] = saphire();
    all_ores[11] = diamond();
    all_ores[12] = uranium();
    all_ores[13] = amethyst();
    all_ores[14] = deep_stone();
    all_ores[15] = tough_stone();
    all_ores[16] = abyss_stone();
    all_ores[17] = empty();

    return (all_ores);
}

void    load_ores_textures(int screenWidth, float scale)
{
    ore     **ores = get_ores();
    int i = 0;
    // bool    can_load = true;

    while (i < 18)
    {
        ores[i]->image = LoadImage(ores[i]->fileName);
        if (IsImageValid(ores[i]->image))
        {
            ImageResize(&ores[i]->image, screenWidth / TILE_PROPORTION * scale, screenWidth / TILE_PROPORTION * scale);
            ores[i]->texture = LoadTextureFromImage(ores[i]->image);
        }
        UnloadImage(ores[i]->image);
        write(1, "\n", 1);
        i++;
    }
    free(ores);
}
