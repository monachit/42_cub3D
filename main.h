/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:35:46 by monachit          #+#    #+#             */
/*   Updated: 2024/10/04 15:42:40 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include "get_next_line/get_next_line.h"
# include <math.h>

#define PI 3.141592653589793
#define NUM_RAYS 36
#define length_ray  10;

typedef struct s_vars
{
	char	**map1;
	int		player_x;
	int		player_y;
	int		heigth;
	int		width;
	int 	p_1;
	void	*mlx;
	void	*win;
	void	*img;
		char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int p_x;
	int p_y;
	int win_width;
	int win_height;
	int c;
	int p;
}	t_vars;

typedef struct s_vector
{
	double d_x;
	double d_y;
	
}	vector;

void    game_plan(char **map);
char 	**parse(int ac, char **av);
void    ft_show_error(char *str);


#endif