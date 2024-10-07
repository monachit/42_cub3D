/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younesounajjar <younesounajjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:35:17 by monachit          #+#    #+#             */
/*   Updated: 2024/10/04 14:07:28 by younesounaj      ###   ########.fr       */
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


void    collect_data(t_read **file, t_data *data)
{

    t_read  *curr = *file;
    while (curr)
    {

        int i = skip_spaces(curr->line, 0);
        if (!ft_strcmp("NO", ft_substr(curr->line, i, extract_len_first_word(curr->line, i))))
        {
            i = skip_spaces(curr->line, extract_len_first_word(curr->line, i));
            data->north_path = ft_substr(curr->line, i, extract_len_first_word(curr->line, i));
            // curr->line = NULL;
            curr->type = NO;
        }
        else if (!ft_strcmp("SO", ft_substr(curr->line, i, extract_len_first_word(curr->line, i))))
        {
            i = skip_spaces(curr->line, extract_len_first_word(curr->line, i));
            data->south_path = ft_substr(curr->line, i, extract_len_first_word(curr->line, i));
            // curr->line = NULL;
            curr->type = SO;
        }
        else if (!ft_strcmp("WE", ft_substr(curr->line, i, extract_len_first_word(curr->line, i))))
        {
            i = skip_spaces(curr->line, extract_len_first_word(curr->line, i));
            data->west_path = ft_substr(curr->line, i, extract_len_first_word(curr->line, i));
            curr->type = WE;
        }
        else if (!ft_strcmp("EA", ft_substr(curr->line, i, extract_len_first_word(curr->line, i))))
        {
            i = skip_spaces(curr->line, extract_len_first_word(curr->line, i));
            data->east_path = ft_substr(curr->line, i, extract_len_first_word(curr->line, i));
            curr->type = EA;
        }
        else if (!ft_strcmp("F", ft_substr(curr->line, i, extract_len_first_word(curr->line, i))))
        {
            i = skip_spaces(curr->line, extract_len_first_word(curr->line, i));
            if (check_nb_virgul(ft_substr(curr->line, i, extract_len_first_word(curr->line, i))) != 2)
                ft_show_error("Floor color input invalid!\n");
            ft_rgb_colors(ft_substr(curr->line, i, extract_len_first_word(curr->line, i)), &data->f1, 
                &data->f2, &data->f3);
            curr->type = F;
        }
        else if (!ft_strcmp("C", ft_substr(curr->line, i, extract_len_first_word(curr->line, i))))
        {
            i = skip_spaces(curr->line, extract_len_first_word(curr->line, i));
            if (check_nb_virgul(ft_substr(curr->line, i, extract_len_first_word(curr->line, i))) != 2)
                ft_show_error("Ceiling color input invalid!\n");
            ft_rgb_colors(ft_substr(curr->line, i, extract_len_first_word(curr->line, i)), &data->c1, 
                &data->c2, &data->c3);
            curr->type = C;
        }
        else if (curr->nb_words > 0 && map_token(curr->line))
        {
            curr->type = MAP;
            // printf("%s", curr->line);
        }
        else if (ft_strcmp(curr->line, "\n"))
            ft_show_error("invalid line!\n");

            // printf("type = %d, nb_words = %d / %s", curr->type, curr->nb_words, curr->line);
        // printf("calcul : %d; s = /%s/", curr->nb_words, curr->line);m
        // printf("TYPE : %d/ NB_WORDS / %d/ LINE : %s\n", curr->type, curr->nb_words, curr->line);
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

void    collect_map(t_read **read, t_data *data)
{
    t_map *map = NULL;
    t_read *curr = *read;
    int flg = 0;
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
                curr = curr->next;
            }
            flg = 1;
        }
        else
            curr = curr->next;
    }
    data->head_map = map;
}

void    map_closed(t_map *map)
{
    int i = 0;
    while (map->line[i])
    {
        if (map->line[i] != 32 && map->line[i] != '1')
            ft_show_error("Map not closed!\n");
        i++;
    }
    while (map->next)
    {
        i = 0;
        while (map->line[i] == 32)
            i++;
        if (map->line[i] != '1')
            ft_show_error("Map not closed!\n");
        while (map->line[i])
            i++;
        i--;
        while (map->line[i] == 32)
            i--;
        if (map->line[i] != '1')
            ft_show_error("Map not closed!\n");
        map = map->next;
    }
    i = 0;
    while (map->line[i])
    {
        if (map->line[i] != 32 && map->line[i] != '1')
            ft_show_error("Map not closed!\n");
        i++;
    }
}

void    check_len_spaces(t_map *map)
{
    while (map)
    {
        int i = 0;
        int len = 0;
        while (map->line[i])
        {
            if (map->line[i] == 32)
                i++;
            else
            {
                i++;
                len++;
            }
        }
        if (len < 3)
            ft_show_error("Len of map !\n");
        map = map->next;
    }
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

void    parse_map(t_map *map)
{
    map_closed(map);
    check_len_spaces(map);
    if (calcul_character(map, 'N') != 1 || calcul_character(map, 's') > 1
        || calcul_character(map, 'E') > 1 || calcul_character(map, 'W') > 1)
        ft_show_error("Characters of map invalid!\n");
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

void	free_list(t_read **list)
{
	t_read	*curr;
	t_read	*aux;

	if (!(*list))
		return ;
	curr = *list;
	while (curr != NULL)
	{
		aux = curr->next;
		free(curr);
		curr = aux;
	}
	*list = NULL;
}

void    ft_free_line_read(t_read **file)
{
    t_read *curr = *file;
    while (curr)
    {
        free(curr->line);
        curr = curr->next;
    }
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
    collect_map(&file, &data);
    parse_map(data.head_map);
    check_map_last(file);
    return (data);
}
