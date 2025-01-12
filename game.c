/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:42:41 by monachit          #+#    #+#             */
/*   Updated: 2025/01/12 21:17:05 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int ft_new(char **map)
{
    int i;

    i = 6;
    while (map[i])
        i++;
    return (i - 6);
}

int my_mlx_pixel_get(t_textures *txt, int x, int y)
{
	int color;

    if ((y >= txt->height * 100) || (x  >= txt->width * 100))
        return (0);
	color = *(int *)(txt->addr + (y * txt->line_length + x * (txt->bit_per_pixel / 8)));
    return (color);
}

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

    if ((y >= S_H) || (x  >= S_W))
        return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void clear_image(t_vars *vars, int color){
    for (int y = 0; y <  S_H; y++) {
        for (int x = 0; x <  S_W; x++) {
            my_mlx_pixel_put(vars, x, y, color);
        }
    }
}



int is_ray_facing_down(double rayAngle)
{
    double sinValue = sin(rayAngle);
    if (sinValue > 0)
        return 1;
    return 0;
}

int is_ray_facing_up(double rayAngle)
{
    double sinValue = sin(rayAngle);
    if (sinValue < 0)
        return 1;
    return 0;
}

int is_ray_facing_right(double rayAngle)
{
    double cosValue = cos(rayAngle);
    if (cosValue > 0)
        return 1;
    return 0;
}

int is_ray_facing_left(double rayAngle)
{
    double cosValue = cos(rayAngle);
    if (cosValue < 0)
        return 1;
    return 0;
}


double nor_angle(double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int    wall_check(double x, double y, t_vars *vars)
{
    int mx, my;

    mx = (int)(x / TILE_SIZE);
    my = (int)(y / TILE_SIZE);
    
    if (mx < 0 || my < 0 || mx >= vars->win_width || my >= vars->win_height)
        return (0);
     if  (vars->map1[my][mx] == '1')
        return (0);
    return (1);
}

double get_h_inter(t_vars *vars, double angl)
{
    double h_x, h_y;
    double x_step, y_step;

    y_step = TILE_SIZE;
    if (is_ray_facing_up(angl))
		y_step *= -1;
    x_step = y_step / tan(angl);
    if ((is_ray_facing_left(angl) && x_step > 0) || (is_ray_facing_right(angl)
		&& x_step < 0))
		x_step *= -1;
    if (is_ray_facing_down(angl))
        h_y = floor(vars->p_y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
    else 
        h_y = floor(vars->p_y / TILE_SIZE) * TILE_SIZE - 0.001; //  the computer might think the line is inside the next square, so it tries to draw more lines where it shouldn’t.
    printf("%f\n ", h_y);
    h_x = vars->p_x + (h_y - vars->p_y) / tan(angl);
    while (wall_check(h_x, h_y, vars))
    {
        h_x += x_step;
        h_y += y_step;
    }
    
    return sqrt(pow(h_x - vars->p_x, 2) + pow(h_y - vars->p_y, 2));
}

double get_v_inter(t_vars *vars, double angl)
{
    double v_x, v_y;
    double x_step, y_step;

    x_step = TILE_SIZE;
    if (is_ray_facing_left(angl))
		x_step *= -1;
    y_step = x_step * tan(angl);
    if ((is_ray_facing_up(angl) && y_step > 0 ) || (is_ray_facing_down(angl)
			&& y_step < 0))
		y_step *= -1;
	if (is_ray_facing_left(angl))
		v_x = floor(vars->p_x / TILE_SIZE) * TILE_SIZE - 0.001;
	else
		v_x = floor(vars->p_x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
    v_y = vars->p_y + (v_x - vars->p_x) * tan(angl);
    while (wall_check(v_x, v_y, vars))
    {
        v_x += x_step;
        v_y += y_step;
    }
    return sqrt(pow(v_x - vars->p_x, 2) + pow(v_y - vars->p_y, 2));
}

int get_x(t_vars *vars, double ray)
{
    if (vars->flg_achmn_hayt == 0)
        return fmod((vars->p_x + cos(ray) * vars->distence), TILE_SIZE);
    else
        return fmod((vars->p_y + sin(ray) * vars->distence), TILE_SIZE);
}

void rander_wall(t_vars *vars, int ray, double ray_a)
{
    double wall_h;
    double bottom_p;
    double top_p;

    vars->distence *= cos(ray_a - vars->direction);
 
    wall_h = (TILE_SIZE / vars->distence) * (S_H / 100 * TILE_SIZE / 2) / tan(FOV / 2);
    top_p = (S_H/ 2) - (wall_h /2);
    bottom_p = (S_H / 2) + (wall_h /2);

    if (top_p < 0)
        top_p = 0;
    if (bottom_p > S_H)
        bottom_p =  S_H;
    int t = top_p;
    int b = bottom_p;
    int x = get_x(vars, ray_a);
    int y;
    int tmp_y = top_p;
    while (t > 0)
        my_mlx_pixel_put(vars, ray, (int)t--, 0xF542C2);
    while (b <  S_H)
        my_mlx_pixel_put(vars, ray, (int)b++, 0x4290F5);
    while (top_p <= bottom_p)
    {
        y = (top_p - tmp_y) * TILE_SIZE / wall_h;
        int color = my_mlx_pixel_get(vars->textures.north, x, y);
        my_mlx_pixel_put(vars, ray, (int)top_p, color);
        (int)top_p++;
    }
}

void cast_rays(t_vars *vars)
{
    double first_ray;
    double x_inter;
    double h_inter;
    double  add_angl;

    add_angl = (FOV / (S_W));
    int ray = 0;
    first_ray = vars->direction - (FOV / 2);
    while (ray <  S_W)
    {
        x_inter = get_v_inter(vars, nor_angle(first_ray)); // vertical
        h_inter = get_h_inter(vars, nor_angle(first_ray)); // horizontal 
        if (x_inter < h_inter)
        {
            vars->flg_achmn_hayt = 1;
            vars->distence = x_inter;
        }
        else
        {
            vars->flg_achmn_hayt = 0;
            vars->distence = h_inter;
        }
        rander_wall(vars, ray, first_ray);
        first_ray += add_angl;
        ray++;
    }
    
}

void drawing(t_vars *vars)
{    
    // draw_square(vars, vars->p_x, vars->p_y, 20, 0xFF6FFF);
    // for (int i = 0; i < vars->win_height; i++) 
    // {
    //     for (int j = 0; j < vars->win_width; j++) 
    //     {
    //         if (vars->map1[i][j] == '1')
    //             draw_square(vars, j * 100, i * 100, 100, 0xFF6FFF); 
    //     }
    // }
    clear_image(vars, 0x000000); 
    cast_rays(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}
int	close_window(void *v)
{
    (void)v;
	exit(EXIT_SUCCESS);
	return (0);
}

int key_hook(int keycode, t_vars *vars)
{
    double move_speed = 20.0;
    double rotation_speed = 0.1;
    double new_x, new_y;

    new_x = vars->p_x;
    new_y = vars->p_y;
    if (keycode == 119)
    {
        new_x += cos(vars->direction) * move_speed;
        new_y += sin(vars->direction) * move_speed;
    }
    else if (keycode == 97)
    {
        new_x += sin(vars->direction) * move_speed;
        new_y -= cos(vars->direction) * move_speed;
    }
    else if (keycode == 100)
    {
        new_x -= sin(vars->direction) * move_speed;
        new_y += cos(vars->direction) * move_speed;
    }
    else if (keycode == 115)
    {
        new_x -= cos(vars->direction) * move_speed;
        new_y -= sin(vars->direction) * move_speed;
    }
    else if (keycode == 65361)
        vars->direction -= rotation_speed;
    else if (keycode == 65363)
        vars->direction += rotation_speed;
    else if (keycode == 53)
        close_window(NULL);        
    if (wall_check(new_x, new_y, vars))
    {
        vars->p_x = new_x;
        vars->p_y = new_y;
    }
    vars->direction = nor_angle(vars->direction);
    drawing(vars);
    return 0;
}


void handl_direction(t_data *data , double *s)
{
    int i = 0;
    int j =0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (data->map[i][j] == 'N')
                *s = PI/2;
            else if (data->map[i][j] == 'E')
                *s = 0;
            else if (data->map[i][j] == 'W')
                *s = PI;
            else if (data->map[i][j] == 'S')
                *s = 3* PI/ 2;
            if (*s != -1)
                return ;
            j++;
        }
        i++;
    }
}

t_textures  *texture_loader(t_vars *vars, char *path)
{
    t_textures *txt = malloc(sizeof(t_textures));
    
    txt->img = mlx_xpm_file_to_image(vars->mlx, path, &txt->width, &txt->height);

    txt->addr = mlx_get_data_addr(txt->img, &txt->bit_per_pixel, &txt->line_length, &txt->endian);

    return (txt);
}

void    init_tssawer_amaalem(t_data *data, t_vars *vars)
{
    vars->textures.north = texture_loader(vars, data->north_path);
    vars->textures.south = texture_loader(vars, data->north_path);
    vars->textures.east = texture_loader(vars, data->north_path);
    vars->textures.west = texture_loader(vars, data->north_path);

}

void    game_plan(t_data *data)
{
    t_vars vars;

    vars.map1 = data->map;
    vars.mlx = mlx_init();
    vars.win_width = ft_strlen(data->map[0]);
    vars.win_height = 0;
    vars.direction = -1;
    
    handl_direction(data, &vars.direction);
    while (data->map[vars.win_height])
        vars.win_height++;
    vars.win = mlx_new_window(vars.mlx, S_W, S_H , "YWAAA");
    if (!vars.win)
        ft_show_error("mlx_new_window function fails");
    vars.img = mlx_new_image(vars.mlx, S_W,S_H);
    vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);

    init_tssawer_amaalem(data, &vars);

    for (int j = 0; j < vars.win_height; j++)
    {
        for (int i = 0; i < vars.win_width; i++)
        {
            if (data->map[j][i] != '1' && data->map[j][i] == '0')
            {
                vars.p_x = i * 100;
                vars.p_y = j * 100;
                
            }
                
        }
    }
    mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_hook(vars.win, 17, 0L, close_window, NULL);
    mlx_loop(vars.mlx);

}
