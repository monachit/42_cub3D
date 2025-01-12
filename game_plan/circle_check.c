/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnachit <mnachit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:39:51 by mnachit           #+#    #+#             */
/*   Updated: 2025/01/13 00:02:16 by mnachit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	rayfacing_down(double rayAngle)
{
	double	sinvalue;

	sinvalue = sin(rayAngle);
	if (sinvalue > 0)
		return (1);
	return (0);
}

int	rayfacing_up(double rayAngle)
{
	double	sinvalue;

	sinvalue = sin(rayAngle);
	if (sinvalue < 0)
		return (1);
	return (0);
}

int	rayfacing_right(double rayAngle)
{
	double	cosvalue;

	cosvalue = cos(rayAngle);
	if (cosvalue > 0)
		return (1);
	return (0);
}

int	rayfacing_left(double rayAngle)
{
	double	cosvalue;

	cosvalue = cos(rayAngle);
	if (cosvalue < 0)
		return (1);
	return (0);
}

double	nor_angle(double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}
