/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:34:51 by mnachit           #+#    #+#             */
/*   Updated: 2025/01/16 00:18:05 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	close_window(void *v)
{
	t_vars	*vars;

	vars = v;
	mlx_destroy_image(vars->mlx, vars->textures.north->img);
	mlx_destroy_image(vars->mlx, vars->textures.south->img);
	mlx_destroy_image(vars->mlx, vars->textures.east->img);
	mlx_destroy_image(vars->mlx, vars->textures.west->img);
	free(vars->textures.north);
	free(vars->textures.south);
	free(vars->textures.east);
	free(vars->textures.west);
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free_data(vars->data);
	exit(EXIT_SUCCESS);
	return (0);
}

void	key_hook2(int keycode, t_vars *vars, double *new_x, double *new_y)
{
	if (keycode == 119)
	{
		*new_x += cos(vars->direction) * 20.0;
		*new_y += sin(vars->direction) * 20.0;
	}
	else if (keycode == 97)
	{
		*new_x += sin(vars->direction) * 20.0;
		*new_y -= cos(vars->direction) * 20.0;
	}
	else if (keycode == 100)
	{
		*new_x -= sin(vars->direction) * 20.0;
		*new_y += cos(vars->direction) * 20.0;
	}
	else if (keycode == 115)
	{
		*new_x -= cos(vars->direction) * 20.0;
		*new_y -= sin(vars->direction) * 20.0;
	}
	else if (keycode == 65361)
		vars->direction -= 0.1;
	else if (keycode == 65363)
		vars->direction += 0.1;
}

int	key_hook(int keycode, t_vars *vars)
{
	double	new_x;
	double	new_y;

	new_x = vars->p_x;
	new_y = vars->p_y;
	key_hook2(keycode, vars, &new_x, &new_y);
	if (keycode == 65307)
		close_window(vars);
	if (!wall_check(new_x + 25, new_y - 25, vars))
		return (0);
	if (!wall_check(new_x - 25, new_y + 25, vars))
		return (0);
	if (!wall_check(new_x + 25, new_y + 25, vars))
		return (0);
	if (!wall_check(new_x - 25, new_y - 25, vars))
		return (0);
	else
	{
		vars->p_x = new_x;
		vars->p_y = new_y;
	}
	vars->direction = nor_angle(vars->direction);
	drawing(vars);
	return (0);
}
