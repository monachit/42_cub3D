/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:35:17 by monachit          #+#    #+#             */
/*   Updated: 2024/09/15 15:03:10 by monachit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

char *ft_call_strjoin(char *line2, char *line)
{
    char *tmp;

    tmp = ft_strjoin(line2, line);
    free(line2);
    free(line);
    return (tmp);
}

char **check_map(char *av)
{
    char **map;
    char *line2;
    char *line;
    int fd;

    fd = open(av, O_RDONLY);
    if (fd == -1)
        return (NULL);
    line = get_next_line(fd);
    line2 = ft_strdup("");
    while (line)
    {
        line2 = ft_call_strjoin(line2, line);
        line = get_next_line(fd);
    }
    map = ft_split(line2, '\n');
    free(line2);
    return (map);
}

int	ft_len(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

void    check_wall0(char **map)
{
    int i;

    i = 0;
    while (map[6][i])
    {
        if (map[6][i] == ' ' || map[ft_len(map) - 1][i] == ' ')
            i++;
        else if (map[6][i] != '1' || map[ft_len(map) - 1][i] != '1')
        {
            printf("Error\n");
            exit(1);
        }
        i++;
    }
}

void    check_wall1(char **map)
{
    int i;

    i = 6;
    while (i < ft_len(map) - 1)
    {
        if (map[i][0] == ' ' || map[i][ft_strlen(map[i]) - 1] == ' ')
            i++;
        else if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
        {
            printf("Error\n");
            exit(1);
        }
        else
            i++;
    }
}

void    check_error(char **map)
{
    check_wall0(map);
    check_wall1(map);
    return ;
}

char **parse(int ac, char **av)
{
    char **map;
    
    if (ac != 2)
        ft_show_error("error\n");
    if (check_name(av[1]))
        ft_show_error("error\n");
    if (open(av[1], O_RDONLY) == -1)
        ft_show_error("error\n");
    map = check_map(av[1]);
    check_error(map);
    return (map);

}