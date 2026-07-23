#include "../includes/includes.h"

void sell_ores(player_data *player, int total)
{
    char    action;
    
    action = *(char *)user_input(&action, 'c', "Do you want to sell theses precious ores? (y/n)\n");
    while (action != 'y' && action != 'n')
        action = *(char *)user_input(&action, 'c', "Do you want to sell theses precious ores? (y/n)\n");

    if (action == 'y')
    {
        player->money += total;
        player->inv->used_slots = 0;
    }
}

void sell_menu(player_data *player)
{
    int     i;
    int     total;

    total = 0;
    i = 0;
    while (i < player->inv->used_slots)
    {
        total += player->inv->inv[i].value;
        i++;
    }
    total = total * player->money_multiplier;

    display_sell_menu(*player, total, 1);

    sell_ores(player, total);
}
