/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <younajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:35:46 by monachit          #+#    #+#             */
/*   Updated: 2025/01/16 00:59:14 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include "get_next_line/get_next_line.h"
# include <math.h>
# include <mlx.h>

# define PI 3.141592653589793
# define S_W 1000
# define S_H 1000
# define TILE_SIZE 100

typedef enum t_type
{
	INIT,
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	EMPTY,
	MAP,
}					t_type;

typedef struct t_read
{
	char			*line;
	t_type			type;
	struct t_read	*next;
}					t_read;

typedef struct t_data
{
	char			*north_path;
	char			*south_path;
	char			*east_path;
	char			*west_path;
	int				c1;
	int				c2;
	int				c3;
	int				f1;
	int				f2;
	int				f3;
	char			**map;
	int				h;
	int				v;
}					t_data;

typedef struct t_textures
{
	void			*img;
	char			*addr;
	int				height;
	int				width;
	int				bit_per_pixel;
	int				line_length;
	int				endian;

}					t_textures;

typedef struct t_tata
{
	t_textures		*north;
	t_textures		*south;
	t_textures		*west;
	t_textures		*east;
}					t_tata;

typedef struct s_vars
{
	t_data			*data;
	char			**map1;
	int				player_x;
	int				player_y;
	int				heigth;
	int				width;
	int				p_1;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	double			distence;
	double			p_x;
	double			norm_1;
	double			norm2;
	double			p_y;
	int				win_width;
	int				win_height;
	int				c;
	int				p;
	double			direction;
	int				flg_achmn_hayt;
	t_tata			textures;
}					t_vars;

t_data				parse(int ac, char **av);
void				game_plan(t_data *t_data);
int					check_name(char *name);
t_read				*read_file(char *av);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi_lhbal(char *str);
void				ft_show_error(char *str);
void				free_read(t_read **list);
void				insert_t_read(t_read **file, char *str);
t_read				*read_file(char *av);
int					calcul_token(t_read *file, t_type type);
void				token_data(t_read **file);
int					skip_spaces(char *str, int i);
int					calcul_words(char *str);
int					extract_len(char *str, int i);
bool				check_characters(char *str);
bool				check_empty_line(char *str);
bool				check_order(t_read *file);
void				extract_colors(t_read *file, t_data *data);
int					check_virguls(char *s);
int					len_nb(char *s, int *i);
void				norme_c(t_data *data, int i, char *s, char *tmp);
int					skip_beg(char *str);
int					len_str_color(char *s, int i);
void				extract_paths(t_read *file, t_data *data);
char				**extract_map(t_read *file, int len);
int					ft_strlen_lhbal(char *str);
bool				check_player(char **ss);
bool				parse_map(char **map);
char				**allocation_strs(int len);
char				**norme_map(t_read *file, int len);
t_textures			*chose_image(t_vars *vars, double ray_a);
int					get_x(t_vars *vars, double ray);
int					my_mlx_pixel_get(t_textures *txt, int x, int y);
t_textures			*texture_loader(t_vars *vars, char *path);
void				init_tssawer_amaalem(t_data *data, t_vars *vars);
int					rayfacing_down(double rayAngle);
int					rayfacing_up(double rayAngle);
int					rayfacing_right(double rayAngle);
int					rayfacing_left(double rayAngle);
double				nor_angle(double angle);
double				get_h_inter(t_vars *vars, double angl);
double				get_v_inter(t_vars *vars, double angl);
void				rander_wall2(int top_p, int bottom_p, t_vars *vars,
						double ray_a);
void				rander_wall(t_vars *vars, int ray, double ray_a);
void				cast_rays2(t_vars *vars, double x, double y);
void				cast_rays(t_vars *vars);
int					wall_check(double x, double y, t_vars *vars);
int					close_window(void *v);
int					key_hook(int keycode, t_vars *vars);
void				my_mlx_pixel_put(t_vars *data, int x, int y, int color);
void				clear_image(t_vars *vars, int color);
void				drawing(t_vars *vars);
void				free_data(t_data *data);
void				ft_norm_free_txt(t_vars *vars);
void				ft_free_norme_one(t_vars *vars);

#endif