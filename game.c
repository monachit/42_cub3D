/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monachit <monachit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:42:41 by monachit          #+#    #+#             */
/*   Updated: 2024/09/19 16:32:57 by monachit         ###   ########.fr       */
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
static int i2 = 100;
static int i = 100;
int key_hook(int keycode, t_vars *vars)
{
    int next_x = i;
    int next_y = i2;

    draw_square(vars, vars->p_x * i, vars->p_y * i2, 20, 0xFFFFFF);
    if (keycode == 119)  // Up (W key)
        next_y -= 20;
    else if (keycode == 115)  // Down (S key)
        next_y += 20;
    else if (keycode == 97)  // Left (A key)
        next_x -= 20;
    else if (keycode == 100)  // Right (D key)
        next_x += 20;
    printf("%d  %d\n", next_x * vars->p_x, next_y * vars->p_y);
    if (vars->map1[vars->p_y * next_y/ 100][vars->p_x * next_x / 100] != '1')
    {
        i = next_x;
        i2 = next_y;
    }
    draw_square(vars, vars->p_x * i, vars->p_y * i2, 20, 0xFF6FFF);
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
        "1N01",
        "1001",
        "1001",
        "1111",
        NULL
    };

    vars.map1 = map;
    vars.mlx = mlx_init();
    vars.win_width = ft_strlen(map[0]);
    vars.win_height = 0;
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
                draw_square(&vars, j * 100, i * 100, 100, 0x00FF0000); 
            else if (map[i][j] == '0')
                draw_square(&vars, j * 100, i * 100, 100, 0xFFFFFF);
            else if (map[i][j] == 'N')
            {
                draw_square(&vars, j * 100, i * 100, 100, 0xFFFFFF);
                draw_square(&vars, j * 100, i * 100, 20, 0xFF6FFF);
            }
        }
    }
    // mlx_key_hook(vars.win, key_hook, &vars);
    mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
    
    mlx_loop(vars.mlx);
}
