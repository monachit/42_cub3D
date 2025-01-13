/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younesounajjar <younesounajjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:47:33 by monachit          #+#    #+#             */
/*   Updated: 2024/11/08 16:28:46 by younesounaj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void    free_data(t_data *data)
{
    free(data->east_path);
    free(data->west_path);
    free(data->north_path);
    free(data->south_path);
    int i = 0;
    while (data->map[i])
        free(data->map[i++]);
    free(data->map);
}

int main(int ac, char **av)
{
    t_data data;

    data = parse(ac, av);


    // exit (1);
    game_plan(&data);
    
    free_data(&data);
    return (0);
}
