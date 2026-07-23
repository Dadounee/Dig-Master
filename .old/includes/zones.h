#ifndef ZONES_H
# define ZONES_H

#include "map_structs.h"

void zone_free(zone *zone);
zone *z_core(void);
zone *z_abyss(void);
zone *z_crust(void);
zone *z_surface(void);
zone *z_lower_mantel(void);
zone *z_upper_mantle(void);

zone *get_zones(void);

#endif