/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:46:54 by younajja          #+#    #+#             */
/*   Updated: 2025/01/15 22:47:35 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] == 32)
		i++;
	return (i);
}

int	calcul_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != 32)
		{
			count++;
			while (str[i] && str[i] != 32 && str[i] != '\n')
				i++;
		}
		while (str[i] == 32)
			i++;
	}
	return (count);
}

int	extract_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != '\n' && str[i] != 32)
	{
		len++;
		i++;
	}
	return (len);
}

bool	check_characters(char *str)
{
	int		i;
	char	*s;

	i = 0;
	s = "10NSEW ";
	while (str[i] && str[i] != '\n')
	{
		if (!ft_strchr(s, str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != 32)
			return (false);
		i++;
	}
	return (true);
}
