/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:35:17 by monachit          #+#    #+#             */
/*   Updated: 2025/01/15 22:54:49 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	init_data(t_data *data)
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

void	norme_parse(int ac, char **av)
{
	if (ac != 2)
		ft_show_error("Arguments number not valid >./cub3d name.cub<\n");
	if (check_name(av[1]))
		ft_show_error("Map name not valid >name.cub<\n");
}

t_data	parse(int ac, char **av)
{
	t_read	*file;
	t_data	data;

	norme_parse(ac, av);
	file = read_file(av[1]);
	token_data(&file);
	if (!check_order(file))
	{
		free_read(&file);
		ft_show_error("File syntax invalid\n");
	}
	init_data(&data);
	extract_colors(file, &data);
	extract_paths(file, &data);
	data.map = extract_map(file, calcul_token(file, MAP));
	if (!data.map)
	{
		free_data(&data);
		free_read(&file);
		ft_show_error("Map not valid");
	}
	free_read(&file);
	return (data);
}
