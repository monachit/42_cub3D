/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:44:43 by mnachit           #+#    #+#             */
/*   Updated: 2025/01/13 00:03:34 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

double	get_h_inter(t_vars *vars, double angl)
{
	double	h_x;
	double	h_y;
	double	x_step;
	double	y_step;

	y_step = TILE_SIZE;
	if (rayfacing_up(angl))
		y_step *= -1;
	x_step = y_step / tan(angl);
	if ((rayfacing_left(angl) && x_step > 0) || (rayfacing_right(angl)
			&& x_step < 0))
		x_step *= -1;
	if (rayfacing_down(angl))
		h_y = floor(vars->p_y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	else
		h_y = floor(vars->p_y / TILE_SIZE) * TILE_SIZE - 0.001;
	printf("%f\n ", h_y);
	h_x = vars->p_x + (h_y - vars->p_y) / tan(angl);
	while (wall_check(h_x, h_y, vars))
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - vars->p_x, 2) + pow(h_y - vars->p_y, 2)));
}

double	get_v_inter(t_vars *vars, double angl)
{
	double	v_x;
	double	v_y;
	double	x_step;
	double	y_step;

	x_step = TILE_SIZE;
	if (rayfacing_left(angl))
		x_step *= -1;
	y_step = x_step * tan(angl);
	if ((rayfacing_up(angl) && y_step > 0) || (rayfacing_down(angl)
			&& y_step < 0))
		y_step *= -1;
	if (rayfacing_left(angl))
		v_x = floor(vars->p_x / TILE_SIZE) * TILE_SIZE - 0.001;
	else
		v_x = floor(vars->p_x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	v_y = vars->p_y + (v_x - vars->p_x) * tan(angl);
	while (wall_check(v_x, v_y, vars))
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - vars->p_x, 2) + pow(v_y - vars->p_y, 2)));
}

int	wall_check(double x, double y, t_vars *vars)
{
	int	mx;
	int	my;

	mx = (int)(x / TILE_SIZE);
	my = (int)(y / TILE_SIZE);
	if (mx < 0 || my < 0 || mx >= vars->win_width || my >= vars->win_height)
		return (0);
	if (vars->map1[my][mx] == '1')
		return (0);
	return (1);
}
