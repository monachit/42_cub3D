/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younesounajjar <younesounajjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:35:46 by monachit          #+#    #+#             */
/*   Updated: 2024/11/01 00:51:47 by younesounaj      ###   ########.fr       */
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
# include <math.h>

#define PI 3.141592653589793
#define length_ray  10
#define FOV  60 * PI / 180
#define S_W 1000
#define S_H 1000
#define TILE_SIZE 100

typedef enum t_type{
	INIT,
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	EMPTY,
	MAP,
} t_type;

typedef struct t_read
{
	char 			*line;
	t_type			type;
	struct t_read 	*next;
} 	t_read;


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
	char		**map;
}	t_data;


typedef struct s_vars
{
    char    **map1;
    int     player_x;
    int     player_y;
    int     heigth;
    int     width;
    int     p_1;
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    double     p_x;
    double     p_y;
    int     win_width;
    int     win_height;
	double direction;
} t_vars;


typedef struct s_vector
{
	double d_x;
	double d_y;
	
}	vector;


void    game_plan(t_data *t_data);

// parsing
t_data  parse(int ac, char **av);

// utils
int 	check_name(char *name);
t_read  *read_file(char *av);
int 	ft_strcmp(const char *s1, const char *s2);
int		ft_atoi_lhbal(char *str);
void    ft_show_error(char *str);

// read file
void    insert_t_read(t_read **file, char *str);
t_read  *read_file(char *av);
int 	calcul_token(t_read *file, t_type type);

// tokenize data
void    token_data(t_read **file);

// parsing file
bool    check_order(t_read *file);

// extract colors
void    extract_colors(t_read *file, t_data *data);

// extract paths
void    extract_paths(t_read *file, t_data *data);

// extract map
char    **extract_map(t_read *file, t_data *data, int len);

#endif