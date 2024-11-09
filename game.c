/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younesounajjar <younesounajjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:42:41 by monachit          #+#    #+#             */
/*   Updated: 2024/10/22 09:05:55 by younesounaj      ###   ########.fr       */
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

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void clear_image(t_vars *vars, int color) {
    for (int y = 0; y < vars->win_height * 100; y++) {
        for (int x = 0; x < vars->win_width * 100; x++) {
            my_mlx_pixel_put(vars, x, y, color);
        }
    }
}


void	draw_square(t_vars *vars, int x, int y, int size, int color)
{
	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++)
		{
			my_mlx_pixel_put(vars, x + j, y + i, color);
		}
	}
}

// void draw_line(t_vars *vars, double start_x, double start_y, double end_x, double end_y, int color) {

//     int dx = abs((int)end_x - (int)start_x);
//     int dy = abs((int)end_y - (int)start_y);

//     int sx = (start_x < end_x) ? 1 : -1;
//     int sy = (start_y < end_y) ? 1 : -1;
//     int err = dx - dy;

//     while (1) 
//     {
//         if (start_x >= 0 && start_x < 500 && start_y >= 0 && start_y < 500)
//         {
//             if (vars->map1[(int)(start_y / 100)][(int)(start_x / 100)] != '1')
//                 my_mlx_pixel_put(vars, (int)start_x, (int)start_y, color);
//             else
//                 break;
//         }
//         if ((int)start_x == (int)end_x && (int)start_y == (int)end_y)
//             break;
//         int err2 = err * 2;
//         if (err2 > -dy) { err -= dy; start_x += sx; }
//         if (err2 < dx) { err += dx; start_y += sy; }
//     }
// }

double	nor_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}


int	is_ray_facing_down(float rayAngle)
{
	return (rayAngle > 0 && rayAngle < M_PI);
}

int	is_ray_facing_up(float rayAngle)
{
	return (!is_ray_facing_down(rayAngle));
}

int	is_ray_facing_right(float rayAngle)
{
	return (rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI);
}

int	is_ray_facing_left(float rayAngle)
{
	return (!is_ray_facing_right(rayAngle));
}

int     until_circle(double angl, char c)
{
    if (c == 'x')
    {
        if (angl > 0 && angl < PI)
            return 1;
    }
    else if (c == 'y')
    {
        if (angl > PI / 2 && angl < PI * 3 / 2)
            return 1;
    }
    return (0);
}

int    wall_check(double x, double y, t_vars *vars)
{
    int mx, my;

    mx = (int)x / TILE_SIZE;
    my = (int) y / TILE_SIZE;
    
    if (mx < 0 || my < 0 || mx >= vars->win_width || my >= vars->win_height )
        return (0);
     if  (vars->map1[my][mx] == '1')
        return (0);
    return (1);
}
int inter_check(double angle, double *inter, double *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}
double get_h_inter(t_vars *vars, double angl)
{
    double h_x;
    double h_y;
    double x_step;
    double y_step;
    int pixel;

    y_step = TILE_SIZE;
    x_step = TILE_SIZE / tan(angl);
    h_y = floor(vars->p_y / TILE_SIZE) * TILE_SIZE;
    pixel = inter_check(angl, &h_y, &y_step, 1);
    h_x = vars->p_x + (h_y - vars->p_y) / tan(angl);
    if ((until_circle(angl, 'y') && x_step > 0 ) || !(until_circle(angl, 'y') && x_step < 0))
        x_step *= -1;
    while (wall_check(h_x, h_y - pixel, vars))
    {
        h_x += x_step;
        h_y += y_step;
    }
    return (sqrt(pow(h_x -  vars->p_x, 2) + pow(h_y - vars->p_y, 2)));
}

double  get_v_inter(t_vars *vars, double angl)
{
    double v_x;
    double v_y;
    double x_step;
    double y_step;
    int pixel;

    x_step = TILE_SIZE;
    y_step = TILE_SIZE * tan(angl);
    v_x = floor(vars->p_x / TILE_SIZE) * TILE_SIZE;
    pixel = inter_check(angl, &v_x, &x_step, 0);
    v_y = vars->p_y + (v_x - vars->p_x) * tan(angl);
    if ((until_circle(angl, 'x') && y_step < 0 ) || !(until_circle(angl, 'x') && y_step > 0))
        y_step *= -1;
    while (wall_check(v_x - pixel, v_y, vars))
    {
        v_x += x_step;
        v_y += y_step;
   
    }
    return (sqrt(pow(v_x -  vars->p_x, 2) + pow(v_y - vars->p_y, 2)));
}

void rander_wall(t_vars *vars, int ray)
{
    double wall_h;
    double bottom_p;
    double top_p;

    wall_h = (TILE_SIZE / vars->distence) * (vars->win_width * 100/ 2) / tan(FOV / 2);
    top_p = (900 / 2) - (wall_h /2);
    bottom_p = (900 / 2) + (wall_h /2);

    if (top_p < 0)
        top_p = 0;
    if (bottom_p > 900)
        bottom_p = 900;
    while (top_p < bottom_p)
        my_mlx_pixel_put(vars, ray, top_p++, 0xFFFFFF);
}

void cast_rays(t_vars *vars)
{
    double first_ray;
    double x_inter;
    double h_inter;
    double  add_angl;

    add_angl = (FOV / S_W);
    int ray = 0;

    first_ray = vars->direction - (FOV / 2);
    while (ray < S_W)
    {
        x_inter = get_v_inter(vars, nor_angle(first_ray)); // vertical
        h_inter = get_h_inter(vars, nor_angle(first_ray)); // horizontal 
        if (x_inter <= h_inter)
            vars->distence = x_inter;
        else
            vars->distence = h_inter;
        // draw_line(vars, vars->p_x, vars->p_y, vars->p_x + cos(first_ray) * vars->distence, vars->p_y + sin(first_ray) * vars->distence, 0xFFFFFF);
        first_ray += add_angl;
        rander_wall(vars, ray);
        ray++;
    }

}

void drawing(t_vars *vars)
{    
    clear_image(vars, 0x000000); 
    // draw_square(vars, vars->p_x, vars->p_y, 20, 0xFF6FFF);
    // for (int i = 0; i < vars->win_height; i++) 
    // {
    //     for (int j = 0; j < vars->win_width; j++) 
    //     {
    //         if (vars->map1[i][j] == '1')
    //             draw_square(vars, j * 100, i * 100, 100, 0xFF6FFF); 
    //     }
    // }
    cast_rays(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

int key_hook(int keycode, t_vars *vars)
{
    double move_speed = 20.0;
    double rotation_speed = 0.1;
    if (keycode == 13)  // Up (W key) 113
    {
        vars->p_x += cos(vars->direction) * move_speed;
        vars->p_y += sin(vars->direction) * move_speed;
    } 
    else if (keycode == 1)  // Down (S key) 115
    {
        vars->p_x -= cos(vars->direction) * move_speed;
        vars->p_y -= sin(vars->direction) * move_speed;
    } 
    else if (keycode == 123)  // Left (A key) 97
        vars->direction -= rotation_speed;
    else if (keycode == 124)  // Right (D key) 100 on linux
        vars->direction += rotation_speed;

    // draw_square(vars, vars->p_x, vars->p_y, 20, 0x000000);
    vars->direction = nor_angle(vars->direction);
    drawing(vars);
    return 0;
}

void    set_pos(char **map, int *a, int *b)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N')
            {
                *a = j;
                *b = i;
                return ;
            }
            j++;
        }
        i++;
    }
}

void    game_plan(t_data *data)
{
    t_vars vars;

    // char *map[] = {
    //     "1111",
    //     "1001",
    //     "1001",
    //     "10N1",
    //     "1111",
    //     NULL
    // };

    vars.map1 = data->map;
    vars.mlx = mlx_init();
    vars.win_width = ft_strlen(data->map[0]);
    vars.win_height = 0;
    vars.direction = 0;
    while (data->map[vars.win_height])
        vars.win_height++;
    vars.win = mlx_new_window(vars.mlx, vars.win_width * 100, vars.win_height * 100, "YWAAA");
    if (!vars.win)
        ft_show_error("mlx_new_window function fails");
    vars.img = mlx_new_image(vars.mlx, vars.win_width * 100, vars.win_height * 100);
    vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
    for (int j = 0; j < vars.win_width; j++)
    {
        for (int i = 0; i < vars.win_height; i++)
        {
            if (data->map[j][i] == 'N')
            {
                vars.p_x = i * 100 + (50);
                vars.p_y = j * 100 + (50);
                
            }
                
        }
    }
    // printf("%d\n", vars.win_width);
    // printf("%d\n", vars.win_height);
    mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
    
    mlx_loop(vars.mlx);

}