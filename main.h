/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:35:46 by monachit          #+#    #+#             */
/*   Updated: 2024/09/16 16:13:13 by monachit         ###   ########.fr       */
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

typedef struct s_vars
{
	char	**map1;
	int		player_x;
	int		player_y;
	int		heigth;
	int		width;
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
}	t_vars;

void    game_plan(char **map);
char 	**parse(int ac, char **av);
void    ft_show_error(char *str);


#endif