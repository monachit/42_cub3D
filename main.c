/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:47:33 by monachit          #+#    #+#             */
/*   Updated: 2025/01/15 22:58:52 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_data(t_data *data)
{
	int	i;

	free(data->east_path);
	free(data->west_path);
	free(data->north_path);
	free(data->south_path);
	if (!data->map)
		return ;
	i = 0;
	while (data->map[i])
		free(data->map[i++]);
	free(data->map);
}

int	main(int ac, char **av)
{
	t_data	data;

	data = parse(ac, av);
	game_plan(&data);
	free_data(&data);
	return (0);
}
