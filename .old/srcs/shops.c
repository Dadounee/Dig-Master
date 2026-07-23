#include "../includes/includes.h"

void pickaxes_shop(player_data *player)
{
    int     actual_pick;
    int     p_choice;
    pickaxe *picks = get_pickaxes();

    actual_pick = 0;
    display_pickaxes(player, picks[actual_pick], actual_pick);
    p_choice = *(int *)user_input(&p_choice, 'i', "What do you want to do ? ");
    while (p_choice != 4)
    {
        tc_clear_screen();
        display_pickaxes(player, picks[actual_pick], actual_pick);
        while (p_choice > 4 || p_choice <= 0)
            p_choice = *(int *)user_input(&p_choice, 'i', "What do you want to do ? ");
        if (p_choice == 3)
        {
            if(player->unlocked_pickaxes[actual_pick] == 0 && player->unlocked_pickaxes[actual_pick - 1] == 1)
            {
                if(player->money >= picks[actual_pick].cost)
                {
                    player->equipped_weapons->pickaxe = picks[actual_pick];
                    player->money -= picks[actual_pick].cost;
                    player->unlocked_pickaxes[actual_pick] = 1;
                }
                else
                    printf("You're too poor to buy that.\n");
            }
            else if (player->unlocked_pickaxes[actual_pick] == 1)
                player->equipped_weapons->pickaxe = picks[actual_pick];
        }
        else if (p_choice == 1 && actual_pick > 0)
            actual_pick -= 1;
        else if (p_choice == 2 && actual_pick < 9)
            actual_pick += 1;
        if (p_choice != 4)
            p_choice = 0;
    }
    printf("You left the shop.\n");
}

void zones_shop(player_data *player)
{
    int     actual_zone;
    int     p_choice;
    zone *zones = get_zones();

    actual_zone = 0;
    display_zones(player, zones[actual_zone], actual_zone);
    p_choice = *(int *)user_input(&p_choice, 'i', "What do you want to do ? ");
    while (p_choice != 4)
    {
        tc_clear_screen();
        display_zones(player, zones[actual_zone], actual_zone);
        while (p_choice > 4 || p_choice <= 0)
            p_choice = *(int *)user_input(&p_choice, 'i', "What do you want to do ? ");
        if (p_choice == 3)
        {
            if(player->unlocked_zones[actual_zone] == 0 && player->unlocked_zones[actual_zone - 1] == 1)
            {
                if(player->money >= zones[actual_zone].price)
                {
                    player->actual_zone = &zones[actual_zone];
                    player->money -= zones[actual_zone].price;
                    player->unlocked_zones[actual_zone] = 1;
                }
                else
                    printf("You're too poor to buy that.\n");
            }
            else if (player->unlocked_zones[actual_zone] == 1)
                player->actual_zone = &zones[actual_zone];
        }
        else if (p_choice == 1 && actual_zone > 0)
            actual_zone -= 1;
        else if (p_choice == 2 && actual_zone < 5)
            actual_zone += 1;
        if (p_choice != 4)
            p_choice = 0;
    }
    printf("You left the shop.\n");
}

void inventory_shop(player_data *player)
{
    int     p_choice;

    display_inv_upgrades(player);
    p_choice = *(int *)user_input(&p_choice, 'i', "What do you want to do ? ");
    while (p_choice != 2)
    {
        tc_clear_screen();
        display_inv_upgrades(player);
        while (p_choice > 2 || p_choice <= 0)
            p_choice = *(int *)user_input(&p_choice, 'i', "What do you want to do ? ");
        if (p_choice == 1)
        {
            if (player->money >= (50 * power(2, player->inv->inv_upgrades + 1)))
            {
                player->inv->inv_upgrades++;
                player->inv->inv_size += player->inv->inv_upgrades;
                player->money -= 50 * power(2, player->inv->inv_upgrades + 1);
            }
            else
                printf("You're too poor to buy that.\n");
        }
        if (p_choice != 2)
            p_choice = -1;
    }
}

void in_shop(player_data *player)
{
    int which_shop = 0;

    while (which_shop != 4)
    {
        tc_clear_screen();
        which_shop = *(int*)user_input(&which_shop, 'i', "which shop do you want to go to?\n\n1.pickaxes\n2.zones\n3.inventory\n4+.quit\n\n");

        if (which_shop == 1)
            pickaxes_shop(player);
        else if (which_shop == 2)
            zones_shop(player);
        else if (which_shop == 3)
            inventory_shop(player);
        else
        {
            tc_clear_screen();
            return ;
        }
    }
}
