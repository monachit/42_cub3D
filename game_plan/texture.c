/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:37:50 by mnachit           #+#    #+#             */
/*   Updated: 2025/01/16 01:08:59 by mnachit          ###   ########.fr       */
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
	(void)ray;
	if (vars->flg_achmn_hayt == 0)
		return (vars->data->h % TILE_SIZE);
	else
		return (vars->data->v % TILE_SIZE);
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
	if (!txt->img)
	{
		free(txt);
		write(2, "Path to image invalid!\n", 23);
		return (NULL);
	}
	txt->addr = mlx_get_data_addr(txt->img, &txt->bit_per_pixel,
			&txt->line_length, &txt->endian);
	return (txt);
}

void	init_tssawer_amaalem(t_data *data, t_vars *vars)
{
	vars->textures.north = texture_loader(vars, data->north_path);
	if (!vars->textures.north)
		ft_free_norme_one(vars);
	vars->textures.south = texture_loader(vars, data->south_path);
	if (!vars->textures.south)
	{
		mlx_destroy_image(vars->mlx, vars->textures.north->img);
		free(vars->textures.north);
		ft_free_norme_one(vars);
	}
	vars->textures.east = texture_loader(vars, data->east_path);
	if (!vars->textures.east)
	{
		mlx_destroy_image(vars->mlx, vars->textures.north->img);
		free(vars->textures.north);
		mlx_destroy_image(vars->mlx, vars->textures.south->img);
		free(vars->textures.south);
		ft_free_norme_one(vars);
	}
	vars->textures.west = texture_loader(vars, data->west_path);
	if (!vars->textures.west)
	{
		ft_norm_free_txt(vars);
		ft_free_norme_one(vars);
	}
}
