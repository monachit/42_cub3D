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
    t_data data;

    data = parse(ac, av);


    game_plan(&data);
    return (0);
}
