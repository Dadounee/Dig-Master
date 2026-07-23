# include "../includes/includes.h"

/*
This function will treat the user input if user_input has failed

It'll take 3 arguments:
    void *input_var: the variable which will contains the user input
    char c: the expected type of the user input
    char *str: what's asked to the user

it'll return a pointer to the value entered by the user

if it fails it'll call itself
*/
void *invalid_user_input(void *input_var, char c, char *str)
{
    char *trash_line = malloc(sizeof(char) * 30);

    if (trash_line == NULL)
        return (NULL);
    printf("%sPlease enter a correct value\n", TC_NRM);
    scanf("%s", trash_line);
    free(trash_line);
    
    printf("%s%s", str, TC_CYN);
    if (c == 'i')
    {
        if (scanf(" %d", (int *)input_var) == 0)
            return (invalid_user_input(input_var, c, str));
    }
    else if (c == 'c')
    {
        if (scanf(" %c", (char *)input_var) == 0)
            return (invalid_user_input(input_var, c, str));
    }
    else if (c == 's')
    {
        if (scanf(" %s", (char *)input_var) == 0)
            return (invalid_user_input(input_var, c, str));
    }
    else 
    {
        printf("Wrong return type entered, expected i/c/s got %c", c);
        return (NULL);
    }
    printf("%s", TC_NRM);
    return (input_var);
}

/*
This function will treat the user input

It'll take 3 arguments:
    void *input_var: the variable which will contains the user input
    char c: the expected type of the user input (c = char, i = int, s = char *)
    char *str: what's asked to the user

it'll return a pointer to the value entered by the user

if it fails it'll call invalid_user_input
*/
void *user_input(void *input_var, char c, char *str)
{
    printf("%s%s", str, TC_CYN);
    if (c == 'i')
    {
        if (scanf(" %d", (int *)input_var) == 0)
            return (invalid_user_input(input_var, c, str));
    }
    if (c == 'c')
    {
        if (scanf(" %c", (char *)input_var) == 0)
            return (invalid_user_input(input_var, c, str));
    }
    if (c == 's')
    {
        if (scanf(" %s", (char *)input_var) == 0)
            return (invalid_user_input(input_var, c, str));
    }
    printf("%s", TC_NRM);
    return (input_var);
}

int max(int a, int b)
{
    return ((a > b) * a + (b > a) * b + (b == a) * a);
}

int min(int a, int b)
{
    return ((a > b) * b + (b > a) * a + (b == a) * a);
}

long long int power(int nb, int pw)
{
    if (pw == 0)
        return (1);
    if (pw > 0)
        return (nb * power(nb, pw - 1));
    return (-1);
}

char *get_rarity(int rarity)
{
    switch (rarity)
    {
    case common:
        return "common";
    case uncommon:
        return "uncommon";
    case rare:
        return "rare";
    case epic:
        return "epic";
    case legendary:
        return "legendary";
    case unobtainable:
        return "unobtainable"; 
    default:
        return "";
    }
}
