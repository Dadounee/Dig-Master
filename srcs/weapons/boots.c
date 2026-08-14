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
        .staminaBoost = 0,
        .miningStr = 0,
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
        .staminaBoost = 2,
        .miningStr = 0,
        .rarity=common
    };

    return (&boots);
}