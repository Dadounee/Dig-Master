#include "../includes/includes.h"
#include <time.h>
#include <stdlib.h>

void armor_obtained(armor o_armor)
{
    printf("------------------------\n");
    display_armor(o_armor);
}

armor common_crate(void)
{
    int     i;
    int     random;
    int     probability[5] = {0, 250, 500, 750, 1000};
    armor   available_items[4] = {training_helmet(), training_top(), training_jean(), training_boots()};
    
    srand(rand());
    random = rand() % 1000 + 1;
    i = 0;
    while (random >= probability[i+1])
        i++;
    return (available_items[i]);
}

void open_crate(player_data *player, int crate_rarity)
{
    int     p_choice;
    armor   drop;

    switch (crate_rarity)
    {
    case common:
        drop = common_crate();
        player->crates[crate_rarity]--;
        break;
    
    default:
        printf("%sThis is not a box that you got\n%s", TC_RED, TC_NRM);
        return ;
    }
    
    armor_obtained(drop);
    p_choice = *(int *)user_input(&p_choice, 'i', "1.keep it\n2.drop it\n");
    while (p_choice > 2 || p_choice <= 0)
    {
        printf("This is not an option...\n");
        p_choice = *(int *)user_input(&p_choice, 'i', "1.keep it\n2.drop it\n");
    }

    if(p_choice == 1)
    {
        printf("You succesfully got %s\n", drop.name);
        add_armor(player->weapons_inv, drop);
    }
    else
        printf("You dropped %s\n", drop.name);
}

void in_crate_menu(player_data *player)
{
    int p_choice;
    
    if (player->weapons_inv->used_slots < player->weapons_inv->inv_size)
    {
        p_choice = -1;
        while (p_choice != 0)
        {
            display_crates(*player);
            p_choice = *(int *)user_input(&p_choice, 'i', "Please select a box to open(0 to quit)");
            while (p_choice > 1 || p_choice < 0)
            {
                printf("This is not an option...\n");
                p_choice = *(int *)user_input(&p_choice, 'i', "Please select a box to open(0 to quit)");
            }
            if (p_choice != 0 && player->crates[p_choice-1] > 0)
                open_crate(player, p_choice-1);
            else if (player->crates[p_choice-1] == 0)
                printf("you got none of theses\n");
        }
    }
    else
        printf("Inventory full, go clean it before opening more crates");
}
