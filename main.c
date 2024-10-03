/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younesounajjar <younesounajjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:47:33 by monachit          #+#    #+#             */
/*   Updated: 2024/10/02 18:57:25 by younesounaj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


int main(int ac, char **av)
{
    t_data data;

    data = parse(ac, av);
    
    t_map *map = data.head_map;
    while (map)
    {
        printf("%s\n", map->line);
        map = map->next;
    }
    printf("\n");

    printf("%s\n",data.north_path );
    printf("%s\n",data.south_path );
    printf("%s\n",data.west_path );
    printf("%s\n",data.east_path );
    printf("f1 = %d\n", data.f1);
    printf("f2 = %d\n", data.f2);
    printf("f3 = %d\n", data.f3);
    printf("c1 = %d\n", data.c1);
    printf("c2 = %d\n", data.c2);
    printf("c3 = %d\n", data.c3);


    // char **maps = NULL;
    // game_plan(maps);
    return (0);
}

/*
111111111111111
111111000111111
111110000011111
1111000N0001111
111000000000111
110000000000011
100001111100001
110000111000011
111000010000111
111100000001111
111110000011111
111111000111111
111111111111111
*/