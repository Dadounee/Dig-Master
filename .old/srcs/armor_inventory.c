#include "../includes/includes.h"

void display_armor_inventory(weapons_inventory inv)
{
    int     i;

    if (inv.used_slots == 0)
    {
        printf("Your inventory is empty\n");
        return ;
    }
    i = 0;
    while (i < inv.used_slots)
    {
        printf("%d.%s: %s\n", i+1, inv.inv[i].name, get_rarity(inv.inv[i].rarity));
        i++;
    }
}

void in_selection(player_data *player, int slot)
{
    int p_choice;

    printf("Currently selected: %d\n\n", slot+1);
    display_armor(player->weapons_inv->inv[slot]);
    p_choice = *(int *)user_input(&p_choice, 'i', "1.equip\n2.drop\n3.leave");
    while (p_choice >= 4 || p_choice <= 0)
    {
        printf("This is not an option...\n");
        p_choice = *(int *)user_input(&p_choice, 'i', "1.equip\n2.drop\n3.leave");
    }
    if (p_choice == 1)
        equip_armor(player, &player->weapons_inv->inv[slot]);
    if (p_choice == 2)
    {
        player->weapons_inv->used_slots--;
        player->weapons_inv->inv[slot] = player->weapons_inv->inv[player->weapons_inv->used_slots];   
    }
}

int check_armor(player_data *player, int slot)
{
    int i = 0;
    if (player->equipped_weapons->helmet.name[0] != 0)
    {
        i--;
        if (slot == i)
            return ('h');
    }
    if (player->equipped_weapons->chestplate.name[0] != 0)
    {
        i--;
        if (slot == i)
            return ('c');
    }
    if (player->equipped_weapons->leggings.name[0] != 0)
    {
        i--;
        if (slot == i)
            return ('l');
    }
    if (player->equipped_weapons->boots.name[0] != 0)
    {
        i--;
        if (slot == i)
            return ('b');
    }
    return (-1);
}

void display_s_equipped(player_data *player, int slot)
{
    switch (slot)
    {
    case 'h':
        display_armor(player->equipped_weapons->helmet);
        break;
    case 'c':
        display_armor(player->equipped_weapons->chestplate);
        break;
    case 'l':
        display_armor(player->equipped_weapons->leggings);
        break;
    case 'b':
        display_armor(player->equipped_weapons->boots);
        break;
    default:
        break;
    }
}

void selected_equipped(player_data *player, int slot)
{
    int s_armor;
    int p_choice;

    s_armor = check_armor(player, slot);
    if (s_armor != -1)
    {
        printf("Currently selected: %d\n\n", slot);
        display_s_equipped(player, s_armor);
        p_choice = *(int *)user_input(&p_choice, 'i', "1.unequip\n2.drop\n3.leave");
        while (p_choice >= 4 || p_choice <= 0)
        {
            printf("This is not an option...\n");
            p_choice = *(int *)user_input(&p_choice, 'i', "1.unequip\n2.drop\n3.leave");
        }
        if (p_choice == 1)
        {
            if (player->weapons_inv->used_slots < player->weapons_inv->inv_size)
                unequip_armor(player, s_armor);
            else
                printf("you got no space to fit that in your inventory");
        }
        if (p_choice == 2)
            drop_s_equipped(player, s_armor);
    }
}

void in_armor_inventory(player_data *player)
{
    int p_choice;
    
    p_choice = -1;
    while (p_choice != 0)
    {
        printf("used slots: %d/%d\n\n", player->weapons_inv->used_slots, player->weapons_inv->inv_size);
        display_armor_inventory(*player->weapons_inv);
        display_equipped_armors(player);

        p_choice = *(int *)user_input(&p_choice, 'i', "Please choose an armor. (0 to quit)");
        while ((p_choice > player->weapons_inv->used_slots || p_choice < -4) && p_choice != 0)
        {
            printf("This is not an option...\n");
            p_choice = *(int *)user_input(&p_choice, 'i', "Please choose a valid armor. (0 to quit)");
        }
        if (p_choice > 0)
            in_selection(player, p_choice-1);
        if (p_choice < 0)
            selected_equipped(player, p_choice);
    }
}
