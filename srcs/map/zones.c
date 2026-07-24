#include "map_structs.h"
#include "ores_funcs.h"

// Surface Zone

static ore **o_surface(void)
{
    ore         *available_ores[3];

    available_ores[0] = dirt();
    available_ores[1] = grass();
    available_ores[2] = stone();

    return (available_ores);
}

static int *p_surface(void)
{
    int         probability[4];

    probability[0] = 0;
    probability[1] = 500;
    probability[2] = 800;
    probability[3] = 1000;

    return (probability);
}

zone *z_surface(void)
{
    static const zone surface = {
        .name           = "Surface",
        .available_ores = o_surface,
        .ores_density    = p_surface,

        .mine_map       = {.map_len = 9, .map_height = 9},
        .void_density   = 2000,

        .price  = 0,
        .ore_nb = 3,

        .is_map = 0
    };

    return (&surface);
}

//  Crust Zone

static ore **o_crust(void)
{
    ore         *available_ores[4];

    available_ores[0] = stone();
    available_ores[1] = coal();
    available_ores[2] = copper();
    available_ores[3] = iron();

    return (available_ores);
}

static int *p_crust(void)
{
    int         probability[5];

    probability[0] = 0;
    probability[1] = 500;
    probability[2] = 750;
    probability[3] = 900;
    probability[4] = 1000;

    return (probability);
}

zone *z_crust(void)
{
    static const zone crust = {
        .name           = "Crust",
        .available_ores = o_crust,
        .ores_density    = p_crust,

        .mine_map       = {.map_len = 11, .map_height = 11},
        .void_density   = 2000,

        .price  = 1000,
        .ore_nb = 4,

        .is_map = 0
    };

    return (&crust);
}

// upper_mantel Zone

static ore **o_upper_mantel(void)
{
    ore         *available_ores[6];

    available_ores[0] = tough_stone();
    available_ores[1] = stone();
    available_ores[2] = copper();
    available_ores[3] = iron();
    available_ores[4] = silver();
    available_ores[5] = amethyst();

    return (available_ores);
}

static int *p_upper_mantel(void)
{
    int         probability[7];

    probability[0] = 0;
    probability[1] = 250;
    probability[2] = 500;
    probability[3] = 700;
    probability[4] = 850;
    probability[5] = 950;
    probability[6] = 1000;

    return (probability);
}

zone *z_upper_mantel(void)
{
    static const zone upper_mantel = {
        .name           = "Upper Mantel",
        .available_ores = o_upper_mantel,
        .ores_density    = p_upper_mantel,

        .mine_map       = {.map_len = 12, .map_height = 10},
        .void_density   = 2000,

        .price  = 10000,
        .ore_nb = 6,

        .is_map = 0
    };

    return (&upper_mantel);
}

// lower mantel zoneeee

static ore **o_lower_mantel(void)
{
    ore         *available_ores[4];

    available_ores[0] = deep_stone();
    available_ores[1] = gold();
    available_ores[2] = emerald();
    available_ores[3] = saphire();

    return (available_ores);
}

static int *p_lower_mantel(void)
{
    int         probability[5];

    probability[0] = 0;
    probability[1] = 600;
    probability[2] = 800;
    probability[3] = 925;
    probability[4] = 1000;

    return (probability);
}

zone *z_lower_mantel(void)
{
    static const zone lower_mantel = {
        .name           = "Lower Mantel",
        .available_ores = o_lower_mantel,
        .ores_density    = p_lower_mantel,

        .mine_map       = {.map_len = 10, .map_height = 10},
        .void_density   = 0,

        .price  = 50000,
        .ore_nb = 4,

        .is_map = 0
    };

    return (&lower_mantel);
}

// core Zoneeeeee

static ore **o_core(void)
{
    ore         *available_ores[4];

    available_ores[0] = deep_stone();
    available_ores[1] = saphire();
    available_ores[2] = ruby();
    available_ores[3] = diamond();

    return (available_ores);
}

static int *p_core(void)
{
    int         probability[5];

    probability[0] = 0;
    probability[1] = 500;
    probability[2] = 800;
    probability[3] = 960;
    probability[4] = 1000;

    return (probability);
}
zone *z_core(void)
{
    static const zone core = {
        .name           = "Lower Mantel",
        .available_ores = o_core,
        .ores_density    = p_core,

        .mine_map       = {.map_len = 9, .map_height = 9},
        .void_density   = 4000,

        .price  = 250000,
        .ore_nb = 4,

        .is_map = 0
    };

    return (&core);
}

// The abyss

static ore **o_core(void)
{
    ore         *available_ores[4];

    available_ores[0] = abyss_stone();
    available_ores[1] = ruby();
    available_ores[2] = diamond();
    available_ores[3] = uranium();

    return (available_ores);
}

static int *p_core(void)
{
    int         probability[5];

    probability[0] = 0;
    probability[1] = 550;
    probability[2] = 800;
    probability[3] = 925;
    probability[4] = 1000;

    return (probability);
}

zone *z_abyss(void)
{
    static const zone core = {
        .name           = "Lower Mantel",
        .available_ores = o_core,
        .ores_density    = p_core,

        .mine_map       = {.map_len = 15, .map_height = 12},
        .void_density   = 3200,

        .price  = 1000000,
        .ore_nb = 4,

        .is_map = 0
    };

    return (&core);
}

const zone **get_zones(void)
{
    static  zone zones[6];

    zones[0] = *z_surface();
    zones[1] = *z_crust();
    zones[2] = *z_upper_mantel();
    zones[3] = *z_lower_mantel();
    zones[4] = *z_core();
    zones[5] = *z_abyss();

    return (&zones);
}