#include "../main.h"

int skip_beg(char *str)
{
    int i = 0;
    while (str[i] == 32)
        i++;
    while (str[i] && str[i] != 32)
        i++;
    while (str[i] == 32)
        i++;
    return (i);
}

int len_str_color(char *s, int i)
{
    int count = 0;
    while (s[i] && s[i] != '\n' && s[i] != 32)
    {
        i++;
        count++;
    }
    return (count);
}

int check_virguls(char *s)
{
    int i = 0;
    int count = 0;
    if (s[i] == ',')
        return (-1);
    while (s[i])
    {
        if (i + 1 < ft_strlen(s) && s[i] == ',' && s[i + 1] == ',')
            return (-1);
        if (s[i] == ',')
            count++;
        if (s[i] != ',' && !ft_isdigit(s[i]))
            return (-1);
        i++;
    }
    if (s[i - 1] == ',')
        return (-1);
    return (count);
}

int len_nb(char *s, int *i)
{
    int i1 = *i;
    int len = 0;
    while (ft_isdigit(s[i1]))
    {
        len++;
        i1++;
    }
    *i = i1;
    return (len);
}

void    extract_numbers(t_data *data, char *s, char c)
{
    int i = 0;
    if (c == 'c')
    {
        data->c1 = ft_atoi_lhbal( ft_substr(s, i, len_nb(s, &i)));
        i++;
        data->c2 = ft_atoi_lhbal( ft_substr(s, i, len_nb(s, &i)));
        i++;
        data->c3 = ft_atoi_lhbal( ft_substr(s, i, len_nb(s, &i)));
    }
    else if (c == 'f')
    {
        data->f1 = ft_atoi_lhbal( ft_substr(s, i, len_nb(s, &i)));
        i++;
        data->f2 = ft_atoi_lhbal( ft_substr(s, i, len_nb(s, &i)));
        i++;
        data->f3 = ft_atoi_lhbal( ft_substr(s, i, len_nb(s, &i)));
    }
}

void    process_colors(t_data *data,char *str, char c)
{
    (void)data;
    int i = skip_beg(str);
    int j = len_str_color(str, i);
    char *s = ft_substr(str, i, j);
    if (check_virguls(s) != 2)
    {
        // FREE HNAYA Lfile
        ft_show_error("Colors invalid!\n");
    }
    extract_numbers(data, s, c);
}

void    extract_colors(t_read *file, t_data *data)
{

    while (file)
    {
        if (file->type == F)
            process_colors(data, file->line, 'f');
        else if (file->type == C)
            process_colors(data, file->line, 'c');
        file = file->next;
    }
    if (data->c1 < 0 || data->c1 > 255 
        || data->c2 < 0 || data->c2 > 255 
        || data->c3 < 0 || data->c3 > 255 
        || data->f1 < 0 || data->f1 > 255 
        || data->f2 < 0 || data->f2 > 255 
        || data->f3 < 0 || data->f3 > 255)
    {
        // FREE HNAYA L FILE YA ZWIWN DIAL MAMAH
        ft_show_error("RGB colors range invalid [0,255]\n");
    }
    
}