#include "../includes/includes.h"

armor create_chestplate(char *name, a_params parameters, int rarity)
{
    armor armor;

    armor.name = name;
    armor.slot = 'c';
    armor.rarity = rarity;

    armor.hp = parameters.hp;
    armor.str = parameters.str;
    armor.speed = parameters.speed;
    armor.mining_sta = parameters.mining_sta;
    armor.mining_str = parameters.mining_str;
    
    return (armor);
}

armor shredded_t_shirt(void)
{
    a_params params;

    params.hp = 0;
    params.str = 0;
    params.speed = 0;
    params.mining_sta = 0;
    params.mining_str = 0;

    return (create_chestplate("Shredded T-shirt", params, common));
}

armor training_top(void)
{
    a_params params;

    params.hp = 10;
    params.str = 2;
    params.speed = 0;
    params.mining_sta = 1;
    params.mining_str = 1;

    return (create_chestplate("Training Top", params, common));
}
