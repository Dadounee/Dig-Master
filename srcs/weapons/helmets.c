#include "weapons_structs.h"
#include "ores_funcs.h"

armor *plain_armor(void)
{
    static armor plain={
        .name = "\0",
        .slot = ' ',
        .hp = 0,
        .str = 0,
        .speed = 0,
        .mining_sta = 0,
        .mining_str = 0
    };

    return (&plain);
}

armor *h_broken(void)
{
    static armor helmet={
        .name = "Broken Helmet",
        .slot = 'h',
        .hp = 1,
        .str = 0,
        .speed = 0,
        .mining_sta = 0,
        .mining_str = 0,
        .rarity = common
    };

    return (&helmet);
}

armor *h_training(void)
{
    static armor helmet={
        .name = "Training Helmet",
        .slot = 'h',
        .hp = 5,
        .str = 2,
        .speed = 0,
        .mining_sta = 1,
        .mining_str = 0,
        .rarity = common
    };

    return (&helmet);
}
