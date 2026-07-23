#include "../includes/includes.h"

void inventory_init(player_data *player)
{
    player->inv = malloc(sizeof(p_inventory));
    player->inv->inv_size = 5;
    player->inv->used_slots = 0;
    player->inv->inv = (ore *)malloc(player->inv->inv_size * sizeof(ore));
}

void first_weapons(player_data *player)
{
    int     i = 0;
    sword   sword;
    armor   ar = plain_armor();

    sword.name = "Fists";
    sword.cost = 0;
    sword.speed = 1.0;
    sword.str = 2;
    sword.effects = NULL;

    player->unlocked_zones = malloc(6 * sizeof(bool));
    player->unlocked_pickaxes = malloc(10 * sizeof(bool));
    player->unlocked_zones[0] = 1;
    player->unlocked_pickaxes[0] = 1;
    player->crates[0] = 0;

    while (++i < 6)
            player->unlocked_zones[i] = 0;
    i = 0;
    while (++i < 10)
            player->unlocked_pickaxes[i] = 0;
    
    player->equipped_weapons->sword = sword;
    player->equipped_weapons->pickaxe = p_fists();
    player->equipped_weapons->helmet = ar;
    player->equipped_weapons->chestplate = ar;
    player->equipped_weapons->leggings = ar;
    player->equipped_weapons->boots = ar;

}

void armor_inventory_init(player_data *player)
{
    player->weapons_inv = malloc(sizeof(weapons_inventory));
    player->weapons_inv->inv_size = 5;
    player->weapons_inv->used_slots = 0;
    player->weapons_inv->inv = (armor *)malloc(player->inv->inv_size * sizeof(armor));
}

void inventory_free(player_data *player)
{
    free(player->inv->inv);
    free(player->inv);
}

player_data player_init(void)
{
    player_data player;
    
    inventory_init(&player);
    armor_inventory_init(&player);
    
    player.equipped_weapons = malloc(sizeof(weapons));
    first_weapons(&player);
    
    player.actual_zone = malloc(sizeof(zone));
    player.actual_zone = z_surface();
    
    player.hp = 100;
    player.def = 5;
    player.str = 2;
    player.speed = 1;
    player.luck_mult = 1;
    player.money = 1000;
    player.money_multiplier = 8;
    
    return (player);
}

void player_free(player_data *player)
{
    inventory_free(player);
    free(player->equipped_weapons);
    zone_free(player->actual_zone);
    // free(player);
}

void add_armor(weapons_inventory *w_inv, armor armor)
{
    w_inv->inv[w_inv->used_slots] = armor;
    w_inv->used_slots++;
}

void add_armor_stats(player_data *player, armor ar)
{
    player->hp += ar.hp;
    player->str += ar.str;
    player->speed += ar.speed;
    player->mining_str += ar.mining_str;
}

void rem_armor_stats(player_data *player, armor ar)
{
    player->hp -= ar.hp;
    player->str -= ar.str;
    player->speed -= ar.speed;
    player->mining_str -= ar.mining_str;
}

void first_equip_w_inv(weapons_inventory *w_inv)
{
   w_inv->used_slots--;
}

void swap_armor(armor *old_armor, armor *new_armor)
{
    armor temp = *new_armor;

    *new_armor = *old_armor;
    *old_armor = temp;
}

void equip_armor(player_data *player, armor *ar)
{
    switch (ar->slot)
    {
    case 'h':
        swap_armor(&player->equipped_weapons->helmet, ar);
        add_armor_stats(player, player->equipped_weapons->helmet);
        break;
    case 'c':
        swap_armor(&player->equipped_weapons->chestplate, ar);
        add_armor_stats(player, player->equipped_weapons->chestplate);
        break;
    case 'l':
        swap_armor(&player->equipped_weapons->leggings, ar);
        add_armor_stats(player, player->equipped_weapons->leggings);
        break;
    case 'b':
        swap_armor(&player->equipped_weapons->boots, ar);
        add_armor_stats(player, player->equipped_weapons->boots);
        break;
    default:
        printf("%sThis armor isn't recognised! \n%s", TC_RED, TC_NRM);
        break;
    }

    if (ar->name[0] == 0)
    {
        armor temp = *ar;
        first_equip_w_inv(player->weapons_inv);

        *ar = player->weapons_inv->inv[player->weapons_inv->used_slots];
        player->weapons_inv->inv[player->weapons_inv->used_slots] = temp;
    }
    else
        rem_armor_stats(player, *ar);
}

void unequip_armor(player_data *player, int slot)
{

    switch (slot)
    {
    case 'h':
        rem_armor_stats(player, player->equipped_weapons->helmet);
        add_armor(player->weapons_inv, player->equipped_weapons->helmet);
        player->equipped_weapons->helmet = plain_armor();
        break;
    case 'c':
        rem_armor_stats(player, player->equipped_weapons->chestplate);
        add_armor(player->weapons_inv, player->equipped_weapons->chestplate);
        player->equipped_weapons->chestplate = plain_armor();
        break;
    case 'l':
        rem_armor_stats(player, player->equipped_weapons->leggings);
        add_armor(player->weapons_inv, player->equipped_weapons->leggings);
        player->equipped_weapons->leggings = plain_armor();
        break;
    case 'b':
        rem_armor_stats(player, player->equipped_weapons->boots);
        add_armor(player->weapons_inv, player->equipped_weapons->boots);
        player->equipped_weapons->boots = plain_armor();
        break;
    default:
        break;
    }
}

void display_equipped_armors(player_data *player)
{
    int i = -1;

    if (player->equipped_weapons->helmet.name[0] != 0)
    {
        printf("%d.%s: %s\n", i, player->equipped_weapons->helmet.name, get_rarity(player->equipped_weapons->helmet.rarity));
        i--;
    }
    if (player->equipped_weapons->chestplate.name[0] != 0)
    {
        printf("%d.%s: %s\n", i, player->equipped_weapons->chestplate.name, get_rarity(player->equipped_weapons->chestplate.rarity));
        i--;
    }
    if (player->equipped_weapons->leggings.name[0] != 0)
    {
        printf("%d.%s: %s\n", i, player->equipped_weapons->leggings.name, get_rarity(player->equipped_weapons->leggings.rarity));
        i--;
    }
    if (player->equipped_weapons->boots.name[0] != 0)
        printf("%d.%s: %s\n", i, player->equipped_weapons->boots.name, get_rarity(player->equipped_weapons->boots.rarity));

}

void drop_s_equipped(player_data *player, int slot)
{
    switch (slot)
    {
    case 'h':
        rem_armor_stats(player, player->equipped_weapons->helmet);
        player->equipped_weapons->helmet = plain_armor();
        break;
    case 'c':
        rem_armor_stats(player, player->equipped_weapons->chestplate);
        player->equipped_weapons->chestplate = plain_armor();
        break;
    case 'l':
        rem_armor_stats(player, player->equipped_weapons->leggings);
        player->equipped_weapons->leggings = plain_armor();
        break;
    case 'b':
        rem_armor_stats(player, player->equipped_weapons->boots);
        player->equipped_weapons->boots = plain_armor();
        break;
    default:
        break;
    }
}

int player_mining_sta(player_data *player)
{
    return (player->equipped_weapons->pickaxe.mining_sta+player->equipped_weapons->helmet.mining_sta+player->equipped_weapons->chestplate.mining_sta+player->equipped_weapons->leggings.mining_sta+player->equipped_weapons->boots.mining_sta);
}
