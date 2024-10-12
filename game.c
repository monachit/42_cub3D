/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:42:41 by monachit          #+#    #+#             */
/*   Updated: 2024/10/12 14:18:21 by monachit         ###   ########.fr       */
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
	for (int i = 0; i < size; i++)  // Loop through the square's height
	{
		for (int j = 0; j < size; j++)  // Loop through the square's width
		{
			my_mlx_pixel_put(vars, x + j, y + i, color);  // Plot the pixel
		}
	}
}

void draw_line(t_vars *vars, double start_x, double start_y, double end_x, double end_y, int color) {

    int dx = abs((int)end_x - (int)start_x);
    int dy = abs((int)end_y - (int)start_y);

    int sx = (start_x < end_x) ? 1 : -1;
    int sy = (start_y < end_y) ? 1 : -1;
    int err = dx - dy;

    while (1) 
    {
        if (start_x >= 0 && start_x < 500 && start_y >= 0 && start_y < 500)
        {
            if (vars->map1[(int)(start_y / 100)][(int)(start_x / 100)] != '1')
                my_mlx_pixel_put(vars, (int)start_x, (int)start_y, color);
            else
                break;
        }
        if ((int)start_x == (int)end_x && (int)start_y == (int)end_y)
            break;
        int err2 = err * 2;
        if (err2 > -dy) { err -= dy; start_x += sx; }
        if (err2 < dx) { err += dx; start_y += sy; }
    }
}



void cast_rays(t_vars *vars) {
    for (int i = 0; i < NUM_RAYS; i++)
    {
        double ray_angle = vars->ray_angles[i];
        double ray_dir_x = cos(ray_angle);
        double ray_dir_y = sin(ray_angle);
        double ray_x = vars->p;
        double ray_y = vars->c;
        while (1)
        {
            ray_x += ray_dir_x;
            ray_y += ray_dir_y;
            int map_x = (int)(ray_x / 100);
            int map_y = (int)(ray_y / 100);
            if (vars->map1[map_y][map_x] == '1')
            {
                draw_line(vars, vars->p, vars->c, ray_x, ray_y, 0xFFFFFF); 
                break;
            }
        }
    }
}

void drawing(t_vars *vars)
{    
    clear_image(vars, 0x000000); 
    draw_square(vars, vars->p, vars->c, 20, 0xFF6FFF);
    for (int i = 0; i < vars->win_height; i++) 
    {
        for (int j = 0; j < vars->win_width; j++) 
        {
            if (vars->map1[i][j] == '1')
                draw_square(vars, j * 100, i * 100, 100, 0xFF6FFF); 
        }
    }
    for (int i = 0; i < NUM_RAYS; i++)
        vars->ray_angles[i] = vars->direction - (M_PI / 6) + (i * (M_PI / 30));
    cast_rays(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

int key_hook(int keycode, t_vars *vars)
{
    double move_speed = 20.0;
    double rotation_speed = 0.1;
    draw_square(vars, vars->p, vars->c, 20, 0x000000);
    if (keycode == 119)
    {
        vars->p += cos(vars->direction) * move_speed;
        vars->c += sin(vars->direction) * move_speed;
    } 
    else if (keycode == 115)
    {
        vars->p -= cos(vars->direction) * move_speed;
        vars->c -= sin(vars->direction) * move_speed;
    } 
    else if (keycode == 65361)
        vars->direction -= rotation_speed;
    else if (keycode == 65363)
        vars->direction += rotation_speed;
    int map_y = (int)(vars->c / 100);
    int map_x = (int)(vars->p/ 100);
    if (vars->map1[map_y][map_x] != '1')
    {
        vars->c = (int)vars->c;
        vars->p = (int)vars->p;
    }
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

void    game_plan(char **map1)
{
    t_vars vars;

    char *map[] = {
        "1111",
        "1001",
        "1001",
        "10N1",
        "1111",
        NULL
    };

    vars.map1 = map;
    vars.mlx = mlx_init();
    vars.win_width = ft_strlen(map[0]);
    vars.win_height = 0;
    vars.direction = 0;
    while (map[vars.win_height])
        vars.win_height++;
    vars.win = mlx_new_window(vars.mlx, vars.win_width * 100, vars.win_height * 100, "YWAAA");
    if (!vars.win)
        ft_show_error("mlx_new_window function fails");
    vars.img = mlx_new_image(vars.mlx, vars.win_width * 100, vars.win_height * 100);
    vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
    set_pos(map, &vars.p_x, &vars.p_y);
    for (int i = 0; i < vars.win_height; i++)
    {
        for (int j = 0; j < vars.win_width; j++)
        {
            if (map[i][j] == 'N')
            {
                // draw_square(&vars, j * 100, i * 100, 100, 0xFFFFFF);
                draw_square(&vars, j * 100, i * 100, 20, 0xFF6FFF);
                vars.c = i * 100;
                vars.p = j * 100;
            }
            if (map[i][j] == '1')
                draw_square(&vars, j * 100, i * 100, 100, 0xFF6FFF);
                
        }
    }

    mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
    
    mlx_loop(vars.mlx);

}