/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:49:41 by lugibone          #+#    #+#             */
/*   Updated: 2020/01/06 15:41:27 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	change_color(t_point *point, int color)
{
	point->color = color;
	if (point->color > 0xFFFFFF)
		point->color = 0xFFFFFF;
	if (point->color < 0x000000)
		point->color = 0x000000;
}

int		rgb_r(int color)
{
	return ((color & 0xFF0000) >> 16);
}

int		rgb_g(int color)
{
	return ((color & 0x00FF00) >> 8);
}

int		rgb_b(int color)
{
	return ((color & 0x0000FF));
}
