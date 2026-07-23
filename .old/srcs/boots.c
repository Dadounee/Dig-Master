#include "../includes/includes.h"

armor create_boots(char *name, a_params parameters, int rarity)
{
    armor armor;

    armor.name = name;
    armor.slot = 'b';
    armor.rarity = rarity;

    armor.hp = parameters.hp;
    armor.str = parameters.str;
    armor.speed = parameters.speed;
    armor.mining_sta = parameters.mining_sta;
    armor.mining_str = parameters.mining_str;
    
    return (armor);
}

armor broken_boots(void)
{
    a_params params;

    params.hp = 0;
    params.str = 0;
    params.speed = 0;
    params.mining_sta = 0;
    params.mining_str = 0;

    return (create_boots("Broken Boots", params, common));
}

armor training_boots(void)
{
    a_params params;

    params.hp = 3;
    params.str = 1;
    params.speed = 2;
    params.mining_sta = 2;
    params.mining_str = 0;

    return (create_boots("Training Boots", params, common));
}