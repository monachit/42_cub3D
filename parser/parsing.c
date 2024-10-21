/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younesounajjar <younesounajjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:35:17 by monachit          #+#    #+#             */
/*   Updated: 2024/10/21 15:57:12 by younesounaj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int check_name(char *name)
{
    int i;

    i = 0;
    while (name[i])
    {
        if (name[i] == '.')
        {
            if (name[i + 1] == 'c' && name[i + 2] == 'u' && name[i + 3] == 'b' && name[i + 4] == '\0')
                return (0);
            else
                return (1);
        }
        i++;
    }
    return (1);
}


t_read  *read_file(char *av)
{
    char *line;
    int fd;
    t_read  *read = NULL;

    fd = open(av, O_RDONLY);
    if (fd == -1)
        ft_show_error("File not found!\n");    
    line = get_next_line(fd);
    while (line)
    {
        insert_t_read(&read, ft_strdup(line));
        free(line);
        line = get_next_line(fd);
    }
    return (read);
}



int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] && s1[i] == s2[i])
        i++;
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

void    init_data(t_data *data)
{
    data->c1 = -1;
    data->c2 = -1;
    data->c3 = -1;
    data->f1 = -1;
    data->f2 = -1;
    data->f3 = -1;
    data->north_path = NULL;
    data->south_path = NULL;
    data->east_path = NULL;
    data->west_path = NULL;
}

int extract_len_first_word(char *s, int i)
{
    int j = 0;
    while (s[i] && s[i] != 32 && s[i] != '\n')
    {
        i++;
        j++;
    }
    return (j);
}

int skip_spaces(char *s, int i)
{
    while (s[i] == 32)
        i++;
    return (i);
}

int	ft_atoi_lhbal(char *str)
{
	int	i;
	int	res;
	int	prev;

	i = 0;
	res = 0;
	prev = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = res;
		res = res * 10 + str[i] - 48;
		if (prev != res / 10)
			return (-1);
		i++;
	}
	return (res);
}

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
    if (nb1 > 250 || nb2 > 250 || nb3 > 250) 
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
        {
            return (0);
        }
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

// void	free_list(t_read **list)
// {
// 	t_read	*curr;
// 	t_read	*aux;

// 	if (!(*list))
// 		return ;
// 	curr = *list;
// 	while (curr != NULL)
// 	{
// 		aux = curr->next;
// 		free(curr);
// 		curr = aux;
// 	}
// 	*list = NULL;
// }


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
