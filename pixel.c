/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:28:15 by lugibone          #+#    #+#             */
/*   Updated: 2020/01/06 16:58:03 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fill_pixel(int *my_image_string, int x, int y, int color)
{
	int i;

	if (!(x <= 0 || y <= 0 || y >= HEIGHT || x >= WIDTH))
	{
		i = x + WIDTH * y;
		my_image_string[i] = color;
	}
}

void	fill_img(t_scene *param, int color)
{
	int i;
	int c;

	c = color;
	i = 0;
	while (i < param->win_width * param->win_height)
	{
		param->str[i] = c;
		i++;
	}
}

void	usage(void)
{
	ft_putendl("usage: ./fractol [1-3]");
}
