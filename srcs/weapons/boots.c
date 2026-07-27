#include "weapons_structs.h"
#include "map_structs.h"

armor *b_broken(void)
{
    static armor boots = {
        .name = "Broken Boots",
        .slot = 'b',
        .hp = 1,
        .str = 0,
        .speed = 0,
        .mining_sta = 0,
        .mining_str = 0,
        .rarity=common
    };

    return (&boots);
}

armor *b_training(void)
{
    static armor boots = {
        .name = "Training Boots",
        .slot = 'b',
        .hp = 3,
        .str = 1,
        .speed = 2,
        .mining_sta = 2,
        .mining_str = 0,
        .rarity=common
    };

    return (&boots);
}