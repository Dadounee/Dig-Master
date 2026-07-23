# include "../includes/includes.h"

int menu(player_data player)
{
    int     p_choice;
    char    **display_data;

    display_data = (char **)malloc(sizeof(char *) * 2);
    display_data[0] = malloc(sizeof(char) * 33);
    display_data[1] = malloc(sizeof(char) * 10);
    
    display_main_menu(player.money, player.inv->inv_size-player.inv->used_slots, 1);
    
    p_choice = *(int *)user_input(&p_choice, 'i', "What do you want to do ? ");
    while (p_choice > 7 || p_choice < 0)
    {
        printf("This is not an option...\n");
        p_choice = *(int *)user_input(&p_choice, 'i', "What do you want to do ? ");
    }
    printf("\x1B[0m");
    tc_clear_screen();
	return (p_choice);
}

int main(void)
{
    int         in_game;
    player_data player;

    player = player_init();
    tc_clear_screen();
    
    in_game = 50;
    while (in_game > 0)
    {
        in_game = menu(player);
        if (in_game == 1)
            mining_session(&player);
        if (in_game == 2)
            in_inventory(player);
        if (in_game == 3)
            sell_menu(&player);
        if (in_game == 4)
            in_shop(&player);
        if (in_game == 5)
            in_armor_inventory(&player);  
        if (in_game == 6)
            in_crate_menu(&player);
        if (in_game == 7)
            display_stats(player); 
    }
    player_free(&player);
    return (0);
}
    