#include "includes.h"
#include "libs.h"

/*
    INVENTORY INIT RELATED STUFF
*/

void armor_inventory_init(playerData *player)
{
    player->weapons_inv = malloc(sizeof(weapons_inventory));
    player->weapons_inv->inv_size = 5;
    player->weapons_inv->count = 0;
    player->weapons_inv->inv = malloc(player->inv->inv_size * sizeof(armor *));
}

void inventories_free(playerData *player)
{
    free(player->weapons_inv->inv);
    free(player->weapons_inv);
}

/*
    WEAPON INIT RELATED STUFF
*/

void first_weapons(playerData *player)
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

playerData *player_init(void)
{
    static playerData player;
    
    player.miningStr = 0;

    inventory_init(&player);
    initPlayerStats(&player);
    first_weapons(&player);
    applyPlayerStats(&player);
    armor_inventory_init(&player);
    
    player.actual_zone = z_surface();

    player.oldState = MINING;
    player.gameState = MINING;

    
    player.display_actualisation = true;
    return (&player);
}

void player_free(playerData *player)
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

void add_armor_stats(playerData *player, armor *ar)
{
    player->hp += ar->hp;
    player->str += ar->str;
    player->speed += ar->speed;
    player->miningStr += ar->miningStr;
}

void rem_armor_stats(playerData *player, armor *ar)
{
    player->hp -= ar->hp;
    player->str -= ar->str;
    player->speed -= ar->speed;
    player->miningStr -= ar->miningStr;
}

void first_equip_w_inv(weapons_inventory *w_inv)
{
   w_inv->count--;
}


void    equip_pickaxe(playerData *player, pickaxe *pick)
{
    if (player->equipped_weapons.pickaxe != NULL)
        player->playerStats.baseStrBoost -= player->equipped_weapons.pickaxe->miningStr;
    
    player->equipped_weapons.pickaxe = pick;
    player->playerStats.baseStrBoost += player->equipped_weapons.pickaxe->miningStr;
}

/*

    init stat part

*/

void    initPlayerStats(playerData *player)
{
    player->playerStats.exp = 0;
    player->playerStats.level = 0;
    
    player->playerStats.dayCount = 0;

    player->playerStats.moneyMult = BASE_MULT;

    player->playerStats.baseHpBoost = BASE_HP;
    player->playerStats.multHpBoost = 1;

    player->playerStats.baseStaBoost = BASE_STAMINA;
    player->playerStats.multStaBoost = 1;

    player->playerStats.baseDefBoost = BASE_DEF;
    player->playerStats.multDefBoost = 1;

    player->playerStats.baseStrBoost = 0;
    player->playerStats.multStrBoost = 1;

    player->playerStats.baseLuckBoost = BASE_LUCK;
    player->playerStats.multLuckBoost = 1;

    player->playerStats.baseSpeedBoost = BASE_SPEED;
    player->playerStats.multSpeedBoost = 1;
    
}

void    applyPlayerStats(playerData *player)
{
    player->hp = player->playerStats.baseHpBoost * player->playerStats.multHpBoost;
    player->def = player->playerStats.baseDefBoost * player->playerStats.multDefBoost;
    player->luck = player->playerStats.baseLuckBoost * player->playerStats.multLuckBoost;
    player->speed = player->playerStats.baseSpeedBoost * player->playerStats.multSpeedBoost;
    player->miningStr = player->playerStats.baseStrBoost * player->playerStats.multStrBoost;
    player->actualSta = player->playerStats.baseStaBoost * player->playerStats.multStaBoost;
    printf("hp:%d\ndef:%d\nstr:%d\n", player->hp, player->def, player->miningStr);
}

/*
    stat: 0.hp 1.sta 2.def 3.str 4.luck 5.speed
*/
void    applyOnePlayerStats(playerData *player, unsigned char stat)
{
    switch (stat)
    {
        case 0:
            player->hp = player->playerStats.baseHpBoost * player->playerStats.multHpBoost;
            break;
        case 1:
            player->actualSta = player->playerStats.baseStaBoost * player->playerStats.multStaBoost;
            break;
        case 2:
            player->def = player->playerStats.baseDefBoost * player->playerStats.multDefBoost;
            break;
        case 3:
            player->miningStr = player->playerStats.baseStrBoost * player->playerStats.multStrBoost;
            break;
        case 4:
            player->luck = player->playerStats.baseLuckBoost * player->playerStats.multLuckBoost;
            break;
        case 5:
            player->speed = player->playerStats.baseSpeedBoost * player->playerStats.multSpeedBoost;
            break;
        
        default:
            break;
    }

}
// void swap_armor(playerData *player, armor *new_armor)
// {
//     armor temp = *new_armor;

//     *new_armor = *old_armor;
//     *old_armor = temp;
// }

// void equip_armor(playerData *player, armor *ar)
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

// void unequip_armor(playerData *player, int slot)
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

// void display_equipped_armors(playerData *player)
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

// void drop_s_equipped(playerData *player, int slot)
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