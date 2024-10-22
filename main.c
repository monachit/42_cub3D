/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younesounajjar <younesounajjar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:47:33 by monachit          #+#    #+#             */
/*   Updated: 2024/10/22 09:03:59 by younesounaj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


int main(int ac, char **av)
{
    t_data data;

    data = parse(ac, av);

    int i = 0;
    while (data.map[i] != NULL)
    {
        printf("%s\n", data.map[i++]);
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


    game_plan(&data);

    return (0);
}
