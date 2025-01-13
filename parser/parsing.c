/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younesounajjar <younesounajjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:35:17 by monachit          #+#    #+#             */
/*   Updated: 2024/11/02 11:25:42 by younesounaj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void    init_data(t_data *data)
{
    data->c1 = -1;
    data->c2 = -1;
    data->c3 = -1;
    data->f1 = -1;
    data->f2 = -1;
    data->f3 = -1;
    data->north_path = NULL;
    data->south_path = NULL;
    data->east_path = NULL;
    data->west_path = NULL;
}

t_data  parse(int ac, char **av)
{
    t_read  *file;
    t_data  data;

    if (ac != 2)
        ft_show_error("Arguments number not valid >./cub3d name.cub<\n");
    if (check_name(av[1]))
        ft_show_error("Map name not valid >name.cub<\n");
    file = read_file(av[1]);
    token_data(&file);
    if (!check_order(file))
    {
        // HNAYA FREEYI READ FILE YA ZAAML
        ft_show_error("File syntax invalid\n");
    }
    init_data(&data);
    extract_colors(file, &data);
    extract_paths(file, &data);
    data.map = extract_map(file, calcul_token(file, MAP));
    // HNAYA FREEYI READ YA ZWIWN DIAL MAMAH
    free_read(&file);

    

    return (data);
}
