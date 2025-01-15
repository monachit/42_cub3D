/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:46:02 by younajja          #+#    #+#             */
/*   Updated: 2025/01/15 22:46:12 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	skip_beg_path(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32)
		i++;
	while (str[i] && str[i] != 32)
		i++;
	while (str[i] == 32)
		i++;
	return (i);
}

int	len_str_path(char *s, int i)
{
	int	count;

	count = 0;
	while (s[i] && s[i] != '\n' && s[i] != 32)
	{
		i++;
		count++;
	}
	return (count);
}

void	process_paths(t_data *data, char *str, t_type type)
{
	int	i;
	int	j;

	(void)data;
	i = skip_beg_path(str);
	j = len_str_path(str, i);
	if (type == NO)
		data->north_path = ft_substr(str, i, j);
	else if (type == SO)
		data->south_path = ft_substr(str, i, j);
	else if (type == WE)
		data->west_path = ft_substr(str, i, j);
	else if (type == EA)
		data->east_path = ft_substr(str, i, j);
}

void	extract_paths(t_read *file, t_data *data)
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
}
