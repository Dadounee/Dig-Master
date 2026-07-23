#include "../includes/includes.h"

pickaxe create_pick(char *name, int cost, int str, int sta)
{
    pickaxe pickaxe;

    pickaxe.name = name;
    pickaxe.cost = cost;
    pickaxe.mining_str = str;
    pickaxe.mining_sta = sta;

    return (pickaxe);
}

pickaxe p_fists(void)
{
    pickaxe pickaxe;

    pickaxe = create_pick("Fists", 0, 1, 5);
    pickaxe.effects = NULL;
    pickaxe.radius = &radius_1;

    return (pickaxe);
}

pickaxe p_stick(void)
{
    pickaxe pickaxe;

    pickaxe = create_pick("Stick", 20, 2, 6);
    pickaxe.effects = NULL;
    pickaxe.radius = &radius_1;

    return (pickaxe);
}

pickaxe p_wooden_pickaxe(void)
{
    pickaxe pickaxe;

    pickaxe = create_pick("Wooden Pickaxe", 150, 3, 10);
    pickaxe.effects = NULL;
    pickaxe.radius = &radius_1;

    return (pickaxe);
}

pickaxe p_wooden_hammer(void)
{
    pickaxe pickaxe;

    pickaxe = create_pick("Wooden Hammer", 1000, 8, 10);
    pickaxe.effects = NULL;
    pickaxe.radius = &radius_0;

    return (pickaxe);
}

pickaxe p_stone_pickaxe(void)
{
    pickaxe pickaxe;

    pickaxe = create_pick("Stone Pickaxe", 2500, 15, 12);
    pickaxe.effects = NULL;
    pickaxe.radius = &radius_2;

    return (pickaxe);
}

pickaxe p_iron_pickaxe(void)
{
    pickaxe pickaxe;

    pickaxe = create_pick("Iron Pickaxe", 8000, 25, 16);
    pickaxe.effects = NULL;
    pickaxe.radius = &radius_1;

    return (pickaxe);
}

pickaxe p_golden_pickaxe(void)
{
    pickaxe pickaxe;

    pickaxe = create_pick("Golden Pickaxe", 20000, 60, 20);
    pickaxe.effects = NULL;
    pickaxe.radius = &radius_1;

    return (pickaxe);
}

pickaxe p_diamond_pickaxe(void)
{
    pickaxe pickaxe;

    pickaxe = create_pick("Diamond Pickaxe", 60000, 100, 22);
    pickaxe.effects = NULL;
    pickaxe.radius = &radius_2;

    return (pickaxe);
}

pickaxe p_electric_pickaxe(void)
{
    pickaxe pickaxe;

    pickaxe = create_pick("Electrric Pickaxe", 150000, 180, 21);
    pickaxe.effects = NULL;
    pickaxe.radius = &radius_3;

    return (pickaxe);
}

pickaxe p_abyss_pickaxe(void)
{
    pickaxe pickaxe;

    pickaxe = create_pick("Abyss Pickaxe", 500000, 310, 24);
    pickaxe.effects = NULL;
    pickaxe.radius = &radius_2;

    return (pickaxe);
}

pickaxe *get_pickaxes(void)
{
    pickaxe *picks = malloc(10 * sizeof(pickaxe));

    picks[0] = p_fists();
    picks[1] = p_stick();
    picks[2] = p_wooden_pickaxe();
    picks[3] = p_wooden_hammer();
    picks[4] = p_stone_pickaxe();
    picks[5] = p_iron_pickaxe();
    picks[6] = p_golden_pickaxe();
    picks[7] = p_diamond_pickaxe();
    picks[8] = p_electric_pickaxe();
    picks[9] = p_abyss_pickaxe();

    return (picks);

}
