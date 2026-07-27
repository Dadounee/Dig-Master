#include "weapons_structs.h"
#include "ores_funcs.h"

armor *c_broken(void)
{
    static armor chest={
        .name = "Shredded T-shirt",
        .slot = 'c',
        .hp = 1,
        .str = 0,
        .speed = 0,
        .mining_sta = 0,
        .mining_str = 0,
        .rarity = common
    };

    return (&chest);
}

armor *c_training(void)
{
    static armor chest={
        .name = "Training Top",
        .slot = 'c',
        .hp = 10,
        .str = 2,
        .speed = 0,
        .mining_sta = 1,
        .mining_str = 1,
        .rarity = common
    };

    return (&chest);
}
