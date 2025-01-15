/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_colors2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:00:52 by younajja          #+#    #+#             */
/*   Updated: 2025/01/15 22:01:07 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	extract_numbers(t_data *data, char *s, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (c == 'c')
		norme_c(data, i, s, tmp);
	else if (c == 'f')
	{
		tmp = ft_substr(s, i, len_nb(s, &i));
		data->f1 = ft_atoi_lhbal(tmp);
		i++;
		free(tmp);
		tmp = ft_substr(s, i, len_nb(s, &i));
		data->f2 = ft_atoi_lhbal(tmp);
		i++;
		free(tmp);
		tmp = ft_substr(s, i, len_nb(s, &i));
		data->f3 = ft_atoi_lhbal(tmp);
		free(tmp);
	}
}

void	process_colors(t_read *file, t_data *data, char *str, char c)
{
	int		i;
	int		j;
	char	*s;

	(void)data;
	i = skip_beg(str);
	j = len_str_color(str, i);
	s = ft_substr(str, i, j);
	if (check_virguls(s) != 2)
	{
		free(s);
		free_read(&file);
		ft_show_error("Colors invalid!\n");
	}
	extract_numbers(data, s, c);
	free(s);
}

void	extract_colors(t_read *file, t_data *data)
{
	t_read	*head;

	head = file;
	while (head)
	{
		if (head->type == F)
			process_colors(file, data, head->line, 'f');
		else if (head->type == C)
			process_colors(file, data, head->line, 'c');
		head = head->next;
	}
	if (data->c1 < 0 || data->c1 > 255 || data->c2 < 0 || data->c2 > 255
		|| data->c3 < 0 || data->c3 > 255 || data->f1 < 0 || data->f1 > 255
		|| data->f2 < 0 || data->f2 > 255 || data->f3 < 0 || data->f3 > 255)
	{
		free_read(&file);
		ft_show_error("RGB colors range invalid [0,255]\n");
	}
}
