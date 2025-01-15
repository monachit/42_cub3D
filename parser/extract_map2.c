/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:44:09 by younajja          #+#    #+#             */
/*   Updated: 2025/01/15 22:44:26 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	free_map(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

char	**extract_map(t_read *file, int len)
{
	char	**strs;

	strs = norme_map(file, len);
	if (!check_player(strs) || !parse_map(strs))
	{
		free_map(strs);
		return (NULL);
	}
	return (strs);
}
