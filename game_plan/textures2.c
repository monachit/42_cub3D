/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 00:57:59 by younajja          #+#    #+#             */
/*   Updated: 2025/01/16 01:00:22 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	ft_norm_free_txt(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->textures.north->img);
	free(vars->textures.north);
	mlx_destroy_image(vars->mlx, vars->textures.south->img);
	free(vars->textures.south);
	mlx_destroy_image(vars->mlx, vars->textures.east->img);
	free(vars->textures.east);
}

void	ft_free_norme_one(t_vars *vars)
{
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free_data(vars->data);
	exit(1);
}
