#include "weapons_structs.h"
#include "ores_funcs.h"

armor *l_broken(void)
{
    static armor leggings={
        .name = "Shredded Jean",
        .slot = 'l',
        .hp = 1,
        .str = 0,
        .speed = 0,
        .mining_sta = 0,
        .mining_str = 0,
        .rarity = common
    };

    return (&leggings);
}

armor *l_training(void)
{
    static armor leggings={
        .name = "Training leggings",
        .slot = 'l',
        .hp = 4,
        .str = 0,
        .speed = 2,
        .mining_sta = 2,
        .mining_str = 1,
        .rarity = common
    };

    return (&leggings);
}
