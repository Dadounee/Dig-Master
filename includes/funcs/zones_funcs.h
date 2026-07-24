#ifndef ZONES_FUNCS_H
# define ZONES_FUNCS_H

# include "map_structs.h"

zone *z_surface(void);
zone *z_crust(void);
zone *z_upper_mantel(void);
zone *z_lower_mantel(void);
zone *z_core(void);
zone *z_abyss(void);

zone **get_zones(void);

#endif