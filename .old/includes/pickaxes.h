#ifndef PICKAXES_H
# define PICKAXES_H

# include "weapons_structs.h"

pickaxe p_fists(void);
pickaxe p_stick(void);
pickaxe p_wooden_pickaxe(void);
pickaxe p_wooden_hammer(void);
pickaxe p_stone_pickaxe(void);
pickaxe p_iron_pickaxe(void);
pickaxe p_golden_pickaxe(void);
pickaxe p_diamond_pickaxe(void);
pickaxe p_electric_pickaxe(void);
pickaxe p_abyss_pickaxe(void);

pickaxe *get_pickaxes(void);

#endif