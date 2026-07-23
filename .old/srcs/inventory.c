#include "../includes/includes.h"

int in_list(char **word_list, int list_size, char *word)
{
    int i;

    i = 0;
    while (i < list_size)
    {
        if (strcmp(word_list[i], word) == 0)
            return (1);
        i++;
    }
    return (0);
}

int ore_count(p_inventory inv, char *ore_name)
{
    int i = 0;
    int count = 0;
    
    while (i < inv.used_slots)
    {
        if (strcmp(inv.inv[i].name, ore_name) == 0)
            count++;
        i++;
    }
    return (count);
}

void display_inventory(p_inventory inv)
{
    int     i;
    int     item_count;
    char    **inv_items;

    inv_items = (char **) malloc(inv.used_slots * sizeof(char *));
    if (inv_items == NULL || inv.used_slots == 0)
    {
        printf("Your inventory is empty\n");
        return ;
    }
    i = 0;
    item_count = 0;
    while (i < inv.used_slots)
    {
        if (in_list(inv_items, item_count, inv.inv[i].name) == 0)
        {
            inv_items[item_count] = (char *)malloc(strlen(inv.inv[i].name) * sizeof(char));
            strcpy(inv_items[item_count], inv.inv[i].name);
            printf("%s: x%d\n", inv_items[item_count], ore_count(inv, inv.inv[i].name));
            item_count++;
        }
        i++;
    }
    while (item_count > 0)
    {
        item_count--;
        free(inv_items[item_count]);
    }
    free(inv_items);
}

void in_inventory(player_data player)
{
    char    *enter;
    
    printf("used slots: %d/%d\n\n", player.inv->used_slots, player.inv->inv_size);
    display_inventory(*player.inv);
    enter = (char *)malloc(sizeof(char));
    printf("\npress anything + enter to continue. ");
    scanf(" %s", enter);
    free(enter);
}

void add_item(p_inventory *inv, ore ore)
{
    inv->inv[inv->used_slots] = ore;
    inv->used_slots++;
}

void fuse_inv(p_inventory *inv_base, p_inventory *fuse_inv)
{
    int i;

    i = 0;
    while(i < fuse_inv->used_slots && inv_base->used_slots < inv_base->inv_size)
    {
        add_item(inv_base, fuse_inv->inv[i]);
        i++;
    }
}