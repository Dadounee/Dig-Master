#include "includes.h"
#include "libs.h"

/*
    INVENTORY INIT RELATED STUFF
*/

void armor_inventory_init(player_data *player)
{
    player->weapons_inv = malloc(sizeof(weapons_inventory));
    player->weapons_inv->inv_size = 5;
    player->weapons_inv->count = 0;
    player->weapons_inv->inv = malloc(player->inv->inv_size * sizeof(armor *));
}

void inventories_free(player_data *player)
{
    free(player->weapons_inv->inv);
    free(player->weapons_inv);
}

/*
    WEAPON INIT RELATED STUFF
*/

void first_weapons(player_data *player)
{
    int     i = 0;

    player->unlocked_zones[0] = 1;
    player->unlocked_pickaxes[0] = 1;
    player->crates[0] = 0;

    while (++i < 6)
            player->unlocked_zones[i] = 0;
    i = 0;
    while (++i < 10)
            player->unlocked_pickaxes[i] = 0;
    
    player->equipped_weapons.sword = NULL;
    player->equipped_weapons.pickaxe = NULL;
    equip_pickaxe(player, p_fists());

    player->equipped_weapons.helmet = plain_armor();
    player->equipped_weapons.chestplate = plain_armor();
    player->equipped_weapons.leggings = plain_armor();
    player->equipped_weapons.boots = plain_armor();

}

/*
    PLAYER INIT RELATED STUFF
*/

player_data *player_init(void)
{
    static player_data player;
    
    inventory_init(&player);
    armor_inventory_init(&player);
    
    player.actual_zone = z_surface();
    
    player.hp = BASE_HP;
    player.def = BASE_DEF;
    player.str = BASE_STR;
    player.speed = BASE_SPEED;
    player.luck_mult = BASE_LUCK;
    player.money = BASE_MONEY;
    player.money_multiplier = BASE_MULT;

    player.mining_sta = 0;
    player.mining_str = 0;
    player.actual_sta = 0;
    player.oldState = MINING;
    player.gameState = MINING;

    first_weapons(&player);
    
    player.display_actualisation = true;
    return (&player);
}

void player_free(player_data *player)
{
    OreInventoryFree(player->inv);
    inventories_free(player);
    if (player->actual_zone->is_map)
        map_free(&player->actual_zone->mine_map);
}

/*
    WEAPONS INV MANIP RELATED STUFF
*/

void add_armor(weapons_inventory *w_inv, armor *armor)
{
    w_inv->inv[w_inv->count] = armor;
    w_inv->count++;
}

void add_armor_stats(player_data *player, armor *ar)
{
    player->hp += ar->hp;
    player->str += ar->str;
    player->speed += ar->speed;
    player->mining_str += ar->mining_str;
}

void rem_armor_stats(player_data *player, armor *ar)
{
    player->hp -= ar->hp;
    player->str -= ar->str;
    player->speed -= ar->speed;
    player->mining_str -= ar->mining_str;
}

void first_equip_w_inv(weapons_inventory *w_inv)
{
   w_inv->count--;
}


void    equip_pickaxe(player_data *player, pickaxe *pick)
{
    if (player->equipped_weapons.pickaxe != NULL)
    {
        player->mining_sta -= player->equipped_weapons.pickaxe->mining_sta;
        player->mining_str -= player->equipped_weapons.pickaxe->mining_str;
    }
    
    player->equipped_weapons.pickaxe = pick;
    player->mining_sta += player->equipped_weapons.pickaxe->mining_sta;
    player->mining_str += player->equipped_weapons.pickaxe->mining_str;
}

void    changeState(player_data *player)
{
    if (player->gameState == MINING)
    {

    }
    else if (player->gameState == INVENTORY)
    {
        changeButtonStateName("inventoryButton", DISABLED);
    }
}

// void swap_armor(player_data *player, armor *new_armor)
// {
//     armor temp = *new_armor;

//     *new_armor = *old_armor;
//     *old_armor = temp;
// }

// void equip_armor(player_data *player, armor *ar)
// {
//     switch (ar->slot)
//     {
//     case 'h':
//         swap_armor(&player->equipped_weapons->helmet, ar);
//         add_armor_stats(player, player->equipped_weapons->helmet);
//         break;
//     case 'c':
//         swap_armor(&player->equipped_weapons->chestplate, ar);
//         add_armor_stats(player, player->equipped_weapons->chestplate);
//         break;
//     case 'l':
//         swap_armor(&player->equipped_weapons->leggings, ar);
//         add_armor_stats(player, player->equipped_weapons->leggings);
//         break;
//     case 'b':
//         swap_armor(&player->equipped_weapons->boots, ar);
//         add_armor_stats(player, player->equipped_weapons->boots);
//         break;
//     default:
//         printf("%sThis armor isn't recognised! \n%s", TC_RED, TC_NRM);
//         break;
//     }

//     if (ar->name[0] == 0)
//     {
//         armor temp = *ar;
//         first_equip_w_inv(player->weapons_inv);

//         *ar = player->weapons_inv->inv[player->weapons_inv->used_slots];
//         player->weapons_inv->inv[player->weapons_inv->used_slots] = temp;
//     }
//     else
//         rem_armor_stats(player, *ar);
// }

// void unequip_armor(player_data *player, int slot)
// {

//     switch (slot)
//     {
//     case 'h':
//         rem_armor_stats(player, player->equipped_weapons->helmet);
//         add_armor(player->weapons_inv, player->equipped_weapons->helmet);
//         player->equipped_weapons->helmet = plain_armor();
//         break;
//     case 'c':
//         rem_armor_stats(player, player->equipped_weapons->chestplate);
//         add_armor(player->weapons_inv, player->equipped_weapons->chestplate);
//         player->equipped_weapons->chestplate = plain_armor();
//         break;
//     case 'l':
//         rem_armor_stats(player, player->equipped_weapons->leggings);
//         add_armor(player->weapons_inv, player->equipped_weapons->leggings);
//         player->equipped_weapons->leggings = plain_armor();
//         break;
//     case 'b':
//         rem_armor_stats(player, player->equipped_weapons->boots);
//         add_armor(player->weapons_inv, player->equipped_weapons->boots);
//         player->equipped_weapons->boots = plain_armor();
//         break;
//     default:
//         break;
//     }
// }

// void display_equipped_armors(player_data *player)
// {
//     int i = -1;

//     if (player->equipped_weapons->helmet.name[0] != 0)
//     {
//         printf("%d.%s: %s\n", i, player->equipped_weapons->helmet.name, get_rarity(player->equipped_weapons->helmet.rarity));
//         i--;
//     }
//     if (player->equipped_weapons->chestplate.name[0] != 0)
//     {
//         printf("%d.%s: %s\n", i, player->equipped_weapons->chestplate.name, get_rarity(player->equipped_weapons->chestplate.rarity));
//         i--;
//     }
//     if (player->equipped_weapons->leggings.name[0] != 0)
//     {
//         printf("%d.%s: %s\n", i, player->equipped_weapons->leggings.name, get_rarity(player->equipped_weapons->leggings.rarity));
//         i--;
//     }
//     if (player->equipped_weapons->boots.name[0] != 0)
//         printf("%d.%s: %s\n", i, player->equipped_weapons->boots.name, get_rarity(player->equipped_weapons->boots.rarity));

// }

// void drop_s_equipped(player_data *player, int slot)
// {
//     switch (slot)
//     {
//     case 'h':
//         rem_armor_stats(player, player->equipped_weapons->helmet);
//         player->equipped_weapons->helmet = plain_armor();
//         break;
//     case 'c':
//         rem_armor_stats(player, player->equipped_weapons->chestplate);
//         player->equipped_weapons->chestplate = plain_armor();
//         break;
//     case 'l':
//         rem_armor_stats(player, player->equipped_weapons->leggings);
//         player->equipped_weapons->leggings = plain_armor();
//         break;
//     case 'b':
//         rem_armor_stats(player, player->equipped_weapons->boots);
//         player->equipped_weapons->boots = plain_armor();
//         break;
//     default:
//         break;
//     }
// }
//     switch (slot)
//     {
//     case 'h':
//         rem_armor_stats(player, player->equipped_weapons->helmet);
//         player->equipped_weapons->helmet = plain_armor();
//         break;
//     case 'c':
//         rem_armor_stats(player, player->equipped_weapons->chestplate);
//         player->equipped_weapons->chestplate = plain_armor();
//         break;
//     case 'l':
//         rem_armor_stats(player, player->equipped_weapons->leggings);
//         player->equipped_weapons->leggings = plain_armor();
//         break;
//     case 'b':
//         rem_armor_stats(player, player->equipped_weapons->boots);
//         player->equipped_weapons->boots = plain_armor();
//         break;
//     default:
//         break;
//     }
// }