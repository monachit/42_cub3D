/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:41:44 by mnachit           #+#    #+#             */
/*   Updated: 2025/01/16 00:20:21 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	rander_wall2(int top_p, int bottom_p, t_vars *vars, double ray_a)
{
	double		wall_h;
	int			tmp_y;
	int			y;
	int			x;
	t_textures	*tmp;

	x = get_x(vars, ray_a);
	tmp_y = top_p;
	wall_h = vars->norm_1;
	while (top_p <= bottom_p)
	{
		y = (top_p - tmp_y) * TILE_SIZE / wall_h;
		tmp = chose_image(vars, ray_a);
		my_mlx_pixel_put(vars, vars->norm2, top_p, my_mlx_pixel_get(tmp, x, y));
		top_p++;
	}
}

int	rgb(int R, int G, int B)
{
	return ((R << 16) | (G << 8) | B);
}

void	rander_wall(t_vars *vars, int ray, double ray_a)
{
	double	wall_h;
	double	bottom_p;
	double	top_p;
	int		b;
	int		tmp_y;

	vars->distence *= cos(ray_a - vars->direction);
	wall_h = (TILE_SIZE / vars->distence) * (S_H / 100 * TILE_SIZE / 2)
		/ tan(60 * (PI / 180) / 2);
	vars->norm_1 = wall_h;
	vars->norm2 = ray;
	top_p = (S_H / 2) - (wall_h / 2);
	bottom_p = (S_H / 2) + (wall_h / 2);
	tmp_y = top_p;
	b = bottom_p;
	while (tmp_y >= 0)
		my_mlx_pixel_put(vars, ray, (int)tmp_y--, rgb(vars->data->c1,
				vars->data->c2, vars->data->c3));
	while (b < S_H)
		my_mlx_pixel_put(vars, ray, (int)b++, 0x4290F5);
	rander_wall2((int)top_p, (int)bottom_p, vars, ray_a);
}

void	cast_rays2(t_vars *vars, double x, double y)
{
	if (x < y)
	{
		vars->flg_achmn_hayt = 1;
		vars->distence = x;
	}
	else
	{
		vars->flg_achmn_hayt = 0;
		vars->distence = y;
	}
}

void	cast_rays(t_vars *vars)
{
	double	first_ray;
	double	x_inter;
	double	h_inter;
	double	add_angl;
	int		ray;

	add_angl = (60 * (PI / 180) / (S_W));
	ray = 0;
	first_ray = vars->direction - (60 * (PI / 180) / 2);
	while (ray < S_W)
	{
		x_inter = get_v_inter(vars, nor_angle(first_ray));
		h_inter = get_h_inter(vars, nor_angle(first_ray));
		cast_rays2(vars, x_inter, h_inter);
		rander_wall(vars, ray, first_ray);
		first_ray += add_angl;
		ray++;
	}
}
