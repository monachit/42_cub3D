/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:37:50 by mnachit           #+#    #+#             */
/*   Updated: 2025/01/13 00:06:00 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	my_mlx_pixel_get(t_textures *txt, int x, int y)
{
	int	color;

	if ((y >= txt->height * 100) || (x >= txt->width * 100))
		return (0);
	color = *(int *)(txt->addr + (y * txt->line_length + x * (txt->bit_per_pixel
					/ 8)));
	return (color);
}

int	get_x(t_vars *vars, double ray)
{
	if (vars->flg_achmn_hayt == 0)
		return (fmod((vars->p_x + cos(ray) * vars->distence), TILE_SIZE));
	else
		return (fmod((vars->p_y + sin(ray) * vars->distence), TILE_SIZE));
}

t_textures	*chose_image(t_vars *vars, double ray_a)
{
	if (rayfacing_up(ray_a) && vars->flg_achmn_hayt == 0)
		return (vars->textures.north);
	else if (rayfacing_down(ray_a) && vars->flg_achmn_hayt == 0)
		return (vars->textures.south);
	else if (rayfacing_left(ray_a) && vars->flg_achmn_hayt == 1)
		return (vars->textures.west);
	else if (rayfacing_right(ray_a) && vars->flg_achmn_hayt == 1)
		return (vars->textures.east);
	return (NULL);
}

t_textures	*texture_loader(t_vars *vars, char *path)
{
	t_textures	*txt;

	txt = malloc(sizeof(t_textures));
	txt->img = mlx_xpm_file_to_image(vars->mlx, path, &txt->width,
			&txt->height);
	txt->addr = mlx_get_data_addr(txt->img, &txt->bit_per_pixel,
			&txt->line_length, &txt->endian);
	return (txt);
}

void	init_tssawer_amaalem(t_data *data, t_vars *vars)
{
	vars->textures.north = texture_loader(vars, data->north_path);
	vars->textures.south = texture_loader(vars, data->south_path);
	vars->textures.east = texture_loader(vars, data->east_path);
	vars->textures.west = texture_loader(vars, data->west_path);
}
