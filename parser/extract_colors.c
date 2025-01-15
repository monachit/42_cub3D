/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 05:32:25 by younajja          #+#    #+#             */
/*   Updated: 2025/01/15 05:48:28 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	skip_beg(char *str)
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

int	len_str_color(char *s, int i)
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

int	check_virguls(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[i] == ',')
		return (-1);
	while (s[i])
	{
		if (i + 1 < (int)ft_strlen(s) && s[i] == ',' && s[i + 1] == ',')
			return (-1);
		if (s[i] == ',')
			count++;
		if (s[i] != ',' && !ft_isdigit(s[i]))
			return (-1);
		i++;
	}
	if (s[i - 1] == ',')
		return (-1);
	return (count);
}

int	len_nb(char *s, int *i)
{
	int	i1;
	int	len;

	i1 = *i;
	len = 0;
	while (ft_isdigit(s[i1]))
	{
		len++;
		i1++;
	}
	*i = i1;
	return (len);
}

void	norme_c(t_data *data, int i, char *s, char *tmp)
{
	tmp = ft_substr(s, i, len_nb(s, &i));
	data->c1 = ft_atoi_lhbal(tmp);
	i++;
	free(tmp);
	tmp = ft_substr(s, i, len_nb(s, &i));
	data->c2 = ft_atoi_lhbal(tmp);
	free(tmp);
	i++;
	tmp = ft_substr(s, i, len_nb(s, &i));
	data->c3 = ft_atoi_lhbal(tmp);
	free(tmp);
}
