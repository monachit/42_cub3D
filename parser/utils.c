#include "../main.h"

void    ft_show_error(char *str)
{
    write(1, "Error\n", 6);
    write(1, str, ft_strlen(str));
    exit (1);
}


int calcul_words(char *str)
{
    int i = 0;
    int calcul = 0;
    while(str[i] && str[i] != '\n')
    {
        while (str[i] == 32)
            i++;
        if (str[i] && str[i] != 32 && str[i] != '\n')
        {
            calcul++;
            while (str[i] && str[i] != 32 && str[i] != '\n')
                i++;
        }
    }
    return (calcul);
}

void    insert_t_read(t_read **file, char *str)
{
    t_read *new = malloc(sizeof(t_read));
    new->line = str;
    new->nb_words = calcul_words(str);
    new->type = INIT;
    new->next = NULL;
    if (!(*file))
        *file = new;
    else
    {
        t_read *curr = *file;
        while (curr->next)
            curr = curr->next;
        curr->next = new;
    }

}