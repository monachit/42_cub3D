/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younesounajjar <younesounajjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:35:17 by monachit          #+#    #+#             */
/*   Updated: 2024/10/21 16:21:43 by younesounaj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int check_dup(t_read **file, t_type type)
{
    t_read  *curr = *file;
    int i = 0;
    while (curr)
    {
        if (curr->type == type)
            i++;
        curr = curr->next;
    }
    return (i);
}

void    insert_map(t_map **map, char *str)
{
    t_map *new = malloc(sizeof(t_map));
    new->line = str;
    new->next = NULL;
    if (!(*map))
        *map = new;
    else
    {
        t_map *curr = *map;
        while (curr->next)
            curr = curr->next;
        curr->next = new;
    }
}

void    collect_map(t_read **read, t_data *data, int *len)
{
    t_map *map = NULL;
    t_read *curr = *read;
    int flg = 0;
    int i = 0;
    while (curr)
    {
        if (flg == 1 && curr->type == MAP)
            ft_show_error("Lines between map!\n");
        if (curr->type == MAP)
        {
            while (curr && curr->type == MAP)
            {
                char *s = ft_substr(curr->line, 0, ft_strlen(curr->line) - 1);
                insert_map(&map, s);
                i++;
                curr = curr->next;
            }
            flg = 1;
        }
        else
            curr = curr->next;
    }
    *len = i;
    data->head_map = map;
}

int calcul_character(t_map *map, char c)
{
    map = map->next;
    int count = 0;
    while (map->next)
    {
        int i = 0;
        while (map->line[i])
        {
            if (c == map->line[i])
                count++;
            i++;
        }
        map = map->next;
    }
    return (count);
    
}


void    check_map_last(t_read *file)
{
    while (file && file->type != MAP)
        file = file->next;
    while (file && file->type == MAP)
        file = file->next;
    while (file)
    {
        if (file->type != INIT)
            ft_show_error("Map syntax!");
        file = file->next;
    }
}


void    map_to_char(t_data *data, int len_map)
{
    data->map = (char **)malloc(sizeof(char *) * (len_map + 1));
    if (!data->map)
        exit (1);
    t_map *curr = data->head_map;
    int i = 0;
    while (curr)
    {
        data->map[i++] = ft_strdup(curr->line);
        curr = curr->next;
    }
    data->map[i] = NULL;
}


bool    map_characters(t_data *data)
{
    int i = 0;
    int count = 0;
    char *str = "NEWS";
    char *s2 = "NEWS0";
    while (data->map[i])
    {
        int j = 0;
        while (data->map[i][j])
        {
            if (ft_strchr(str, data->map[i][j]))
                count++;
            if (ft_strchr(s2, data->map[i][j]))
            {
                if ((data->map[i + 1][j] == 32 || data->map[i - 1][j] == 32 
                    || data->map[i][j + 1] == 32 || data->map[i][j - 1] == 32))
                    return(false);
            }
            j++;
        }
        i++;
    }
    if (count != 1)
        return (false);
    else
        return (true);
}

void    map_parse(t_data *data)
{
    if (map_characters(data) == false)
        ft_show_error("Characters in map invalid!\n");
    
}

t_data  parse(int ac, char **av)
{
    t_read  *file;
    t_data  data;

    if (ac != 2)
        ft_show_error("Arguments number not valid >./cub3d name.cub<\n");
    if (check_name(av[1]))
        ft_show_error("Map name not valid >name.cub<\n");
    file = read_file(av[1]);
    init_data(&data);
    collect_data(&file, &data);
    if (check_dup(&file, NO) != 1 || check_dup(&file, SO) != 1 || check_dup(&file, WE) != 1
        || check_dup(&file, EA) != 1 || check_dup(&file, F) != 1 || check_dup(&file, C) != 1
        || check_dup(&file, MAP) < 3)
        ft_show_error("Line missing or duplicated on file!\n");
    check_map_last(file);
    int len_map;
    collect_map(&file, &data, &len_map);
    map_to_char(&data, len_map);
    map_parse(&data);
    return (data);
}
