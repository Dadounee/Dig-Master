#include "../includes/includes.h"

armor create_leggings(char *name, a_params parameters, int rarity)
{
    armor armor;

    armor.name = name;
    armor.slot = 'l';
    armor.rarity = rarity;

    armor.hp = parameters.hp;
    armor.str = parameters.str;
    armor.speed = parameters.speed;
    armor.mining_sta = parameters.mining_sta;
    armor.mining_str = parameters.mining_str;
    
    return (armor);
}

armor shreadded_jean(void)
{
    a_params params;

    params.hp = 0;
    params.str = 0;
    params.speed = 0;
    params.mining_sta = 0;
    params.mining_str = 0;

    return (create_leggings("Shredded Jean", params, common));
}

armor training_jean(void)
{
    a_params params;

    params.hp = 4;
    params.str = 0;
    params.speed = 2;
    params.mining_sta = 2;
    params.mining_str = 1;

    return (create_leggings("Training Jean", params, common));
}
