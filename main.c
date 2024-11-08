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


int main(int ac, char **av)
{
    t_game game;

    game.input = parse(ac, av);
    printf("%d\n", game.input.c1);
    printf("%d\n", game.input.c2);
    printf("%d\n", game.input.c3);
    printf("%d\n", game.input.f1);
    printf("%d\n", game.input.f2);
    printf("%d\n", game.input.f3);

    printf("no = **%s**\n", game.input.north_path);
    printf("so = **%s**\n", game.input.south_path);
    printf("we = **%s**\n", game.input.west_path);
    printf("ea = **%s**\n", game.input.east_path);
    
    int i = 0;
    while (game.input.map[i])
    {
        printf("%s\n", game.input.map[i++]);
    }



    return (0);
}
