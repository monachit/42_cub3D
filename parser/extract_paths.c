#include "../main.h"

int skip_beg_path(char *str)
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

int len_str_path(char *s, int i)
{
    int count = 0;
    while (s[i] && s[i] != '\n' && s[i] != 32)
    {
        i++;
        count++;
    }
    return (count);
}

void    process_paths(t_data *data, char *str, t_type type)
{
    (void)data;
    int i = skip_beg_path(str);
    int j = len_str_path(str, i);
    // char *s = ft_substr(str, i, j);
    if (type == NO)
        data->north_path = ft_substr(str, i, j);
    else if (type == SO)
        data->south_path = ft_substr(str, i, j);
    else if (type == WE)
        data->west_path = ft_substr(str, i, j);
    else if (type == EA)
        data->east_path = ft_substr(str, i, j);
    // printf("%s\n", s);
}

void    extract_paths(t_read *file, t_data *data)
{

    while (file)
    {
        if (file->type == NO)
            process_paths(data, file->line, NO);
        else if (file->type == SO)
            process_paths(data, file->line, SO);
        else if (file->type == WE)
            process_paths(data, file->line, WE);
        else if (file->type == EA)
            process_paths(data, file->line, EA);
        file = file->next;
    }

    // check if paths valid and if not free and leavs    
    // if () 

    // }
    
}