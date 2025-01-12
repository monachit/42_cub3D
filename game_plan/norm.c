/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:34:51 by mnachit           #+#    #+#             */
/*   Updated: 2025/01/12 23:58:20 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	close_window(void *v)
{
	(void)v;
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
	if (wall_check(new_x, new_y, vars))
	{
		vars->p_x = new_x;
		vars->p_y = new_y;
	}
	vars->direction = nor_angle(vars->direction);
	drawing(vars);
	return (0);
}

void	clear_image(t_vars *vars, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < S_H)
	{
		x = 0;
		while (x < S_W)
		{
			my_mlx_pixel_put(vars, x, y, color);
			x++;
		}
		y++;
	}
}
