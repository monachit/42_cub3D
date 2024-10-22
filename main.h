/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younesounajjar <younesounajjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:35:46 by monachit          #+#    #+#             */
/*   Updated: 2024/10/22 09:04:29 by younesounaj      ###   ########.fr       */
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
#define NUM_RAYS 10
#define length_ray  10;

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
    int     p_x;
    int     p_y;
    int     win_width;
    int     win_height;
    int     c;
    int     p;
	double ray_angles[NUM_RAYS];

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
void    ft_show_error(char *str);
int 	calcul_words(char *str);
void    insert_t_read(t_read **file, char *str);
int 	check_name(char *name);
t_read  *read_file(char *av);
int 	ft_strcmp(const char *s1, const char *s2);
void    init_data(t_data *data);
int 	extract_len_first_word(char *s, int i);
int 	skip_spaces(char *s, int i);
int		ft_atoi_lhbal(char *str);
int 	check_nb_virgul(char *s);
void    ft_rgb_colors(char *s, int *nbr1, int *nbr2, int *nbr3);
int 	map_token(char *s);
void    extract_paths(t_read *curr, char **path, int *i2, t_type type);
void    extract_colors(t_read *curr, int *n1, int *n2, int *n3, int type, int *i2);
void    collect_data(t_read **file, t_data *data);



#endif