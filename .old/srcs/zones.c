#include "../includes/includes.h"

/*
static const zone zones[] =
{
    {
        .name = "Surface",
        .available_ores = surface_ores,
        .probability = surface_prob,
        .mine_map = {.map_len = 9, .map_height = 9},
        .void_density = 5,
        .price = 0,
        .ore_nb = 3
    },
    {
        .name = "Crust",
        ...
    }
};
*/


zone *create_zone(char *name, ore *available_ores, int *probability, map_params parameters)
{
    zone *zonee;

    zonee = malloc(sizeof(zone));
    zonee->name = (char *)malloc(strlen(name) * sizeof(char));
    zonee->name = name;

    zonee->available_ores = available_ores;
    zonee->probability = probability;
    
    zonee->mine_map.map_len = parameters.len;
    zonee->mine_map.map_height = parameters.height;
    zonee->void_density = parameters.void_density;
    zonee->is_map = 0;
    zonee->price = parameters.price;
    zonee->ore_nb = parameters.ore_nb;

    return (zonee);
}

void zone_free(zone *zone)
{
    free(zone->probability);
    if (zone->is_map)
    {
        free(zone->name);
        map_free(&zone->mine_map);
    }
    free(zone);
}

zone *z_surface(void)
{
    int         *probability;
    ore         *available_ores;
    map_params  params;

    available_ores = (ore *)malloc(3 * sizeof(ore));
    available_ores[0] = dirt();
    available_ores[1] = grass();
    available_ores[2] = stone();

    probability = (int *)malloc(4 * sizeof(int));
    probability[0] = 0;
    probability[1] = 500;
    probability[2] = 800;
    probability[3] = 1000;

    params.len = 9;
    params.height = 9;
    params.void_density = 5;
    params.price = 0;
    params.ore_nb = 3;

    return (create_zone("Surface", available_ores, probability, params));
}

zone *z_crust(void)
{
    int         *probability;
    ore         *available_ores;
    map_params  params;

    available_ores = (ore *)malloc(4 * sizeof(ore));
    available_ores[0] = stone();
    available_ores[1] = coal();
    available_ores[2] = copper();
    available_ores[3] = iron();

    probability = (int *)malloc(5 * sizeof(int));
    probability[0] = 0;
    probability[1] = 500;
    probability[2] = 750;
    probability[3] = 900;
    probability[4] = 1000;

    params.len = 11;
    params.height = 11;
    params.void_density = 5;
    params.price = 1000;
    params.ore_nb = 4;

    return (create_zone("Crust", available_ores, probability, params));
}

zone *z_upper_mantle(void)
{
    int         *probability;
    ore         *available_ores;
    map_params  params;

    available_ores = (ore *)malloc(6 * sizeof(ore));
    available_ores[0] = tough_stone();
    available_ores[1] = stone();
    available_ores[2] = copper();
    available_ores[3] = iron();
    available_ores[4] = silver();
    available_ores[5] = amethyst();

    probability = (int *)malloc(7 * sizeof(int));
    probability[0] = 0;
    probability[1] = 250;
    probability[2] = 500;
    probability[3] = 700;
    probability[4] = 850;
    probability[5] = 950;
    probability[6] = 1000;

    params.len = 12;
    params.height = 10;
    params.void_density = 5;
    params.price = 10000;
    params.ore_nb = 6;

    return (create_zone("Upper Mantel", available_ores, probability, params));
}

zone *z_lower_mantel(void)
{
    int         *probability;
    ore         *available_ores;
    map_params  params;

    available_ores = (ore *)malloc(4 * sizeof(ore));
    available_ores[0] = deep_stone();
    available_ores[1] = gold();
    available_ores[2] = emerald();
    available_ores[3] = saphire();

    probability = (int *)malloc(5 * sizeof(int));
    probability[0] = 0;
    probability[1] = 600;
    probability[2] = 800;
    probability[3] = 925;
    probability[4] = 1000;

    params.len = 10;
    params.height = 10;
    params.void_density = 0;
    params.price = 50000;
    params.ore_nb = 4;

    return (create_zone("Lower Mantel", available_ores, probability, params));
}

zone *z_core(void)
{
    int         *probability;
    ore         *available_ores;
    map_params  params;

    available_ores = (ore *)malloc(4 * sizeof(ore));
    available_ores[0] = deep_stone();
    available_ores[1] = saphire();
    available_ores[2] = ruby();
    available_ores[3] = diamond();

    probability = (int *)malloc(5 * sizeof(int));
    probability[0] = 0;
    probability[1] = 500;
    probability[2] = 800;
    probability[3] = 960;
    probability[4] = 1000;

    params.len = 9;
    params.height = 9;
    params.void_density = 10;
    params.price = 250000;
    params.ore_nb = 4;

    return (create_zone("Core", available_ores, probability, params));
}

zone *z_abyss(void)
{
    int         *probability;
    ore         *available_ores;
    map_params  params;

    available_ores = (ore *)malloc(4 * sizeof(ore));
    available_ores[0] = abyss_stone();
    available_ores[1] = ruby();
    available_ores[2] = diamond();
    available_ores[3] = uranium();

    probability = (int *)malloc(5 * sizeof(int));
    probability[0] = 0;
    probability[1] = 550;
    probability[2] = 800;
    probability[3] = 925;
    probability[4] = 1000;

    params.len = 15;
    params.height = 12;
    params.void_density = 8;
    params.price = 1000000;
    params.ore_nb = 4;

    return (create_zone("Abyss", available_ores, probability, params));
}

zone *get_zones(void)
{
    zone *zones = malloc(6 * sizeof(zone));

    zones[0] = *z_surface();
    zones[1] = *z_crust();
    zones[2] = *z_upper_mantle();
    zones[3] = *z_lower_mantel();
    zones[4] = *z_core();
    zones[5] = *z_abyss();

    return (zones);
}