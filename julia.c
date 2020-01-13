/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:53:07 by lugibone          #+#    #+#             */
/*   Updated: 2020/01/06 17:03:57 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		init_julia(t_scene *scene, int *i, int x, int y)
{
	double zoomx;
	double zoomy;

	zoomx = WIDTH / (scene->plan.x2 - scene->plan.x1);
	zoomy = HEIGHT / (scene->plan.y2 - scene->plan.y1);
	*i = 0;
	scene->z.r = x / zoomx + scene->plan.x1;
	scene->z.i = y / zoomy + scene->plan.y1;
}

static int		julia_loop(t_scene *scene, int i)
{
	double tmp;

	tmp = scene->z.r;
	scene->z.r = scene->z.r * scene->z.r - scene->z.i * scene->z.i + scene->c.r;
	scene->z.i = 2 * scene->z.i * tmp + scene->c.i;
	return (++i);
}

int				julia_set(t_scene *scene, int xx, int yy)
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
			init_julia(scene, &i, x, y);
			scene->c.r = x_real(scene, xx);
			scene->c.i = y_real(scene, yy);
			i = julia_loop(scene, i);
			while ((scene->z.r * scene->z.r) + (scene->z.i * scene->z.i) < 4 &&
i < scene->iteration)
				i = julia_loop(scene, i);
			if (i == scene->iteration)
				fill_pixel(scene->str, x, y, scene->bg_color);
			else
				fill_pixel(scene->str, x, y, i * 0x010203);
		}
		x++;
	}
	return (1);
}

int				julia_hook(int x, int y, t_scene *scene)
{
	if (scene->fractal_id == 2)
	{
		julia_set(scene, x, y);
		mlx_put_image_to_window(scene->mlx_ptr,
				scene->win_ptr, scene->img_ptr, 0, 0);
	}
	return (1);
}
