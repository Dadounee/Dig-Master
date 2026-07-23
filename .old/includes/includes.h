#ifndef INCLUDES_H
# define INCLUDES_H

# include "player_structs.h"
# include "radius.h"
# include "map_structs.h"
# include "libs.h"
# include "tc.h"

# include "ores.h"
# include "pickaxes.h"
# include "zones.h"
# include "crates.h"

# include "displays.h"

int             min(int a, int b);
int             max(int a, int b);
int             player_mining_sta(player_data *player);
int             mine_pos(player_data *player, int x, int y);

char            *get_rarity(int rarity);

void            map_free(map *map);
void            zone_free(zone *zone);
void            map_gen(zone *actual_zone);
void            in_shop(player_data *player);
void            sell_menu(player_data *player);
void            player_free(player_data *player);
void            in_inventory(player_data player);
void            in_crate_menu(player_data *player);
void            mining_session(player_data *player);
void            add_item(p_inventory *inv, ore ore);
void            in_armor_inventory(player_data *player);
void            unequip_armor(player_data *player, int slot);
void            drop_s_equipped(player_data *player, int slot);
void            equip_armor(player_data *player, armor *armor);
void            add_armor(weapons_inventory *w_inv, armor armor);
void            fuse_inv(p_inventory *inv_base, p_inventory *fuse_inv);

void            *user_input(void *input_var, char c, char *str);
void            *invalid_user_input(void *input_var, char c, char *str);

armor           plain_armor(void);

player_data     player_init(void);

long long int   power(int nb, int power);

#endif