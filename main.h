/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younesounajjar <younesounajjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:35:46 by monachit          #+#    #+#             */
/*   Updated: 2024/10/21 11:51:34 by younesounaj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include "mlx/mlx.h"
# include "get_next_line/get_next_line.h"

typedef enum t_type{
	INIT,
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	MAP,
} t_type;

typedef struct t_read
{
	char 			*line;
	int 			nb_words;
	t_type			type;
	struct t_read 	*next;
} 	t_read;

typedef struct t_map
{
	char			*line;
	struct t_map	*next;
}	t_map;

typedef	struct t_data
{
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;
	int			c1;
	int			c2;
	int			c3;
	int			f1;
	int			f2;
	int			f3;
	t_map		*head_map;
	char		**map;
}	t_data;


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
	int c;
	int p;
}	t_vars;

void    game_plan(char **map);

// parsing
t_data  parse(int ac, char **av);
void    ft_show_error(char *str);
int 	calcul_words(char *str);
void    insert_t_read(t_read **file, char *str);


#endif