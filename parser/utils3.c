#include "../main.h"

int check_nb_virgul(char *s)
{
    int i = 0;
    int calcul = 0;
    while (s[i])
    {
        if (!ft_isdigit(s[i]) && s[i] != ',')
            ft_show_error("RGB colors invalid!\n");
        if (s[i] == ',')
            calcul++;
        i++;
    }
    return (calcul);
}

void    ft_rgb_colors(char *s, int *nbr1, int *nbr2, int *nbr3)
{
    int i = 0;
    if (s[i] == ',')
        ft_show_error("RGB colors invalid!\n");
    while (ft_isdigit(s[i]))
        i++;
    int nb1 = ft_atoi_lhbal(ft_substr(s, 0, i));
    i++;
    if (s[i] == ',')
        ft_show_error("RGB colors invalid!\n");
    int j = i;
    while (ft_isdigit(s[i]))
        i++;
    int nb2 = ft_atoi_lhbal(ft_substr(s, j, i));
    i++;
    if (!s[i])
        ft_show_error("RGB colors invalid!\n");
    j = i;
    int nb3 = ft_atoi_lhbal(ft_substr(s, j, i));
    if (nb1 > 250 || nb2 > 250 || nb3 > 250 || nb1 < 0 || nb2 < 0 || nb3 < 0) 
        ft_show_error("RGB colors must in the range [0,250]\n"); 
    *nbr1 = nb1;
    *nbr2 = nb2;
    *nbr3 = nb3;
}

int map_token(char *s)
{
    int i = 0;
    while (s[i] && s[i] != '\n')
    {
        if (s[i] != '1' && s[i] != '0' && s[i] != 'N' && s[i] != 'S' && s[i] != 'E' && s[i] != 'W'
            && s[i] != 32)
            return (0);
        i++;
    }
    return (1);
}

void    extract_paths(t_read *curr, char **path, int *i2, t_type type)
{
    int i = *i2;
    i = skip_spaces(curr->line, extract_len_first_word(curr->line, i));
    *path = ft_substr(curr->line, i, extract_len_first_word(curr->line, i));
    curr->type = type;
    *i2 = i;
}

void    extract_colors(t_read *curr, int *n1, int *n2, int *n3, int type, int *i2)
{
    int i = *i2;
    i = skip_spaces(curr->line, extract_len_first_word(curr->line, i));
    if (check_nb_virgul(ft_substr(curr->line, i, extract_len_first_word(curr->line, i))) != 2)
        ft_show_error("Floor color input invalid!\n");
    ft_rgb_colors(ft_substr(curr->line, i, extract_len_first_word(curr->line, i)), n1, n2, n3);
    curr->type = type;
    *i2 = i;
}

void    collect_data(t_read **file, t_data *data)
{
    t_read  *curr = *file;
    while (curr)
    {
        int i = skip_spaces(curr->line, 0);
        if (!ft_strcmp("NO", ft_substr(curr->line, i, extract_len_first_word(curr->line, i))))
            extract_paths(curr, &data->north_path, &i, NO);
        else if (!ft_strcmp("SO", ft_substr(curr->line, i, extract_len_first_word(curr->line, i))))
            extract_paths(curr, &data->south_path, &i, SO);
        else if (!ft_strcmp("WE", ft_substr(curr->line, i, extract_len_first_word(curr->line, i))))
            extract_paths(curr, &data->west_path, &i, WE);
        else if (!ft_strcmp("EA", ft_substr(curr->line, i, extract_len_first_word(curr->line, i))))
            extract_paths(curr, &data->east_path, &i, EA);
        else if (!ft_strcmp("F", ft_substr(curr->line, i, extract_len_first_word(curr->line, i))))
            extract_colors(curr, &data->f1, &data->f2, &data->f3, F, &i);
        else if (!ft_strcmp("C", ft_substr(curr->line, i, extract_len_first_word(curr->line, i))))
            extract_colors(curr, &data->c1, &data->c2, &data->c3, C, &i);
        else if (curr->nb_words > 0 && map_token(curr->line))
            curr->type = MAP;
        else if (ft_strcmp(curr->line, "\n"))
            ft_show_error("invalid line!\n");
        curr = curr->next;
    }
}