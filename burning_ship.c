/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:53:17 by lugibone          #+#    #+#             */
/*   Updated: 2020/01/06 16:16:33 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	bs_loop(t_scene *scene, int i)
{
	double tmp;

	tmp = fabs(scene->z.r);
	scene->z.r = fabs(scene->z.r) * fabs(scene->z.r) - fabs(scene->z.i) *
fabs(scene->z.i) + scene->c.r;
	scene->z.i = 2 * fabs(scene->z.i) * tmp + scene->c.i;
	return (++i);
}

int	bs_set(t_scene *scene)
{
	int i;
	int x;
	int y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			init_md(scene, &i, x, y);
			i = bs_loop(scene, i);
			while ((scene->z.r * scene->z.r) + (scene->z.i * scene->z.i) < 4 &&
i < scene->iteration)
				i = bs_loop(scene, i);
			if (i == scene->iteration)
				fill_pixel(scene->str, x, y, scene->bg_color);
			else
				fill_pixel(scene->str, x, y, i * 0x010203);
			y++;
		}
		x++;
	}
	return (1);
}
