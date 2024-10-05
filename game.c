/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:42:41 by monachit          #+#    #+#             */
/*   Updated: 2024/10/04 16:06:57 by mnachit          ###   ########.fr       */
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

vector cast_ray(t_vars *vars, double angle)
{
    vector ray_end;
    
    double ray_Dirx = cos(angle);
    double ray_Diry = sin(angle);
    
    ray_end.d_x = vars->p_x * 100 + ray_Dirx * length_ray;
    ray_end.d_y = vars->p_y * 100 + ray_Diry * length_ray;
    return ray_end;
}

void draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        my_mlx_pixel_put(vars, x0, y0, color);


        int err2 = err * 2;
        if (x0 == x1 && y0 == y1) break;
        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
        
    }
}
static int i= 0;
void draw_ray(t_vars *vars) {
    vector ray_end = cast_ray(vars, vars->p_1);
    int start_x = vars->p_x - i;
    int start_y = vars->p_y - i;
    int end_x = (int)ray_end.d_x;
    int end_y = (int)ray_end.d_y;
    draw_line(vars, start_x, start_y, end_x, end_y, 0x4575B4); // Draw the ray in blue
    }




int key_hook(int keycode, t_vars *vars)
{
    int next_x = vars->p;
    int next_y = vars->c;

    draw_square(vars, vars->p, vars->c, 20, 0xFFFFFF);
    if (keycode == 119)  // Up (W key)
        next_y -= 20;
    else if (keycode == 115)  // Down (S key)
        next_y += 20;
    else if (keycode == 97)  // Left (A key)
        next_x -= 20;
    else if (keycode == 100)  // Right (D key)
        next_x += 20;
    else if (keycode == 65361)
        i += 10;
    else if (keycode == 65363)
        i -= 10;
    if (vars->map1[next_y / 100][next_x / 100] != '1')
    {
        vars->c = next_y;
        vars->p = next_x;
    }
    draw_square(vars, vars->p, vars->c, 20, 0xFF6FFF);
    draw_ray(vars);
     mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
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
    vars.p_1 = 0;
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
            if (map[i][j] == '1') 
                draw_square(&vars, j * 100, i * 100, 97, 0x00FF0000); 
            else if (map[i][j] == '0')
                draw_square(&vars, j * 100, i * 100, 100, 0xFFFFFF);
            else if (map[i][j] == 'N')
            {
                draw_square(&vars, j * 100, i * 100, 100, 0xFFFFFF);
                draw_square(&vars, j * 100, i * 100, 20, 0xFF6FFF);
                vars.c = i * 100;
                vars.p = j * 100;
            }
        }
    }
    // mlx_key_hook(vars.win, key_hook, &vars);
    mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
    
    mlx_loop(vars.mlx);
}
