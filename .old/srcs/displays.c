#include "../includes/includes.h"

void display_main_menu(long long int money, int inv_slots, int clear)
{
    if (clear)
        tc_clear_screen();

    printf("%s~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",TC_B_WHT);
    printf("           -\\_main menu_/-\n");
    printf("%smoney: %lld\n", TC_B_YEL, money);
    printf("%sremaining slots: %d\n", TC_B_WHT, inv_slots);
    printf("1.excavate\n");
    printf("2.ores inventory\n");
    printf("%s$3.sell ores$%s\n", TC_B_GRN, TC_B_WHT);
    printf("4.shop\n");
    printf("5.armor inventory\n");
    printf("6.crates\n");
    printf("7.your stats\n");
	printf("\n\n0.quit\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n%s",TC_B_NRM);
}
void display_sell_menu(player_data player,int total, int clear)
{
    if (clear)
        tc_clear_screen();

    printf("%s------------------------------------------\n", TC_B_WHT);
    printf("                 \\shop/\n\n");
    printf("You've mined:\n");

    display_inventory(*player.inv);

    printf("\n%sMult: %d\n", TC_B_WHT, player.money_multiplier);
    printf("Total: %s%d\n\n", TC_B_GRN, total);
    printf("%s------------------------------------------\n%s", TC_B_WHT, TC_B_NRM);
}

void put_number_map(int i)
{
    if (i < 10)
        printf(" %d ", i);
    else if (i < 100)
        printf("%d ", i);
    else
        printf("%d", i);
}

void display_map(map map)
{
    int     l;
    int     h;

    printf("%s   ", TC_WHT);

    h = 0;
    l = -1;
    while (++l < map.map_len)
        put_number_map(l+1);
    printf("\n");
    while (h < map.map_height)
    {
        l = 0;
        put_number_map(h+1);
        while (l < map.map_len)
        {
            if (!map.map[h][l].discovered)
                printf(" # ");
            else
            {
                if (map.map[h][l].s_type == empty)
                    printf("   ");
                else if (map.map[h][l].s_type == mineral && map.map[h][l].durability > 0)
                    printf(" %sx%s ", map.map[h][l].ore.color, TC_WHT);
                else if (map.map[h][l].s_type == crate && map.map[h][l].rarity >= 0)
                    printf(" %sC%s ", TC_RED, TC_WHT);
                else
                    printf(" o ");
            }
            l++;
        }
        if (h++ < map.map_height)
            printf("\n");
    }
    printf("%s", TC_NRM);
}

void display_pickaxes(player_data *player, pickaxe pick, int pickaxe_no)
{
    if (player->unlocked_pickaxes[pickaxe_no] || player->unlocked_pickaxes[pickaxe_no-1])
    {
        printf("------_______\\\\Pickaxes shop//_______------\n");
        printf("4.Quit                      Money: %lld\n\n", player->money);
        printf("Pickaxe: %s\n", pick.name);
        printf("Cost: %d\n", pick.cost);
        if (player->unlocked_pickaxes[pickaxe_no])
            printf("                        3.equip\n");
        else
            printf("                        3.buy\n");
        printf("Strength: %d\n", pick.mining_str);
        printf("Stamina: %d\n\n", pick.mining_sta);
    }
    else
    {
        printf("------_______\\\\Pickaxes shop//_______------\n");
        printf("4.Quit                      Money: %lld\n\n", player->money);
        printf("Pickaxe: ???\n");
        printf("Cost: ???\n");
        printf("                        X.xxx\n");
        printf("Strength: ???\n");
        printf("Stamina: ???\n\n");
    }
    printf("            ");
    if (pickaxe_no > 0)
        printf("< 1 ");
    printf("|");
    if (pickaxe_no < 9)
        printf(" 2 >");
    printf("\n");
}

void display_zones(player_data *player, zone zone, int zone_no)
{
    int i = -1;
    
    if (player->unlocked_zones[zone_no] || player->unlocked_zones[zone_no-1])
    {
        printf("------_______\\\\Zones shop//_______------\n");
        printf("4.Quit                      Money: %lld\n\n", player->money);
        printf("Zone: %s\n", zone.name);
        printf("Cost: %d\n", zone.price);
        if (player->unlocked_zones[zone_no])
            printf("                        3.equip\n");
        else
            printf("                        3.buy\n");
        printf("Available ores:\n\n");
        while(++i < zone.ore_nb)
            printf("%d.%s\n", i + 1, zone.available_ores[i].name);
            
    }
    else
    {
        printf("------_______\\\\Zones shop//_______------\n");
        printf("4.Quit                      Money: %lld\n\n", player->money);
        printf("Zone: ???\n");
        printf("Cost: ???\n");
        printf("                        X.xxx\n");
        printf("Available ores:\n\n");
        while(++i < zone.ore_nb)
            printf("???\n");
    }
    printf("\n            ");
    if (zone_no > 0)
        printf("< 1 ");
    printf("|");
    if (zone_no < 6)
        printf(" 2 >");
    printf("\n");
}

void display_inv_upgrades(player_data *player)
{
    printf("----_____\\\\Inventory upgrades//_____----\n");
    printf("2.Quit                      Money: %lld\n\n", player->money);
    printf("Your current inventory:\n");
    printf("Level: %d\n", player->inv->inv_upgrades);
    printf("Slots: %d\n\n", player->inv->inv_size);
    printf("Next:\n");
    printf("Level: %d\n", player->inv->inv_upgrades + 1);
    printf("Slots: %d\n\n", player->inv->inv_size + player->inv->inv_upgrades + 1);
    printf("Cost: %lld", 50 * power(2, player->inv->inv_upgrades + 1));
    if (player->money > 50 * power(2, player->inv->inv_upgrades + 1))
        printf("        1.Buy\n");
    else
        printf("        X.XXX\n");
}

void display_stats(player_data player)
{
    char    *enter;
    
    printf("Here are your stats:\n");
    printf("hp: %d\n", player.hp);
    printf("str: %d\n", player.str);
    printf("speed: %d\n", player.speed);
    printf("mining str: %d\n", player.mining_str);
    printf("mining sta: %d\n\n", player_mining_sta(&player));
    enter = (char *)malloc(sizeof(char));
    printf("\npress anything + enter to continue. ");
    scanf(" %s", enter);
    free(enter);
}

void display_crates(player_data player)
{
    int i;

    i = 0;
    while (i < 1)
    {
        printf("%d.%s crates: %d\n", i+1, get_rarity(i), player.crates[i]);
        i++;
    }
}

void display_armor(armor ar)
{
    printf("name: %s\n\n", ar.name);
    printf("hp: %d\n", ar.hp);
    printf("str: %d\n", ar.str);
    printf("speed: %d\n", ar.speed);
    printf("mining str: %d\n", ar.mining_str);
    printf("mining sta: %d\n\n", ar.mining_sta);
    printf("slot: %c\n", ar.slot);
    printf("rarity: %s\n\n", get_rarity(ar.rarity));
}
