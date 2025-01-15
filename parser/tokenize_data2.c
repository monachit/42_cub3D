/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_data2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:47:27 by younajja          #+#    #+#             */
/*   Updated: 2025/01/15 22:53:41 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	norme_process_lone(t_read *line_file)
{
	if (check_empty_line(line_file->line))
		line_file->type = EMPTY;
	else if (check_characters(line_file->line))
		line_file->type = MAP;
}

void	process_line(t_read *line_file)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (calcul_words(line_file->line) == 2)
	{
		i = skip_spaces(line_file->line, 0);
		tmp = ft_substr(line_file->line, i, extract_len(line_file->line, i));
		if (!ft_strcmp("F", tmp))
			line_file->type = F;
		else if (!ft_strcmp("C", tmp))
			line_file->type = C;
		else if (!ft_strcmp("NO", tmp))
			line_file->type = NO;
		else if (!ft_strcmp("SO", tmp))
			line_file->type = SO;
		else if (!ft_strcmp("WE", tmp))
			line_file->type = WE;
		else if (!ft_strcmp("EA", tmp))
			line_file->type = EA;
		free(tmp);
	}
	norme_process_lone(line_file);
}

void	token_data(t_read **file)
{
	t_read	*curr;

	curr = *file;
	while (curr)
	{
		process_line(curr);
		curr = curr->next;
	}
}
