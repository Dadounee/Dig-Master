#include "../includes/includes.h"

void display_stamina(player_data *player, int sta)
{
    int     i;
    int     j;
    char    *filled_bar;
    char    *missing_bar;
    float   remaining_sta;

    filled_bar = malloc(10 * sizeof(char));
    missing_bar = malloc(10 * sizeof(char));
    remaining_sta = 10 * player->mining_sta/ 1.0 / sta;
    i = 0;
    while (i < remaining_sta)
    {
        filled_bar[i] = '#';
        i++;
    }
    filled_bar[i] = 0;
    j = 0;
    while (i + j < 10)
    {
        missing_bar[j] = '.';
        j++;
    }
    missing_bar[j] = 0;
    printf("%s---[%s%s%s%s%s]--- stamina:%d/%d%s\n", TC_WHT, TC_GRN, filled_bar, TC_RED, missing_bar, TC_WHT, player->mining_sta, sta, TC_NRM);
}
void mining(player_data *player, p_inventory *mining_inv)
{
    int x = -1;
    int y = -1;  
    display_map(player->actual_zone->mine_map);
    display_stamina(player, player_mining_sta(player));
    printf("Where do you want to start digging?\nplease enter 2 numbers\n");
    while (0 >= x || x > player->actual_zone->mine_map.map_height)
        user_input(&x, 'i', "(x)line num: ");
    while (0 >= y || y > player->actual_zone->mine_map.map_len)
        user_input(&y, 'i', "(y)line col: ");
    if (mine_pos(player, x, y) == 1)
        add_item(mining_inv, player->actual_zone->mine_map.map[x-1][y-1].ore);
}

void mining_end(player_data *player, p_inventory mining_inv)
{
    char *enter;

    fuse_inv(player->inv, &mining_inv);

    tc_clear_screen();
    printf("------------______<<session ended>>______------------\n\n");
    printf("You got:\n\n");
    display_inventory(mining_inv);

    enter = (char *)malloc(sizeof(char));
    printf("\npress anything + enter to continue. ");
    scanf(" %s", enter);
    free(enter);
}

void mining_session(player_data *player)
{
    int         action;
    p_inventory mining_inv;

    mining_inv.inv_size = player->inv->inv_size - player->inv->used_slots;
    mining_inv.used_slots = 0;
    mining_inv.inv = malloc(mining_inv.inv_size * sizeof(ore));

    if (player->inv->used_slots == player->inv->inv_size)
    {
        printf("You may want to sell your ores first.\n");
        return ;
    }
    player->mining_sta = player_mining_sta(player);
    player->mining_str = player->equipped_weapons->pickaxe.mining_str;

    map_gen(player->actual_zone);
    mining(player, &mining_inv);
    while (player->mining_sta > 0 && player->inv->used_slots < player->inv->inv_size)
    {
        user_input(&action, 'i', "\n----------\n1.mine\n2.temp inv\n3.return home\n----------\n");
        tc_clear_screen();
        if (action == 1)
            mining(player, &mining_inv);
        else if (action == 2)
            display_inventory(mining_inv);
        else
            player->mining_sta = 0;
    }
    mining_end(player, mining_inv);
}
