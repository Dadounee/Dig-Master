#ifndef WEAPONS_FUNCS_H
# define WEAPONS_FUNCS_H

# include "map_structs.h"
# include "weapons_structs.h"


// pickaxe utils

    pickaxe *p_fists(void);
    pickaxe *p_stick(void);
    pickaxe *p_wooden_pickaxe(void);
    pickaxe *p_wooden_hammer(void);
    pickaxe *p_stone_pickaxe(void);
    pickaxe *p_iron_pickaxe(void);
    pickaxe *p_golden_pickaxe(void);
    pickaxe *p_diamond_pickaxe(void);
    pickaxe *p_electric_pickaxe(void);
    pickaxe *p_abyss_pickaxe(void);

    void    pick_radius(map *map, int x, int y, int remaining_depth);

// armor utils

    armor   *plain_armor(void);

    // helmet utils
    
        armor   *h_broken(void);
        armor   *h_training(void);

    // chestplate utils
    
        armor   *c_broken(void);
        armor   *c_training(void);

    // leggings utils
    
        armor   *l_broken(void);
        armor   *l_training(void);

    // boots utils
    
        armor   *b_broken(void);
        armor   *b_training(void);

#endif