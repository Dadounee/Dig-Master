#include "../includes/includes.h"

armor plain_armor(void)
{
    armor ar;

    ar.name = "\0";
    ar.hp = 0;
    ar.str = 0;
    ar.speed = 0;
    ar.mining_sta = 0;
    ar.mining_str = 0;

    return (ar);
}

armor create_helmet(char *name, a_params parameters, int rarity)
{
    armor armor;

    armor.name = name;
    armor.slot = 'h';
    armor.rarity = rarity;

    armor.hp = parameters.hp;
    armor.str = parameters.str;
    armor.speed = parameters.speed;
    armor.mining_sta = parameters.mining_sta;
    armor.mining_str = parameters.mining_str;
    
    return (armor);
}

armor broken_helmet(void)
{
    a_params params;

    params.hp = 0;
    params.str = 0;
    params.speed = 0;
    params.mining_sta = 0;
    params.mining_str = 0;

    return (create_helmet("Broken Helmet", params, common));
}

armor training_helmet(void)
{
    a_params params;

    params.hp = 5;
    params.str = 2;
    params.speed = 0;
    params.mining_sta = 1;
    params.mining_str = 0;

    return (create_helmet("Training Helmet", params, common));
}
