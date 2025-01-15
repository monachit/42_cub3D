/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:42:41 by monachit          #+#    #+#             */
/*   Updated: 2025/01/15 03:38:47 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	if ((y >= S_H) || (x >= S_W) || (x < 0) || (y < 0))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_vars *vars, int x, int y, int size, int color)
{
	for (int i = 0; i < size; i++)  // Loop through the square's height
	{
		for (int j = 0; j < size; j++)  // Loop through the square's width
		{
			my_mlx_pixel_put(vars, x + j, y + i, color);  // Plot the pixel
		}
	}
}

void	drawing(t_vars *vars)
{
	//clear_image(vars, 0x000000);
	// draw_square(vars, vars->p, vars->c, 20, 0xFF6FFF);
    // for (int i = 0; i < vars->win_height; i++) 
    // {
    //     for (int j = 0; j < vars->win_width; j++) 
    //     {
    //         if (vars->map1[i][j] == '1')
    //             draw_square(vars, j * 100, i * 100, 100, 0xFF6FFF); 
    //     }
    // }
	cast_rays(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

void	handl_direction(t_data *data, double *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N')
				*s = PI / 2;
			else if (data->map[i][j] == 'E')
				*s = 0;
			else if (data->map[i][j] == 'W')
				*s = PI;
			else if (data->map[i][j] == 'S')
				*s = 3 * PI / 2;
			if (*s != -1)
				return ;
			j++;
		}
		i++;
	}
}

void	player_p(t_vars *vars, t_data *data)
{
	int	j;
	int	i;

	j = 0;
	while (j < vars->win_height)
	{
		i = 0;
		while (i < vars->win_width)
		{
			if (data->map[j][i] != '1' && data->map[j][i] == '0')
			{
				vars->p_x = i * 100;
				vars->p_y = j * 100;
			}
			i++;
		}
		j++;
	}
}

void	game_plan(t_data *data)
{
	t_vars	vars;

	vars.map1 = data->map;
	vars.data = data;
	vars.mlx = mlx_init();
	vars.win_width = ft_strlen(data->map[0]);
	vars.win_height = 0;
	vars.direction = -1;
	
	handl_direction(data, &vars.direction);
	while (data->map[vars.win_height])
		vars.win_height++;
	init_tssawer_amaalem(data, &vars);
	vars.win = mlx_new_window(vars.mlx, S_W, S_H, "YWAAA");
	if (!vars.win)
		ft_show_error("mlx_new_window function fails");
	vars.img = mlx_new_image(vars.mlx, S_W, S_H);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel,
			&vars.line_length, &vars.endian);
	player_p(&vars, data);
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_hook(vars.win, 17, 0L, close_window, &vars);
	mlx_loop(vars.mlx);
}
