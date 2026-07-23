#ifndef DISPLAYS_H
# define DISPLAYS_H

# include "map_structs.h"
# include "player_structs.h"

void display_main_menu(long long int money, int inv_slots, int clear);
void display_map(map map);
void display_armor(armor ar);
void display_stats(player_data player);
void display_crates(player_data player);
void display_inventory(p_inventory inv);
void display_inv_upgrades(player_data *player);
void display_equipped_armors(player_data *player);
void display_zones(player_data *player, zone zone, int zone_no);
void display_sell_menu(player_data player, int total, int clear);
void display_pickaxes(player_data *player, pickaxe pick, int pickaxe_no);

#endif