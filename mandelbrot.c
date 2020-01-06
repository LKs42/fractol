/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:53:01 by lugibone          #+#    #+#             */
/*   Updated: 2020/01/06 16:23:25 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		md_loop(t_scene *scene, int i)
{
	double tmp;

	tmp = scene->z.r;
	scene->z.r = scene->z.r * scene->z.r - scene->z.i * scene->z.i + scene->c.r;
	scene->z.i = 2 * scene->z.i * tmp + scene->c.i;
	return (++i);
}

void	init_md(t_scene *scene, int *i, int x, int y)
{
	double zoomx;
	double zoomy;

	zoomx = WIDTH / (scene->plan.x2 - scene->plan.x1);
	zoomy = HEIGHT / (scene->plan.y2 - scene->plan.y1);
	*i = 0;
	scene->z.r = 0;
	scene->z.i = 0;
	scene->c.r = x / zoomx + scene->plan.x1;
	scene->c.i = y / zoomy + scene->plan.y1;
}

int		md_set(t_scene *scene)
{
	int i;
	int x;
	int y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y++ < HEIGHT)
		{
			init_md(scene, &i, x, y);
			i = md_loop(scene, i);
			while ((scene->z.r * scene->z.r) + (scene->z.i * scene->z.i) < 4 &&
i < scene->iteration)
				i = md_loop(scene, i);
			if (i == scene->iteration)
				fill_pixel(scene->str, x, y, scene->bg_color);
			else
				fill_pixel(scene->str, x, y, i * 0x010203);
		}
		x++;
	}
	return (1);
}
