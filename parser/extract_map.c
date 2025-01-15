/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:04:55 by younajja          #+#    #+#             */
/*   Updated: 2025/01/15 22:44:07 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_strlen_lhbal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

bool	check_player(char **ss)
{
	char	*player;
	int		i;
	int		count;
	int		j;

	player = "NSWE";
	i = 0;
	count = 0;
	while (ss[i])
	{
		j = 0;
		while (ss[i][j])
		{
			if (ft_strchr(player, ss[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (count == 1)
		return (true);
	else
		return (false);
}

bool	parse_map(char **map)
{
	char	*c;
	int		i;
	int		j;

	c = "0NSWE";
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(c, map[i][j]))
			{
				if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1])
					return (false);
				if (map[i][j + 1] == 32 || map[i][j - 1] == 32 || map[i
					+ 1][j] == 32 || map[i - 1][j] == 32 || !map[i][j + 1]
					|| !map[i][j - 1] || !map[i + 1][j] || !map[i - 1][j])
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

char	**allocation_strs(int len)
{
	char	**strs;

	strs = (char **)malloc(sizeof(char *) * (len + 1));
	if (!strs)
		exit(EXIT_FAILURE);
	return (strs);
}

char	**norme_map(t_read *file, int len)
{
	char	*tmp;
	char	**strs;
	int		i;

	i = 0;
	strs = allocation_strs(len);
	while (file)
	{
		if (file->type == MAP)
		{
			while (file && file->type == MAP)
			{
				tmp = ft_substr(file->line, 0, ft_strlen_lhbal(file->line));
				strs[i] = ft_strdup(tmp);
				file = file->next;
				free(tmp);
				i++;
			}
			strs[i] = NULL;
			break ;
		}
		file = file->next;
	}
	return (strs);
}
